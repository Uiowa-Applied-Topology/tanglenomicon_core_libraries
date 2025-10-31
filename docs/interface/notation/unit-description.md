# Unit Description

## Class Diagram

```mermaid
classDiagram
    notation *-- note_t
    class notation {
        <<interface>>
        + note_t decode(string)
        + string encode(note_t)
    }

    class note_t {
        <<struct>>
    }

```

## Functionality

### Public Structures

#### Notation Data Structure

This is the primary data structure for a notation component. This data structure defines and stores
the computational representation of a knot notation.

### Public Functions

#### Encode Function

The encode function takes in the string representation of a knot notation, processes the string and
stores the computational representation into a notation data structure.

#### Decode Function

The decode function takes in a computational representation of a notation data structure, and
processes it into a string representation of a knot notation.
