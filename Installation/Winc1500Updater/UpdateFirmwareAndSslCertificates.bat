@echo off
rem set /p PORT="An welchem Port ist die Sensebox angeschlossen? "
for /D %%I in ("%USERPROFILE%\Arduino15\packages\arduino\tools\bossac\1*") do "%%~I\bossac.exe"
echo "%I%"
rem FirmwareUploader --model winc --flasher FirmwareUpdater.SenseBoxMcuV2.ino.bin --firmware firmware\19.6.1_m2m_aio_3a0.bin --port %PORT% --retries 1 --programmer {runtime.tools.bossac.path}/bossac.exe
@pause