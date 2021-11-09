@echo off
set /p PORT="An welchem Port ist die Sensebox angeschlossen? "
arduino-cli compile --fqbn sensebox:samd:sb --libraries %CD%/../../Components/ -u -p %PORT% %CD%/../../Sketches/SenseBoxMcu
@pause