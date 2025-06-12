# Unit Description: Twist Vector Notation

## Class Diagram

```mermaid
classDiagram
    note_tv --|> notation
    note_tv *-- note_tv_t

    class note_tv_t {
        <<struct>>
        uint8_t twist_vec[MAX_CN]
        size_t tv_length[MAX_CN]
    }

    class notation {
        <<interface>>
    }
```

## Language

C

## Implements

- [Notations Interface](../../notation-interface.md)

## Uses

The twist vector notation component does not use any other components.

## External Libraries

The twist vector notation component does not use any external libraries.

## Functionality

### Public Structures

#### Notation structure

The interface structure contains an array of integers, each entry of the twist
vector is stored into the array. The indexing of the array is as in
@se-tv-math-index.

```{math}
:label: se-tv-math-index
 [ x_n\ x_{n-1}\ \cdots\ x_0]\to \begin{array}{|c|c|c|c|} \hline
\text{0x0000}& & &\text{0x0000}+n\cdot \text{size\_t}\\\hline x_0&\cdots &
x_{n-1} &x_n\\ \hline \end{array}
```

### Public Functions

#### Decode Function

The decode function takes in the linearized string form of the twist vector and
encodes it as a `note_tv_t`.

This process is described in the following state machines:

```mermaid
stateDiagram-v2
    state "Init" as vj
    state "• tv_index to 0" as vj
    state "• str_end to point at end of input string" as vj
    state "Move input str pointer past opening [" as rl
    state "Read int from imput string" as rc
    state "Increment tv_index" as itvi
    state "Reverse order of list" as ro
    state if_end_of_string <<choice>>
    [*] --> vj
    vj --> rl
    rl --> rc
    rc --> itvi
    itvi --> if_end_of_string
    if_end_of_string --> rc: is not end of string
    if_end_of_string --> ro: is end of sting
    ro-->[*]

```

#### Encode Function

The encode function takes in a `note_tv_t` and encodes it into the linearized
string form of the twist vector.

```mermaid
stateDiagram-v2
    state "Init" as vj
    state "• local_str_buffer[MAX_CN]" as vj
    state "• local_str_ptr to beginning of str" as vj
    state "• interator i to tv_length" as vj
    state "Place opening [" as pob
    state "Place closing ]" as pcb
    state "Place space" as ps
    state "Place int into string" as piis
    state "Decrement i" as di
    state "Move local_str_ptr forward" as mspf
    state "Convert int to string" as cits
    state if_tv_empty <<choice>>

    [*] --> vj
    vj --> pob
    pob --> mspf
    mspf --> if_tv_empty
    if_tv_empty --> cits: i is not zero
    cits --> piis
    piis --> ps
    ps --> di
    di --> mspf
    if_tv_empty --> pcb: i is zero

    pcb --> [*]
```

### Private Functions decode path

#### Twist Vector Reverse

This function reverses the order of the twist vector storage array. They makes
the increment read order match the theoretical indexing of the twist vector.

```mermaid
stateDiagram-v2
    state "Init" as rn
    state "• left_p to start of array" as rn
    state "• right_p to end of array" as rn
    state "Set placeholder to left_p int" as spl
    state "Set left_p to right_p int" as slr
    state "Set right_p to placeholder int" as srp
    state "Increment left_p " as ilp
    state "Decrement right_p " as drp
    state if_at_middle <<choice>>

    [*] --> rn
    rn --> if_at_middle
    if_at_middle --> spl: If left_p != right_p
    spl --> slr
    slr --> srp
    srp --> ilp
    ilp --> drp
    drp --> if_at_middle
    if_at_middle --> [*]: If left_p == right_p

```

## Validation

### Decode interface

```{test-card} Valid string representing a twist vector

A valid string representing a twist vector is fed to the function.

**Inputs:**

- A valid string representing a twist vector.

**Expected Output:**

A correct and valid decoding of the string


```

### Encode interface

```{test-card} Valid twist vector

A valid twist vector is fed to the function.

**Inputs:**

- A correct and valid twist vector.

**Expected Output:**

A valid string representing the twist vector.

```

## Doxygen Documentation

```{doxygenfile} notation_tv.h

```

```{doxygenfile} notation_tv.c

```

## Bibliography

```{bibliography}
   :filter: docname in docnames
```

```{raw} latex
    \newpage
```
