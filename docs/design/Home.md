# Overview

The tanglenomicon describes a tool for computing on tangles. The design is indented to allow flexibility in target user interface. The project is written in a mix of C and C++, each module is expected to make a selection, C modules are expected to be C++ linkable. There's no target system but ubuntu linux is the CI OS.  

## Infra 

### Build

#### Compiler

The project primarily targets clang. The CI uses both clang and GNU compiler.

#### Make System 

The project uses [cmake](https://cmake.org/) as it's make system. 

### Testing

Tests are run by [ctest](https://cmake.org/cmake/help/latest/module/CTest.html).

#### Unit

The project uses [Unity](http://www.throwtheswitch.org/unity) and [Cmock](http://www.throwtheswitch.org/cmock) for unity testing. 

#### Integration 

Integration/system testing is done with [pytest](https://docs.pytest.org/en/7.3.x/). 

### Process 

##### VC

The project uses git as it's primary VC system. We use git pull requests for merging onto the ```main```. Tests are expected to be passing for a pull request to be approved. 

##### CI

The project uses GitHub actions for CI. 

##### Style 

A style format is defined as a clang format file. Files are checked against clang.tidy on pull request.

##### Directory Map 

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
 ┃   ┣ 📂 \<Module Unit Test\> 
 ┃     ┗ \<Module Unit Test Source\> 
 ┣ 📜.clang-format  
 ┣ 📜.clang-tidy  
 ┣ 📜.gitignore  
 ┣ 📜CMakeLists.txt  
 ┣ 📜CMakeSettings.json  
 ┣ 📜README.md  
 ┗ 📜requirements.txt


### Documentation 

#### Code

C code is documented with [Doxygen](https://www.doxygen.nl/) comments. Python is documented with numpy style docstrings. 

#### Design 

This document uses [markdown](https://www.markdownguide.org/) files in an [obsidian](https://obsidian.md/) vault. Diagrams are written as [mermaid.js](https://mermaid.js.org/). 

#### Generation 

Doxygen comments are parsed and output as xml. Python docstrings are parsed automatically by [sphinx](https://www.sphinx-doc.org/en/master/). Sphinx then uses [breathe](https://github.com/breathe-doc/breathe) to parse doxygen xml into a sphinx documents. C modules are expected to link to their design .md file in their header @file block. 

Tooling as described in [here](https://devblogs.microsoft.com/cppblog/clear-functional-c-documentation-with-sphinx-breathe-doxygen-cmake/)


# Block Er Diagram


```mermaid
erDiagram
    Runner ||--|{ Generator : Runs
    Runner ||--|{ Computation : Runs
    Runner ||--|{ Translator : Runs
		Generator ||--||Notation : Uses
		Computation ||--||Notation : Uses
		Translator ||--|{ Notation : ""
		Generator ||--||Storage : Uses
		Computation||--||Storage : Uses
		Translator ||--|| Storage : Uses
```


## Runners

A runner is a human/machine interface layer. This abstracts the routines in lower layers for a user to interact with. This could be a CLI interface, python bindings, a Mathematica wrapper, etc. 

### Definitions 

- [CLI](Runners/CLI.md)

## Module types

### Runnables 

#### Generators 

Generators create new data of a defined type. These might look like a module that generates rational tangles up to a crossing number or tangle closures of a specific type. They may use one or more Computations, Notations, or Translators. 

#### Computation 

Computations compute a value for a given data. These might look like computing a polynomial of a link, or a computing the writhe of a tangle. 

#### Translators

Translators define a conversion between two Notations. An example might be a translator from [PD](Notations/PD.md) to [Conway](Notations/Conway.md) notation or it's opposite Conway to PD.

### Data wranglers 

#### Notations 

Notations define a notational convention for a link/tangle. They describe a method for converting to and from a string representation of a link/tangle and struct describing that link/tangle.


#### Storage

A storage module defines a storage interface for the application. The main inter-module type is string
and the calling module is responsible for en/decoding the string. The interfaces are defined with serializable storage in mind. 


