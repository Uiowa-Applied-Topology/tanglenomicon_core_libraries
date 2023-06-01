```mermaid
classDiagram

note_pd --|> notation 
note_pd *-- note_pd_t

class note_pd_t {
<<struct>>
}


class notation {
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
