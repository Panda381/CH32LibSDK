
// ****************************************************************************
//
//                               Power Control
//
// ****************************************************************************

#include "../_include.h"

#if USE_PWR		// 1=use power control

// Enter sleep mode, use WFI wakeup
void PWR_EnterSleep()
{
	// select Sleep mode
	PWR_PDDSSleep();

	// set Sleep mode
	NVIC_Sleep();

	// wait
	wfi_ins();
}

// Enter sleep mode, use WFE wakeup
void PWR_EnterSleepWfe()
{
	// select Sleep mode
	PWR_PDDSSleep();

	// set Sleep mode
	NVIC_Sleep();

	// wait
	wfe();
}

// Enter standby mode, use WFI wakeup
void PWR_EnterStandby()
{
	// select Standby mode
	PWR_PDDSStandby();

	// set DeepSleep mode
	NVIC_DeepSleep();

	// wait
	wfi_ins();

	// return to normal mode
	NVIC_Sleep();
}

// Enter standby mode, use WFE wakeup
void PWR_EnterStandbyWfe()
{
	// select Standby mode
	PWR_PDDSStandby();

	// set DeepSleep mode
	NVIC_DeepSleep();

	// wait
	wfe();

	// return to normal mode
	NVIC_Sleep();
}

#endif // USE_PWR
