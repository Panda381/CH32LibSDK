@echo off
del OUT\*.wav
for %%f in (IN\*.mp3) do ffmpeg -i "%%f" -y -c:a adpcm_ima_wav -ar 22050 -ac 2 -map_metadata -1 "OUT\%%~nf.wav"
