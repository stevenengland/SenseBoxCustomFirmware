# Custom SenseBox Firmware

## Intro
This repo contains modularized firmware for the public science project [SenseBox](https://sensebox.de/) that I need for my personal projects.

## Using an IDE
The Arduino IDE lacks a lot of features. Therefore all the .ino files in this project are meant to be edited outside of the Arduino IDE. Please refer to guides telling you how to set
up your specific IDE how to do this or read the sections below for working solutions I can tell you. 

The most important part is to include all the Arduino header files/libraries so that you won't earn all the compiler errors
telling you that specific #include commands cannot find the file mentioned (like #include "Arduino.h"). 
No matter what solution you prefer you need either an Arduino IDE running on your machine or the Arduino CLI as an alternative that provide you with the headers and libs.

### CMake based solution for every IDE
**DISCLAIMER:** This solution is the one that should work with every IDE that is capable of dealing with CMake. 
But this solution should be seen as a workaround because it uses concepts like GLOBbing and EXLUDE_FROM_ALLing. It works nice so far but can lead into trouble in the future. We will see ;)

In order to use this solution you need to create a file called arduino.ini within the Configurations directory. 
That file won't be picked up by git. 
Add the following lines with your environments Arduino paths to it and you're done:

```
# ./Configurations/arduino.ini
ArduinoUserPackagesDir=C:/Users/steven/AppData/Local/Arduino15/packages
ArduinoUserLibrariesDir=C:/Users/steven/Documents/Arduino/libraries
```

### Visual Studio Code specific solution
In your project directory edit or create the .vscode/c_cpp_properties.json
It should ultimately look something like this:
```
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "C:/Users/steven/AppData/Local/Arduino15/packages/**",
                "C:/Users/steven/Documents/Arduino/libraries/**"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "windowsSdkVersion": "10.0.19041.0",
            "compilerPath": "C:/Program Files (x86)/Microsoft Visual Studio/2019/Enterprise/VC/Tools/MSVC/14.28.29910/bin/Hostx64/x64/cl.exe",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "windows-msvc-x64",
            "configurationProvider": "ms-vscode.cmake-tools"
        }
    ],
    "version": 4
}
```
The most important part is the second include path with the wildcards at the end.

## Handling .ino Extension
It may help you to tell your favorite IDE to handle .ino files as c++ files.

+ Visual Studio: Tools > Options > Text Editor > File Extension > ino : Microsoft Visual C++
+ Visual Studio Code: global settings.json > files.associations > "*.ino": "cpp" 

## Build the .ino Files

### Arduino Secrets
In order to build some of the examples you have to look if the sketch directory contains a **arduino_secrets.h.template** file. Please make a copy of that file and rename it to **arduino_secrets.h** and replace the contents with real world items.
The template file is used for source control and must be kept. The renamed copy will be ignored by the source control system (git).

### Arduino CLI
The Arduino IDE is a little bit of a mess when it comes to path inclusion. So the build must be performed with the new Arduino CLI.
Please add the arduino-cli executable to your OSes PATH. That is needed if you build the project because all the .ino files will be compiled as part of the testing strategy.
After installation of Arduino CLI configure it for the SenseBox:

```
arduino-cli core install arduino:samd
arduino-cli --additional-urls https://raw.githubusercontent.com/sensebox/senseBoxMCU-core/master/package_sensebox_index.json core install sensebox:samd
```

Afterwards builds can be done via commands like this:

```
arduino-cli compile --fqbn sensebox:samd:sb --libraries "/path/to/the/libraries" "/path/to/your/sketch" 
```
You can also have a look at the output of the build process where the actual used compile commands are listed.

### Additional Libraries
Following third party libraries are used:
```
arduino-cli.exe lib install "Adafruit SleepyDog Library"
```

# Credits
The testable project structure is following the idea seen here: 
[How to write testable C++ for Arduino](https://youtu.be/jCLgqaXS6Gg)