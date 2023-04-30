

```mermaid
classDiagram
notation *-- note_t
class notation{
<<interface>>
+ note_t parse(string)
+ string encode(note_t)
}

class note_t {
<<struct>>
}

```

## Brief

This interface describes a generic notation module. A notation module sits between a storage module and an upper layer (Computation, Generator, etc.). Notation module will define a struct that encodes the notational data and two IO functions. 