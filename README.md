# chip8_Cpp
# Table of contents

  * [Introduction](#introduction)
  * [Dependencies for Running Locally](#Dependencies for Running Locally)
  * [Basic Build Instructions](#Basic Build Instructions)
  * [Showcase](#Showcase)
  * [Features](#features)
  * [Tests](#tests)

## Introduction

A chip8 interpreter coded in C++

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
```bash
https://github.com/Infrx/chip8_Cpp
```
3. Make a build directory in the top level directory:
```bash
mkdir build && cd build
```
3. Compile:
```bash
cmake .. & make
```
5. Run it:
```bash
./chip8 brix.ch8
```
## Showcase



## Features

 - [X] All basic chip8 instructions 
 - [X] Working hexpad 
 - [X] Audio
 - [X] Quirks
       
## Tests
### Timendus Tests:

- [X] CHIP-8 splash screen
- [X] IBM logo
- [X] Corax+ opcode test
- [X] Flags test
- [X] Quirks test
- [X] Keypad test
- [X] Beep test
- [ ] Scrolling test (Not applicable to CHIP8)

### Other Tests

- [X] Out of bonds tests

## To do list
* [ ] ~~Implement function pointers~~ (switch case method might be better for implementing cycle accuracy in the future)
* [ ] Add showcase section in readme
* [X] ~~Implement CHIP8 quirks~~
