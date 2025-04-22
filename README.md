<link
  href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.5.1/css/all.min.css"
  rel="stylesheet"
/>

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

# Tanglenomicon Core Libraries

The Tanglenomicon core libraries consists of a collection of libraries for
computation and generation of knot/tangle data. Each library should be
considered its own project with its own life-cycle however libraries are loosely
coupled by a common cmake interface.

The libraries found here are primarily C/C++ and is expected to make a selection
between the two, C modules are expected to be C++ linkable. There's no target OS
but ubuntu linux with nix is the CI OS. Each library will adhere to a common
design which allows them flexibility and platform and language agnosticism. The
design allows a library, maybe "calculate jones polynomial", to be runnable in a
jupyter notebook during undergraduate knot theory class, or wrapped in matlab
interfaces for scientific computing, or on a university cluster for high
performance use cases.

We're targeting a "write once deploy anywhere" design.

# Planning

## Tasks

Tasks will be decomposed per library. Issues/bugs will be tracked per report,
combining where it makes sense.

## Version control

Version control will be git based with research git as the source of truth. Work
items will have a branch per work item. Merging a work item will be managed by
Gitlab merge requests.

### Release Schedule

A release will be created at the completion of each feature lifecycle.

#### Release Tagging

The project adopts [semantic versioning](https://semver.org) for version labels.

```
vMAJOR.MINOR.PATCH
```

Since a release is created for every feature implemented the project version may
look odd `v0.20.0` this is OKAY.

```{note}
It is required that every feature module in the project maintian it's own sematic
versioning. It is suggusted to check for compatability of used libraries at compile time.
```

## Software Lifecycle

We're taking a feature centric waterfall approach with design, implementation,
integration, and testing phases.

Feature centric we mean work on one feature at a time, some examples for feature
scope are rational tangle generation, JSON storage, or Conway notation.

Waterfall means we complete a full life cycle for each library.

```mermaid
flowchart TD
    Requirements --> Design
    Design --> Implementation
    Implementation --> UT[Unit Testing]
    UT --> IT["Integration Testing"]
```

This methodology will allow us to have high traceability, meaning we can track
our features through the development cycle. This allows us to justify every
decision we made in the process.

## Project Structure

Project structure will follow a fairly "normal" project structure as follows:

```
📦tanglenomicon_core
 ┣ 📂.github
 ┃ ┗ 📂workflows
 ┃ ┃ ┗ 📜\<github workflows\>
 ┣ 📂data
 ┃ ┗ 📜\<Static data files\>
 ┣ 📂docs
 ┃ ┣ 📜\<Sphinx files\>
 ┃ ┗ 📜Doxyfile
 ┣ 📂libraries \< external libraries\>
 ┃ ┗ 📜\<C/C++ libraries data files\>
 ┣ 📂misc
 ┃ ┗ 📜\< Single use tooling\>
 ┣ 📂source
 ┃ ┗  📂\<Module\>
 ┃    ┣ 📂source
 ┃    ┃ ┗ 📜\<Module Source Files\>
 ┃    ┣ 📂test
 ┃    ┃ ┗ 📜\<Module unit test Files\>
 ┃    ┣ 📜use-case.md
 ┃    ┗ 📜unit-description.md
 ┣ 📂tests
 ┃ ┣ 📂results
 ┃ ┃ ┗ 📜.gitkeep
 ┃ ┗ 📂integration_tests
 ┃   ┗ 📂 \<integration Test Suites\>
 ┣ 📜.clang-format
 ┣ 📜.clang-tidy
 ┣ 📜.gitignore
 ┣ 📜CMakeLists.txt
 ┣ 📜CMakeSettings.json
 ┣ 📜README.md
 ┗ 📜requirements.txt
```

## Define a Unit: A unit in this project shall be a library

## Quality

This repository is a collection of libraries for The Tanglenomicon project. This
requires a high level of quality, with the primary design goal of libraries
never failing in an undetectable way.

### Unit testing

Every unit is expected to have a unit test suite. Unit test suites are expected
to flex every public interface of their unit. Code coverage is optional but
encouraged.

### Integration testing

Integration tests are expected for every bundled "runner".

## Requirements

Since this repository contains a collection of libraries, this section will
describe the high-level design for types of libraries/common use cases.

### Functional Requirements

```mermaid
flowchart LR
    Runner
    subgraph "Runnables"
        Generator
        Computation
    end
    subgraph "Data Wranglers"
        Notation
        Storage
    end
    Runner -->|Runs| Generator
    Runner -->|Runs| Computation
    Generator -->|Uses| Notation
    Computation -->|Uses| Notation
    Generator -->|Uses| Storage
    Computation -->|Uses| Storage


```

General use case descriptions of each of these blocks can be found here:

-   [Runners](/use_cases/runners/index.md)
-   [Generators](/use_cases/generators/index.md)
-   [Computations](/use_cases/computations/index.md)
-   [Notations](/use_cases/notations/index.md)
-   [Storage](/use_cases/storage/index.md)

A functional description for individual libraries are phrased in the following
use cases:

```{toctree}
:titlesonly:
use_cases/index.md
```

### Non-functional Requirements

Not applicable.

## Technologies

### Languages/Frameworks

The runnable and data wrangler libraries will be written in C/C++ using clang
for compiling and cmake as a build system. The runners are written with various
tooling including C/C++, python, and javascript.

Unit testing of runnable and data wrangler libraries will use the
[Unity](http://www.throwtheswitch.org/unity) and
[Cmock](http://www.throwtheswitch.org/cmock) libraries for unity testing. Test
indexing is handled by
[ctest](https://cmake.org/cmake/help/latest/module/CTest.html).

Integration testing of runners is handled by whatever standard test tooling is
appropriate.

#### Code Style Guide

The C/C++ code in this repository shall be formatted by the bundled clang-format
configuration. Doxygen comments are expected to be formatted.

Python code in this repository shall be formatted with black.

### Tools

-   git
-   vscode
-   clion
-   mermaid.js
-   Unity
-   clang
-   cmake
-   ctest
-   doxygen
-   Cmock
-   python3
-   MyStmd
-   sphinx
-   pytest

# Design and Documentation

C/C++ code is documented with [Doxygen](https://www.doxygen.nl/), the doxygen
comments shall be parsed and output as xml. General documentation shall be
recorded as markdown files in each module's directory. Documentation shall be
aggregated using the [sphinx](https://www.sphinx-doc.org/en/master/) framework.
Sphinx shall then use [breathe](https://github.com/breathe-doc/breathe) to parse
doxygen xml into the general documentation.

## Colors

Diagrams included in documentation for features (use case and unit descriptions)
is expected to use the [COLORS](https://clrs.cc) color palette.

```
/* Colors */
Navy    : #001F3F
Blue    : #0074D9
Aqua    : #7FDBFF
Teal    : #39CCCC
Olive   : #3D9970
Green   : #2ECC40
Lime    : #01FF70
Yellow  : #FFDC00
Orange  : #FF851B
Red     : #FF4136
Fuchsia : #F012BE
Purple  : #B10DC9
Maroon  : #85144B
White   : #FFFFFF
Silver  : #DDDDDD
Gray    : #AAAAAA
Black   : #111111
```

## Units

Unit descriptions are as follows:

```{toctree}
:titlesonly:
unit_description/index.md
```
