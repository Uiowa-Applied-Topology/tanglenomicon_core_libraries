---
note: Treat this file as if it was in the root of the docs directory.
---

<link
  href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.5.1/css/all.min.css"
  rel="stylesheet"
/>

# Overview and Philosophy

The tanglenomicon describes a tool for computing on tangles. The design is
indented to allow flexibility, that is to be platform and language agnostic. We
want a feature, maybe "calculate jones polynomial", to be runnable in a jupyter
notebook during undergraduate knot theory class, or wrapped in matlab interfaces
for scientific computing, or on a university cluster for high performance use
cases. We're targeting a "write once deploy anywhere" design.

While the design is platform and language agnostic the core implementation for
the tanglenomicon project is written in a mix of C and C++. Each module is
expected to make a selection, C modules are expected to be C++ linkable. There's
no target system but ubuntu linux is the CI OS.

# Tanglenomicon

## Infra

### Build

#### Compiler

The project primarily targets clang. The CI uses both clang and GNU compiler.

#### Make System

The project uses [cmake](https://cmake.org/) as it's make system.

### Testing

Tests are run by [ctest](https://cmake.org/cmake/help/latest/module/CTest.html).

#### Unit

The project uses [Unity](http://www.throwtheswitch.org/unity)
and [Cmock](http://www.throwtheswitch.org/cmock) for unity testing.

#### Integration

Integration/system testing is done
with [pytest](https://docs.pytest.org/en/7.3.x/).

### Process



##### Version Control (VC)

The project uses git as it's primary VC system. We use git pull requests for
merging onto the ```main```. Tests are expected to be passing for a pull request
to be approved.

##### Continuous Integration (CI)

The project uses GitHub actions for CI.

##### Style

A style format is defined as a clang format file. Files are checked against
clang.tidy on pull request.

##### Directory Map

```
📦tanglenomicon_core
 ┣ 📂.github
 ┃ ┗ 📂workflows
 ┃ ┃ ┗ \<github workflows\>
 ┣ 📂data
 ┃ ┗ \<Static data files\>
 ┣ 📂docs
 ┃ ┣ 📂design
 ┃ ┃ ┗ \<Design Files\>
 ┃ ┗ 📜Doxyfile
 ┣ 📂libraries
 ┃ ┗ \<C/C++ libraries data files\>
 ┣ 📂source
 ┃ ┗  📂\<Module\>
 ┃    ┗ \<Module Source Files\>
 ┣ 📂tests
 ┃ ┣ 📂results
 ┃ ┃ ┗ 📜.gitkeep
 ┃ ┗ 📂unit_tests
 ┃   ┣ 📂framework
 ┃   ┃ ┗ \<Unit Test Framework Source\>
 ┃   ┗ 📂 \<Unit Test Suites\>
 ┃     ┗ 📂\<Module Unit Test\>
 ┃        ┗ \<Module Unit Test Source\>
 ┣ 📜.clang-format
 ┣ 📜.clang-tidy
 ┣ 📜.gitignore
 ┣ 📜CMakeLists.txt
 ┣ 📜CMakeSettings.json
 ┣ 📜README.md
 ┗ 📜requirements.txt
```

### Documentation

#### Code



#### Design

This document uses [markdown](https://www.markdownguide.org/) files in
an [obsidian](https://obsidian.md/) vault. Diagrams are written
as [mermaid.js](https://mermaid.js.org/).

#### Generation

Doxygen comments are parsed and output as xml. Python docstrings are parsed
automatically by [sphinx](https://www.sphinx-doc.org/en/master/). Sphinx then
uses [breathe](https://github.com/breathe-doc/breathe) to parse doxygen xml into
a sphinx documents. C modules are expected to link to their design .md file in
their header @file block.

Tooling as described
in [here](https://devblogs.microsoft.com/cppblog/clear-functional-c-documentation-with-sphinx-breathe-doxygen-cmake/)

### Deployment

#### Web Server

We will use Nginx as the webserver of the UIowa deployment.

#### Frontend Framework

We will use HTML5/CSS3 with the tailwind framework along side jquery for the
frontend frameworks for the UIowa deployment.

#### Backend Framework

We will use Python with the Flask framework for the UIowa deployment.

#### Database System

The design doesn't couple a specific DBS/storage solution to the implementation.
For the Iowa deployment of the tanglenomicon we will be using MongoDB as the DBS
for the UIowa deployment.

## Block Diagram

```mermaid
flowchart LR
    Runner
    subgraph "Runnables"
        Generator
        Translator
        Computation
    end
    subgraph "Data Wranglers"
        Notation
        Storage
    end
    Runner -->|Runs| Generator
    Runner -->|Runs| Computation
    Runner -->|Runs| Translator
    Translator -->|Uses| Notation
    Generator -->|Uses| Notation
    Computation -->|Uses| Notation
    Generator -->|Uses| Storage
    Computation -->|Uses| Storage
    Translator -->|Uses| Storage

```

### Runners

```{toctree}
:maxdepth: 3
design/runners/*
```

### Module types

#### Runnables

##### Generators

```{toctree}
:maxdepth: 3
design/generators/index
```

##### Computation

```{toctree}
:maxdepth: 3
design/computations/index
```

##### Translators

```{toctree}
:maxdepth: 3
design/translators/index
```

#### Data wranglers

##### Notations

```{toctree}
:maxdepth: 3
design/notations/index
```

##### Storage

```{toctree}
:maxdepth: 3
design/storage/index
```