# Use Case: Notation Interface

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

The C interface takes the source $\to$ destination convention in the arguments.

```mermaid
classDiagram
notation *-- note_t
class notation{
<<interface>>
+ int encode(note_t*,string*)
+ int decode(string*,note_t*)
}

class note_t {
<<struct>>
}

```

## Brief

This interface describes a generic notation module. A notation module sits
between a storage module and an upper layer (Computation, Generator, etc.).
Notation module will define a struct that encodes the notational data and two IO
functions.

### Encoding

Takes a data structure and encodes it as its string representation.

### Decoding

Takes a string and decodes it as its data structure representation.

```{raw} latex
    \newpage
```
