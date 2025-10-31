---
date: 2025-06-16
authors:
    - Joe Starr
contact: support@joe-starr.com
abstract: A unit description for computation of arborescent tangle grafting.
---

# Unit Description

## Class Diagram

```mermaid
classDiagram
    comp_rlitt_grafting --|> computation
    comp_rlitt_grafting_config_t --|> notation_wptt
    comp_rlitt_grafting_config_t --|> comp_config_t
    comp_rlitt_grafting *-- comp_rlitt_grafting_config_t
    comp_rlitt_grafting_result_t --|> notation_wptt
    comp_rlitt_grafting_result_t --|> comp_result_t
    comp_rlitt_grafting *-- comp_rlitt_grafting_result_t

    class computation {
        <<interface>>
    }

    class comp_rlitt_grafting {
<<>>
- notation_wptt node_buffer[MAX_CN]
}

class notation_wptt{
<<>>
}

class comp_rlitt_grafting_config_t {
<<struct>>
+ notation_wptt *rootstock
+ notation_wptt *scion
+ uint8 grating_idx
}

class comp_config_t {
<<interface>>
}

class comp_rlitt_grafting_result_t {
<<struct>>
+ notation_wptt result
}

class comp_result_t {
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

The configuration structure contains the data needed for computing the rlitt_grafting of two input
arborescent tangles.

This includes:

- Rootstock pointer to a read-only notation structure for a WPTT.
- Scion pointer to a read-only notation structure for a WPTT.

#### Result Structure

The configuration structure contains a weighted planar tangle tree that is the result of
rlitt_grafting the configured rootstock to the configured scion.

### Public Functions

#### Configuration Function

The configuration function sets the local configuration variable of the computation.

This process is described in the following state machines:

```mermaid
stateDiagram-v2
  state "Init local config" as Sc

    [*] --> Sc
    Sc --> [*]

```

#### Compute Function

The compute function carries out the arborescent tangle rlitt_grafting computation. The function may
contain sub-machines that can be broken out into functions in the implementation.

This process is described in the following state machines:

```mermaid
stateDiagram-v2
    copy_normalize_tree: Copy and normalize
    copy_normalize_tree: rootstock into buffer
    graft: Graft at vertex i

    [*] --> copy_normalize_tree
    copy_normalize_tree --> graft
    graft --> [*]
```

### Private Functions

#### Graft Scion to Rootstock

This function carries out the

```mermaid
stateDiagram-v2
    find_node: Identify the ith node
    set_count: Increment child count
    add_node: Add root of scion
    add_node: to the child list
    move_weight: Move last weight right
    move_weight: one and replace with 0

    [*] --> find_node
    find_node --> set_count
    set_count --> add_node
    add_node --> move_weight
    move_weight --> [*]
```

#### Result Function

When this function is invoked, the result of the rlitt_grafting computation process is reported.

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

- A positve response.
- A correct output on the write interface.

```

```{test-card} A valid configuration with null write interface

A valid configuration is set for the component with null write. The computation is
executed and returns successfully.

**Inputs:**

- A valid configuration is set.

**Expected Output:**

- A positve response.

```

#### Negative Tests

```{test-card} Not Configured

The compute interface is called before configuration.

**Inputs:**

- None.

**Expected Output:**

A negative response.

```

### Results Function

#### Positive Tests

```{test-card} A valid configuration and computation

A valid configuration is set for the component. The computation is executed and
returns successfully. The resulting value is correct when read from the result
interface.

**Inputs:**

- A valid configuration is set.

**Expected Output:**

- A positve response.
- The result is correct.
```

#### Negative Tests

```{test-card} Computation not executed

The result interface is called before compute has been run.

**Inputs:**

- None.

**Expected Output:**

A negative response.

```

## Doxygen Documentation

```{doxygenfile} comp_rlitt_grafting.h

```

```{doxygenfile} comp_rlitt_grafting.c

```

## Bibliography

```{bibliography}
   :filter: docname in docnames
```

```{raw} latex
    \newpage
```
