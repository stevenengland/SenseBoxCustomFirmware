@echo off
set /p PORT="An welchem Port ist die Sensebox angeschlossen? "
arduino-cli compile --fqbn sensebox:samd:sb --libraries ./source/Components/ -u -p %PORT% %CD%/sources/Sketches/SenseBoxMcu