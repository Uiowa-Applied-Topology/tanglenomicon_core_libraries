```mermaid
classDiagram

note_PD --|> notation 
note_PD_config_t --|> note_t 
note_PD *-- note_PD_config_t

class note_PD_config_t {
<<struct>>
}

class notation{
<<interface>>
}

class note_t {
<<interface>>
}


```
## Language

C

## Implements 

* [Interface](Notations/Interface.md)

## Used by 

* [Rational](Generators/Rational.md)
* [Pd-To-Conway](Translators/Pd-To-Conway.md)

## Functionality
