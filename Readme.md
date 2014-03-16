# Introduction

  This is basic OpenGL based demo application.

# Overview

This demo application was originally developed in C, around 1999 with OpenGL 1.1 and targed Windows systems.

I have recoded it as a means to keep myself updated with the C++11/C++14 changes and how to use to target Android systems with NDK and Open GL ES.

The graphics were kept as simple as the original one, because the main goal was to learn the said technologies and not to write a game engine.

# Dependencies

This code requires the following libraries:

- GLM (a C++ math library)
- SDL (a C portable library for multimedia applications)
- GLEW (OpenGL extensions loader, only required on Windows systems)

# Building

## Windows

### Setting up

For building TownGL on Windows, a few steps are required:

1. Download the binary relase of SDL for Windows from http://www.libsdl.org/
3. Copy the SDL binaries into _libs_ location
4. Download GLM from http://glm.g-truc.net
6. Copy the GLM source code into _libs_ location
7. Download the binary relase of GLEW for Windows from http://glew.sourceforge.net/
8. Copy the GLEW binaries into _libs_ location

*Note:* I only tested with 32bit binaries so far. In principle 64bit should work as well, but it hasn't been tested.

### Building

1. Open the Visual Studio 2013 project file
2. Build the solution

## Android

### Setting up

For building TownGL with the NDK, a few steps are required:

1. Download SDL from http://www.libsdl.org/
2. Expand the package contents
3. Copy the full SDL source code into _src/jni_ location
4. Copy the Java code from _android-project/src_ into _src_
5. Download GLM from http://glm.g-truc.net
6. Copy GLM source code into _src/jni_ location

### Building on the command line

1. Make sure ndk-build is on the PATH
2. ant compile

### Building with Eclipse/ADT/CDT

1. Start Eclipse;
2. Use _import existing project_ for adding the project into the workspace;
3. Verify that you have a valid path for the NDK at _Preferences->Android->NDK_ settings panel;
4. Switch to the CDT perspective
5. Build the project
6. Finally deploy it either to the emulator or plugged device

Since the demo makes use of OpenGL ES, it will only work in the emulator if the requirements are fullfiled:

- HAXM is installed
- The emulator is configured with an Intel CPU
- The image has graphics accelaration via host GPU enabled

# License

This code is under the GPL v2 license.