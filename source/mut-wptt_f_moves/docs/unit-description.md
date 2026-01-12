---
date: 2025-11-16
authors:
  - Joe Starr
contact: support@joe-starr.com
abstract: A unit description for mutation of the $F_i$ move mutator.
---

# Unit Description

```{note}
A block diagram for the component under development
```

```mermaid
classDiagram
    mut_wptt_f_moves --|> mutator
    mut_wptt_f_moves_config_t --|> mut_config_t
    mut_wptt_f_moves_config_t *-- notation_wptt
    mut_wptt_f_moves *-- mut_wptt_f_moves_config_t
    mut_wptt_f_moves_config_t *-- mut_wptt_f_move_e
    mut_wptt_f_moves_config_t *-- mut_wptt_f_moves_direction_e
    mut_wptt_f_moves_config_t *-- mut_wptt_f_moves_eqclass_e

    class mutator {
        <<interface>>
    }

    class mut_wptt_f_moves {
    <<>>
    }

    class notation_wptt{
    <<>>
    }

    class mut_wptt_f_moves_config_t {
    <<struct>>
    + note_wptt_node_t wptt
    + note_wptt_V4_label_e V4_label
    + mut_wptt_f_move_e move
    + size_t weight_idx
    + mut_wptt_f_moves_direction_e shift_dir
    + mut_wptt_f_moves_eqclass_e eq_class
    }

    class mut_wptt_f_moves_eqclass_e{
        <<enum>>
        uninit,
        Vertex,
        Children
    }

    class mut_wptt_f_moves_direction_e{
        <<enum>>
        uninit,
        Forward,
        Backward
    }

    class mut_wptt_f_move_e{
        <<enum>>
        uninit,
        F1,
        F2,
        F3
    }

    class mut_config_t {
    <<interface>>

    }


```

## Language

C

## Implements

- [Mutator Interface][interface-mutator]

## Uses

- [Notation Weighted Planar Tangle Tree][note-wptt]

## External Libraries

None

## Functionality

### Public

#### Structures

##### Configuration Structure

The configuration structure contains the data needed for mutating a tree with the $F_1$, $F_2$, and
$F_3^\prime$ moves.

This includes:

- A pointer to a node in a WPTT.
- An indicator for which $F_i$ move to apply.
- The index for the weight to operate on.
- An indicator for which direction to shift the weight.
- An indicator for which equivalence class of vertex to operate on.

#### Functions

##### Configuration Function

The configuration function configures the local instance variable of the mutator.

This process is described in the following state machines:

```mermaid
stateDiagram-v2
  state "Init local configuration" as Sc

    [*] --> Sc
    Sc --> [*]

```

##### Mutator Function

The mutator function carries out the arborescent tangle $F_i$ mutations. The function may contain
submachines that can be broken out into functions in the implementation.

This process is described in the following state machines:

```mermaid
stateDiagram-v2
    state move <<choice>>
    state "Run $$\,F_3^\prime$$" as rf3
    state "Run $$\,F_2$$" as rf2
    state "Run $$\,F_1$$" as rf1
    [*] --> move
    move --> rf3: Request $$\,F_3^\prime$$
    move --> rf2: Request $$\,F_2$$
    move --> rf1: Request $$\,F_1$$
    move --> [*]: Else
    rf3 --> [*]
    rf2 --> [*]
    rf1 --> [*]
```

### Private

#### Function

##### $F_1$

The state machine describing the flow and mutations for the $F_1$ move are as follows:

```mermaid
stateDiagram-v2
    walk: Walk the tree and execute for each vertex visited

    state walk{
    state "Reverse order of vertex" as ro
    [*]-->ro
    ro --> [*]
    }
    [*]--> walk
    walk --> [*]
```

##### $F_2$

The state machine describing the flow and mutations for the $F_2$ move are as follows:

```mermaid
stateDiagram-v2

    state at_object <<choice>>
    state "Walk the tree and reverse" as walk
    child: For each child
    state child{
    state "Walk the tree and reverse" as ro
    [*]-->ro
    ro --> [*]
    }
    [*]--> at_object
    at_object--> walk: Current vertex requested
    at_object --> child: Child vertex requested
    child --> [*]
    walk --> [*]
```

