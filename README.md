# Custom SenseBox Firmware

## Intro
This repo contains modularized firmware for the public science project [SenseBox](https://sensebox.de/) that I need for my personal projects.

## Using a different IDE than Arduino IDE
The Arduino IDE lacks a lot of features. Therefore all the .ino files are meant to be edited outside of Arduino IDE. Please refer to guides telling you how to set
up your IDE. The most important part is to include all the Arduino header files/libraries so that you won't earn all the compiler errors
telling you that specific #include commands cannot find the file mentioned.

## Build the .ino Files
The Arduino IDE is a little bit of a mess when it comes to path inclusion. So the build must be performed with the new Arduino CLI.
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