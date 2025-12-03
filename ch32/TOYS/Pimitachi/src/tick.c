
// ****************************************************************************
//
//                                Game Tick
//
// ****************************************************************************

#include "../include.h"

// shift pet state by one tick (1 tick = 8.2 seconds, total about 10450 ticks per day)
// sleep ... pet is sleeping (True=called from IWDG reset, False=called from main loop)
// - Before calling from the main loop, call IWDG_Reload() to prevent RAM data inconsistency.
void PetTick(Bool sleep)
{
	int m;

	// watchdog reload
	IWDG_Reload();

	// increase ticks and day
	int ticks = PetTicks() + 1;
	if (ticks >= TICKSDAY) // new day
	{
		// reset ticks
		ticks = 0;

		// get current age and max
		int age = PetAge();
		int agemax = PetAgeMax();

		// decrease max age
		int penalty = 0;
		if (PetFeed() == 0) penalty++;
		if (PetHealth() == 0) penalty += 2;
		if (PetHappy() == 0) penalty++;
		penalty >>= 1;
		agemax -= penalty;
		if (agemax < age) agemax = age;
		PetSetAgeMax(agemax);

		// increase age
		if (age > agemax) age = agemax;
		PetSetAge(age);
	}
	PetSetTicks(ticks);
	RamCrc();

	// decrease feed
	m = MASK_FEED;
	if (!sleep) m >>= 2; // if not sleeping, get hungry faster
	if ((ticks & MASK_FEED) == MASK_FEED)
	{
		u8 feed = PetFeed();
		if (feed > 0) PetSetFeed(feed-1);
	}

	// decrease discipline
	if ((ticks & MASK_DISC) == MASK_DISC)
	{
		u8 disc = PetDisc();
		if (disc > 0) PetSetDisc(disc-1);
	}

	// decrease happiness
	// - If low discipline or hungry or sick, decrease happiness faster
	m = MASK_HAPPY;
	if ((PetDisc() < STATEMAX/2) || (PetFeed() < STATEMAX/2) || (PetHealth() < STATEMAX/2) || !sleep) m >>= 1;
	if ((ticks & m) == m)
	{
		u8 happy = PetHappy();
		if (happy > 0) PetSetHappy(happy-1);
	}

	// decrease clean
	if ((ticks & MASK_CLEAN) == MASK_CLEAN)
	{
		u8 clean = PetClean();
		if (clean > 0) PetSetClean(clean-1);
	}

	// increase/decrease rest
	if ((ticks & MASK_REST) == MASK_REST)
	{
		u8 rest = PetRest();
		if (sleep)
		{
			if (rest < STATEMAX) PetSetRest(rest+1);
		}
		else
		{
			if (rest > 0) PetSetRest(rest-1);
		}
	}

	// decrease health
	if ((ticks & MASK_HEALTH) == MASK_HEALTH)
	{
		// health penalties
		if (	(PetFeed() < STATEMAX/4) ||	// hungry
			(PetRest() < STATEMAX/4) ||	// tired
			(PetHappy() < STATEMAX/4) ||	// unhappy
			(PetClean() < STATEMAX/4))	// clean
		{
			u8 health = PetHealth();
			if (health > 0) PetSetHealth(health-1);
		}
	}

	// save RAM to flash, if age changed (to update flash only 1x per day)
	if (PetAge() != FlashData.pet[0].state.age) SaveRamFlash();
}

