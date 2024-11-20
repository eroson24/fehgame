# Proteus Simulator Libraries

This repository contains the libraries used for the Proteus Simulator, along with the Makefile to build student projects in the parent directory.

## Template

We distribute a [template](https://u.osu.edu/fehproteus/vs-code-environment/compiling-and-running-a-project/compiling-a-project-on-the-proteus-simulator/) to students that pulls from this directory on each `make`. Any Makefile that triggers the default target (`all`) in this directory's makefile should work, however.

## Assumptions

We assume that student source code will be in a *parent directory* of these libraries. That is, we expect a student's file structure to look something like

    .
    ├── main.cpp                # The main program file does not need to be named `main.cpp`, but it need to have a `main` function.
    ├── Makefile                # This Makefile should trigger the default target in this directory's Makefile
    ├── simulator_libraries     # This directory, which includes the libraries, like FEHLCD, FEHImages, etc.
    │   ├── Makefile            # The Makefile that will compile and link all student source in `..`, creating the game executable in `..`
    │   ├── ...
    ├── Foo                     # Students can create an arbitrary file structure for their project source code, within the `..` directory.
    │   ├── bar.cpp
    │   ├── bar.h               # They will need to be sure, however, to include the header files, e.g. `#include "bar.h"`.
    └── ...

Copyright 2022 Fundamentals of Engineering for Honors Program, Department of Engineering Education, The Ohio State University.
