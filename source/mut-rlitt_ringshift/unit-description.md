---
date: 2025-06-16
authors:
    - Joe Starr
contact: support@joe-starr.com
abstract: A unit description description for mutation of the rings of an Arborescent Tangle tree.
---

# Unit Description

## Class Diagram

```mermaid
classDiagram
    mut_ring shift --|> mutator
    mut_rlitt_ringshift_config_t --|> notation_wptt
    mut_rlitt_ringshift_config_t --|> mut_config_t
    mut_ring shift *-- mut_rlitt_ringshift_config_t

    class mutator{
        <<interface>>
    }

    class mut_ringshift {
    <<>>
    }

    class notation_wptt{
    <<>>
    }

    class mut_rlitt_ringshift_config_t {
    <<struct>>
    note_wptt * wptt
    }

    class mut_config_t {
    <<interface>>
    }




```

## Language

C

## Implements

- [Computation Interface](#computation-interface)

## Uses

- [Notation Weighted Planar Tangle Tree](#note-wptt)

## Libraries

None

## Functionality

### Public Structures

#### Configuration Structure

The configuration structure contains the data needed for computing the tree with $R^\pm$ applied.

This includes:

- A pointer to a notation structure for a WPTT.

### Public Functions

#### Configuration Function

The configuration function configures the local instance variable of the computation.

This process is described in the following state machines:

```mermaid
stateDiagram-v2
  state "Init local config" as Sc

    [*] --> Sc
    Sc --> [*]

```

#### Compute Function

The compute function carries out the arborescent tangle ring shift computation. The function may
contain sub machines that can be broken out into functions in the implementation.

This process is described in the following state machines:

```mermaid
stateDiagram-v2
    walk: Walk the tree and execute for each vertex visited

    state walk{
        state "shift rings of tree to the right" as sr
        [*]--> sr
          sr  -->[*]
    }
    [*] --> walk
    walk --> [*]
```

### Private Functions

#### Sort Children

The sort children function uses the C standard qsort function to sort the children vertices of the
object vertex.

## Validation

### Configuration Function

#### Positive Tests

```{test-card} Valid Config

A valid configuration for the computation is passed to the function.

**Inputs:**

- A valid config.

**Expected Output:**

A positive response.

```

#### Negative Tests

```{test-card} Null Config

A null configuration for the computation is passed to the function.

**Inputs:**

- A null config.

**Expected Output:**

A negative response.

```

```{test-card} Null Configuration Parameters

A configuration with various null parameters is passed to the function.

**Inputs:**

- A configuration with null rootstock.
- A configuration with null scion.

**Expected Output:**

A negative response.

```

### Compute Function

#### Positive Tests

```{test-card} A valid config

A valid configuration is set for the component. The computation is executed and
returns successfully. The result written to the write interface is correct

**Inputs:**

- A valid configuration is set.

**Expected Output:**

- A positive response.
- A correct output on the write interface.

```

```{test-card} A valid configuration with null write interface

A valid configuration is set for the component with null write. The computation is
executed and returns successfully.

**Inputs:**

- A valid configuration is set.

**Expected Output:**

- A positive response.

```

#### Negative Tests

```{test-card} Not Configured

The compute interface is called before configuration.

**Inputs:**

- None.

**Expected Output:**

A negative response.

```

## Doxygen Documentation

```{doxygenfile} mut_rlitt_ringshift.h

```

```{doxygenfile} mut_rlitt_ringshift.c

```

## Bibliography

```{bibliography}
   :filter: docname in docnames
```

```{raw} latex
    \newpage
```
