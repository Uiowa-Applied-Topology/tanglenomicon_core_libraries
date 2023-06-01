```mermaid
classDiagram

note_tv --|> notation 
note_tv *-- note_tv_t

class note_tv_t {
<<struct>>
List~uint8_t~ twist_vec
}


class notation {
<<interface>>
}


```

## Description 
- [ ] TODO Description

## Language

C

## Implements 

* [Interface](Notations/Interface.md)

## Used by 

* [Rational](Generators/Rational.md)
* [Pd-To-Conway](Translators/Pd-To-Conway.md)

## Functionality
- [ ] TODO Functionality