@echo off
set CONFIG="..\..\Sketches\SenseBoxMcu\arduino_secrets.h"
if exist %CONFIG% (
    notepad %CONFIG%
) else (
    copy "%CONFIG%.template" %CONFIG%
    notepad %CONFIG%
)