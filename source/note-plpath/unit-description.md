---
date: 2024-09-18
authors:
    - Joe Starr
contact: support@joe-starr.com
abstract: A unit description for the arborescent planar tangle tree notation.
---

# Unit Description

```mermaid
classDiagram
    note_plpath --|> notation
    note_plpath *-- note_plpath_t
    note_plpath_t *-- note_plpath_segment_t
    note_plpath_t *-- note_plpath_point_buffer_t
    note_plpath_point_buffer_t *-- note_plpath_point_t
    class note_plpath_t {
        <<struct>>
        note_plpath_point_t segments[]
        size_t segement_count
        note_plpath_point_buffer_t* point_buffer
    }


    class note_plpath_segment_t {
        <<struct>>
        note_plpath_point_t* points
        size_t point_count
    }

    class note_plpath_point_buffer_t {
        <<struct>>
        note_plpath_point_t* points
        size_t size
        size_t idx
    }

    class note_plpath_point_t {
        <<struct>>
        double x
        double y
        double z
        note_plpath_point_t * next_point
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

The piecewise linear path notation component does not use any other components.

## External Libraries

The piecewise linear path notation component does not use any external libraries.

## Functionality

### Public

#### Structures

##### Notation Structure

The interface structure for the component is designed to match the non memory allocating design
goals of non-runner components. That means this notation structure contains:

- An array of piecewise linear path segments (a single connected component homotopic to a point or
  $S^1$)
- The size of the supplied list of segments
- A buffer of points to be used to build the piecewise linear path

```{warning}

This structure does not offer any guarantees on intersection (or self intersection). This means
that segments of a path may intersect (or self intersect).

```

##### Point Structure

The point structure contains a three tuple of doubles representing the $x,y,z$ coordinate of a point
on the path. The structure also contains a pointer to the "next" point in the segment.

#### Functions

##### Decode Function

The decode function takes in a string of the following form:

```
x,y,z
x,y,z
x,y,z

x,y,z
// A comment line
x,y,z
x,y,z
```

Where $x,y,z$ are string representations of floating-point numbers, `\n\n` indicates the beginning
of a new segment of the collection of PL paths, and a line starting with `//` indicates a comment
line.

```{warning}

Comments are lost when decoding the string. This means if you take a round trip (file -> decode -> encode)
the resulting string will have no comments.

```

This process is described in the following state machines:

```mermaid
stateDiagram-v2
    state "Read line" as rl
    state "Add new segment" as ans
    state "Read point" as rp
    state "Add point to segment" as a2s
    state is_good_pt <<choice>>
    state is_eof <<choice>>

    [*] --> rl
    rl --> is_eof
    is_eof --> rl: Is a comment
    is_eof --> rp: Is a point
    is_eof --> ans: Is a new segment
    ans --> rl
    rp --> is_good_pt
    is_good_pt --> a2s: Point is valid
    a2s --> rl
    is_eof --> [*]: Is end of file
    is_good_pt --> [*]: else

```

##### Encode Function

The encode function takes in a `note_plpath_node_t` and encodes it into the linearized string form
of the piecewise linear path.

```mermaid
stateDiagram-v2
    state "Print Point" as pp
    state "Move to next segment" as mns
    state "Print new line" as pnl
    state is_choice <<choice>>
    state is_segement_end <<choice>>

    [*] --> is_choice
    is_choice --> pp: Points are available
    is_choice --> is_segement_end: Is end of segment
    is_segement_end -->  [*]: No segments remaining
    is_segement_end --> mns: else
    mns --> pnl
    pnl --> is_choice
    pp --> is_choice

```

### Private

#### Structures

The component has no private structures.

#### Functions

The private functions of the component are straightforward.

## Validation

### Decode Interface

#### Positive Tests

```{test-card} Valid string representing a PL path

A valid string representing a PL path  is fed to the function.

**Inputs:**

- Valid strings representing a PL path:
    - A string with multiple segments
    - A string with a single segment
    - A string with comments
    - A string with no comments
    - A string with `\n\n\n`
    - A string with terminal `\n`
    - A string with no segments.

**Expected Output:**

A correct and valid decoding of the string

```

#### Negative Tests

```{test-card} A malformed PL path is fed to the function

A malformed PL path string is fed to the function.

**Inputs:**

Malformed strings with the following characteristics:

- An illegal character.
- An incomplete point.


**Expected Output:**

The function reports an error.

```

### Encode Interface

#### Positive Tests

```{test-card} Valid PL path

A valid PL path is fed to the function.

**Inputs:**

- A correct and valid PL path.

**Expected Output:**

A valid string representing the PL path.

```

#### Negative Tests

```{test-card} A NULL string buffer is passed

The output string buffer is a NULL pointer.

**Inputs:**

- A NULL pointer buffer is passed to the function

**Expected Output:**

The function will produce an error.
```

## Doxygen Documentation

```{doxygenfile} notation_plpath.h

```

```{doxygenfile} notation_plpath.c

```

## Bibliography

```{bibliography}
   :filter: docname in docnames
```

```{raw} latex
    \newpage
```

```

```
