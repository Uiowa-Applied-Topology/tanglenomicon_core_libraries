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
    comp_ring shift --|> computation
    comp_rlitt_ringshift_config_t --|> notation_wptt
    comp_rlitt_ringshift_config_t --|> comp_config_t
    comp_ring shift *-- comp_rlitt_ringshift_config_t
    comp_rlitt_ringshift_result_t --|> notation_wptt
    comp_rlitt_ringshift_result_t --|> comp_result_t
    comp_ring shift *-- comp_rlitt_ringshift_result_t

    class computation {
        <<interface>>
    }

    class comp_ring shift {
<<>>
- notation_wptt node_buffer[MAX_CN]
}

class notation_wptt{
<<>>
}

class comp_rlitt_ringshift_config_t {
<<struct>>
+ notation_wptt *rootstock
+ notation_wptt *scion
+ uint8 grating_idx
}

class comp_config_t {
<<interface>>
}

class comp_rlitt_ringshift_result_t {
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

The configuration structure contains the data needed for computing the tree with $R^\pm$ applied.

This includes:

- A pointer to a notation structure for a WPTT.

#### Result Structure

The result structure contains a weighted planar tangle tree that is the result of application of the
$R^\pm$ moves the configured tree.

```{warning}
The tree pointed to by the result is the same as the input tree. The $R^\pm$ moves preserve
topology making this okay mathamatically, however care must be taken computationally.
```

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
    copy_ringshift_tree: Copy and ringshift rootstock into buffer
    graft: Graft at vertex i

    [*] --> copy_ringshift_tree
    copy_ringshift_tree --> graft
    graft --> [*]
```

### Private Functions

### Normalize Rootstock

The ringshift rootstock function rearranges the nodes of the rootstock so that each node has
forwarded order. This is accomplished by reversing the child and weight list, then setting the order
to forward in every node that has order reverse.

```mermaid
stateDiagram-v2
    state is_forward <<choice>>
    for_nodes: For each node in rootstock

    state for_nodes {
        reverse_weights: Reverse weights of node
        reverse_children: Reverse children of node
        set_order: set order to forward
        [*] --> reverse_weights
        reverse_weights --> reverse_children
        reverse_children --> set_order
        set_order --> [*]
    }

    [*] --> is_forward
    is_forward --> for_nodes : Order is reverse
    is_forward --> [*] : Order is forward
    for_nodes --> [*]
```

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

When this function is invoked, the result of the ring shift computation process is reported.

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

### Results Function

#### Positive Tests

```{test-card} A valid configuration and computation

A valid configuration is set for the component. The computation is executed and
returns successfully. The resulting value is correct when read from the result
interface.

**Inputs:**

- A valid configuration is set.

**Expected Output:**

- A positive response.
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

```{doxygenfile} comp_rlitt_ringshift.h

```

```{doxygenfile} comp_rlitt_ringshift.c

```

## Bibliography

```{bibliography}
   :filter: docname in docnames
```

```{raw} latex
    \newpage
```
