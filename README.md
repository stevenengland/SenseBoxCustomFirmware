# Custom SenseBox Firmware

## Intro
This repo contains modularized firmware for the public science project [SenseBox](https://sensebox.de/) that I need for my personal projects.

## Using an IDE
The Arduino IDE lacks a lot of features. Therefore all the .ino files are meant to be edited outside of Arduino IDE. Please refer to guides telling you how to set
up your IDE. The most important part is to include all the Arduino header files/libraries so that you won't earn all the compiler errors
telling you that specific #include commands cannot find the file mentioned.

### Visual Studio Code
You need either an Arduino IDE running on your machine or the Arduino CLI as an alternative that provide you with the headers and libs.
In your project directory edit or create the .vscode/
It should ultimately look something like this:
```
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "C:/Users/steven/AppData/Local/Arduino15/packages/**"
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

## Build the .ino Files
The Arduino IDE is a little bit of a mess when it comes to path inclusion. So the build must be performed with the new Arduino CLI.
Please add the arduino-cli executable to your OSes PATH. That is needed if you build the project because all the .ino files will be compiled as part of the testing strategy.
After installation of Arduino CLI configure it for the SenseBox:

```
arduino-cli core install arduino:samd
arduino-cli --additional-urls https://raw.githubusercontent.com/sensebox/senseBoxMCU-core/master/package_sensebox_index.json core install sensebox:samd
```

Afterwards builds can be done via commands like this:

```
arduino-cli compile --fqbn sensebox:samd --libraries "/path/to/the/libraries" "/path/to/your/sketch" 
```

# Credits
The testable project structure is following the idea seen here: 
[How to write testable C++ for Arduino](https://youtu.be/jCLgqaXS6Gg)