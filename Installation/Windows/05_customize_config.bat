@echo off
set CONFIG="..\..\Sketches\SenseBoxMcu\SketchConfig.h"
if exist %CONFIG% (
    notepad %CONFIG%
) else (
    copy "%CONFIG%.template" %CONFIG%
    notepad %CONFIG%
)