##### $F_3^\prime$

The state machine describing the flow and mutations for the $F_3^\prime$ move are as follows where
$i$ is assumed to to be the index of the weight $w_i$ to be acted on and $j$ is the index of the
destination index wrapping where needed:

```mermaid
stateDiagram-v2
    sib: For each sibling
    state sib{
        state "Walk the tree and reverse" as swtt
        [*]--> swtt
        swtt --> [*]
    }
    state "Walk the tree and reverse" as wtt
    state is_zero <<choice>>
    state is_parent <<choice>>
    state is_odd <<choice>>
    state "Set w_j+w_i" as sij
    state "Set w_i=0" as wi0
    [*] --> is_zero
    is_zero --> [*]: $$w_i\,$$ is zero
    is_zero --> sij
    sij --> wi0
    wi0 --> is_odd
    is_odd --> is_parent: w_i%2=2
    is_parent --> wtt: Else
    is_parent --> sib: If j==0 or  j == n+1$$
    sib --> [*]
    wtt --> [*]
    is_odd --> [*]: Else



```

##### Walk the Tree and Reverse

Walk the tree and execute the following for each vertex visited:

```{mermaid}
stateDiagram-v2
        state is_odd <<choice>>
        state "Reverse order of vertex" as ro
        [*]--> is_odd
        is_odd --> ro: Is odd stack count
        is_odd --> [*]: else
        ro --> [*]
```

## Validation

### Configuration Function

#### Positive Tests

<!-- prettier-ignore-start -->

!!! test-card "Valid Configuration"

    A valid configuration for the mutation is passed to the function.

    **Inputs:**

    - A valid configuration.

    **Expected Output:**

    A positive response.

<!-- prettier-ignore-end -->

#### Negative Tests

<!-- prettier-ignore-start -->

!!! test-card "Null Configuration"

    A null configuration for the mutation is passed to the function.

    **Inputs:**

    - A null configuration.

    **Expected Output:**

    A negative response.

<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->

!!! test-card "Invalid Configuration Parameters"

    A configuration with various null parameters is passed to the function.

    **Inputs:**

    - A configuration with null vertex.
    - A configuration with an uninitialized move.
    - Configurations for the $F_1$ move with:
        - Null label
        - Uninitialized label
    - Configurations for the $F_2$ move with:
        - Null label
        - Uninitialized label
        - Uninitialized eqclass
    - Configurations for the $F_3^\prime$ move with:
        - Uninitialized direction

    **Expected Output:**

    A negative response.

<!-- prettier-ignore-end -->

### Mutate Function

#### Positive Tests

<!-- prettier-ignore-start -->

!!! test-card "A valid configuration"

    A valid configuration is set for the component. The mutation is executed and
    returns successfully.

    **Inputs:**

    - A valid configuration is set for $F_1$.
    - Valid configurations are set for $F_2$:
        - Eqclass is child.
        - Eqclass is self.
    - Valid configurations are set for $F_3^\prime$ with at least one test suming two weights:
        - Odd weight:
            - Index is rightmost:
                - Direction is forward.
                - Direction is backward.
            - Index is leftmost:
                - Direction is forward.
                - Direction is backward.
        - Even weight:
            - Index is rightmost:
                - Direction is forward.
                - Direction is backward.
            - Index is leftmost:
                - Direction is forward.
                - Direction is backward.

    **Expected Output:**

    - A positive response.
    - Mutation is correct.

<!-- prettier-ignore-end -->

#### Negative Tests

<!-- prettier-ignore-start -->

!!! test-card "Not Configured"

    The mutate interface is called before configuration.

    **Inputs:**

    - None.

    **Expected Output:**

    A negative response.

<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->

!!! test-card "Double Execute"

    The mutate interface is called without reconfiguring the module.

    **Inputs:**

    - None.

    **Expected Output:**

    A negative response.

<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->

!!! test-card "$F_3^\prime$ index out of bounds"

    The mutate interface is called with a weight index configured outside
    of the size of the number of children.

    **Inputs:**

    - Configuration with weight idx outside bounds.

    **Expected Output:**

    A negative response.

<!-- prettier-ignore-end -->
