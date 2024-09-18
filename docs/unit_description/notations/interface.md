# @@@TODO Unit Description: Notation Interface


```mermaid
classDiagram
    notation *-- note_t
    class notation {
        <<interface>>
        + note_t encode(string)
        + string decode(note_t)
    }

    class note_t {
        <<struct>>
    }

```

## C Style Interface
```mermaid
classDiagram
notation *-- note_t
class notation{
<<interface>>
+ int decode(note_t*,string*)
+ int encode(string*,note_t*)
}

class note_t {
<<struct>>
}

```

## Brief

This interface describes a generic notation module. A notation module sits between a storage module and an upper layer (Computation, Generator, etc.). Notation module will define a struct that encodes the notational data and two IO functions.

The encode/decode operations are taken from the perspective of the database.

### Encoding

Takes a data structure and encodes it as it's string representation.

### Decoding

Takes a string and decodes it as it's data structure representation.
