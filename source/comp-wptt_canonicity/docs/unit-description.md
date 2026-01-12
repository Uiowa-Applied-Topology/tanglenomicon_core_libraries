---
date: 2024-09-18
authors:
  - Joe Starr
contact: joe@joe-starr.com
abstract: A unit description for computation of weighted planar tangle tree canonicity.
---

# Unit Description

```mermaid
classDiagram
    comp_wptt_canonicity  --|> computation
    comp_wptt_canonicity_config_t --|> notation_wptt_canonicity
    comp_wptt_canonicity_config_t --|> comp_config_t
    comp_wptt_canonicity_result_t --|> comp_result_t
    comp_wptt_canonicity  *-- comp_wptt_canonicity _config_t
    comp_wptt_canonicity  *-- comp_wptt_canonicity _result_t
    comp_wptt_canonicity_config_t *-- comp_wptt_canonicity_positivity_e
    comp_wptt_canonicity_result_t *-- comp_wptt_canonicity_canon_e

    class computation {
        <<interface>>
    }

    class comp_wptt_canonicity  {
    <<>>
    }

    class notation_wptt_canonicity {
    <<>>
    }

    class comp_wptt_canonicity_config_t {
    <<struct>>
    + notation_wptt *tree
    + comp_wptt_canonicity_positivity_e positivity
    }

    class comp_wptt_canonicity_positivity_e {
    <<Enumeration>>
     uninit,
     positive,
     negative,
    }

    class comp_wptt_canonicity_canon_e {
    <<Enumeration>>
     uninit,
     positive,
     negative,
    }

    class comp_wptt_canonicity_result_t {
    <<struct>>
    +comp_wptt_canonicity_canon_e is_canon

    }

    class comp_config_t {
    <<interface>>

    }


```

## Language

C

## Implements

- [Computation Interface][interface-computation]

## Uses

- [Notation Weighted Planar Tangle Tree][note-wptt]
- [Computation WPTT Vertex Canonicity][comp-wptt_vertex_canonicity]

## External Libraries

None

## Functionality

### Public

#### Structures

##### Configuration Structure

The configuration structure has two pieces of data as follows:

- A notation for an object tree to compute canonicity of.
- Positivity to compute against, one of positive or negative.

##### Result Structure

The result structure contains only a boolean indicating canonicity.

#### Functions

##### Configuration Function

The configuration function sets the local configuration variable of the computation.

This process is described in the following state machines:

```mermaid
stateDiagram-v2
  state "Initialize local configuration" as Sc

    [*] --> Sc
    Sc --> [*]

```

##### Computation Function

The computation function walks the object tree and computes each vertex canonicity. If each vertex
is canonical then the whole tree is canonical.

```mermaid
stateDiagram-v2

    walk: Walk the tree and execute for each vertex visited
    state "Report result" as rr
    state "Check root canonicity" as crc
    state is_canon1 <<choice>>

    state walk{
        state "Compute vertex canonicity" as cvc
        state is_canon <<choice>>
        [*] --> cvc
        cvc --> is_canon
        is_canon --> [*]: If not canon break
        is_canon --> [*]: Else continue
    }

    [*] --> crc
    crc --> is_canon1
    is_canon1 -->rr: non-canonical
    is_canon1  --> walk: else
    walk --> rr
    rr --> [*]
```

##### Result Function

When this function is invoked, the result of the canonicity computation process is reported.

```mermaid
stateDiagram-v2
  state "Report result" as Sc

    [*] --> Sc
    Sc --> [*]

```

### Private

#### Function

##### Walk the Tree

The tree walking function follows the pattern used by other WPTT components.

## Validation

### Configuration Function

#### Positive Tests

<!-- prettier-ignore-start -->

!!! test-card "Valid Configuration"

    A valid configuration for the computation is passed to the function.

    **Inputs:**

    - A valid configuration.

    **Expected Output:**

    A positive response.

<!-- prettier-ignore-end -->

#### Negative Tests

<!-- prettier-ignore-start -->

!!! test-card "Null Configuration"

    A null configuration for the computation is passed to the function.

    **Inputs:**

    - A null configuration.

    **Expected Output:**

    A negative response.

<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->

!!! test-card "Null configuration Parameters"

    A configuration with various null parameters is passed to the function.

    **Inputs:**

    - A configuration with null tree.

    **Expected Output:**

    A negative response.

<!-- prettier-ignore-end -->

### Compute Function

#### Positive Tests

<!-- prettier-ignore-start -->

!!! test-card "A valid configuration"

    A valid configuration is set for the component. The computation is executed and
    returns successfully. The result written to the write interface is correct.

    **Inputs:**

    - A valid configuration is set with the following trees:
        - Canonical trees
            - `i[3 3]`
            - `i[3 0]`
            - `x([3 3]3[3 3])`
            - `i((([3 3]3[3 3])3)-3)`
            - `i[-3]`
            - `i[0]`
            - `i[0 0]`
            - `i[2]`
            - `i[-2]`
            - `i[1]`
            - `i[-1]`
        - Non-canonical trees
            - S.A
                - `i[3 -3]`
                - `i((([3 -3]3[3 3])3)-3)`
                - `i((([3 3]3[3 3])3)3)`
                - `i(([3 3]3[3 3])3((([3 3]3[3 3])3)3))`
            - S.0
                - `i[-1 -3]`
                - `i[1 3]`
                - `i([3 3][3 3](([3 3]3[3 3])1))`
                - `i([3 3][3 3](([3 3]3[3 3])-1))`
                - `i([3 3][3 3][1])`
                - `i([3 3][3 3][-1])`
                - `i(((([3 3]3[3 3])1)-3)[3 3])`
                - `i(((([3 3]3[3 3])-1)3)[3 3])`
                - `i(((([3 3]3[3 3])3)-1)[3 3])`
                - `i(((([3 3]3[3 3])-3)1)[3 3])`
            - S.1
                - `i[-3 0 3]`
                - `i([3 3][3 3][0])`
                - `i((([3 3]3[3 3]))[3 3])`
                - `i(((([3 3]3[3 3])3))3)`
                - `i(((([3 3]3[3 3]))3)3)`
            - W
                - `i(3[-3]3)`
                - `i([-3](3[-3]3))`
                - `i(3[-3]3[-3])`
            - P.P
                - `i([-2][3])`
                - `i([3 3](([3 3]3[3 3])-2))`
            - P.N
                - `i([2][3])`
                - `i([3 3](([3 3]3[3 3])2))`

    **Expected Output:**

    - A positive response.
    - A correct output on the write interface.

<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->

!!! test-card "A valid configuration with null write interface"

    A valid configuration is set for the component with null write. The computation is
    executed and returns successfully.

    **Inputs:**

    - A valid configuration is set.

    **Expected Output:**

    - A positive response.

<!-- prettier-ignore-end -->

#### Negative Tests

<!-- prettier-ignore-start -->

!!! test-card "Not Configured"

    The compute interface is called before configuration.

    **Inputs:**

    - None.

    **Expected Output:**

    A negative response.

<!-- prettier-ignore-end -->

### Result Function

#### Positive Tests

<!-- prettier-ignore-start -->

!!! test-card "Correct handling of a canonical tree"

    A valid configuration is set for the component. The computation is executed and
    returns successfully. The result written to the write interface is correct.

    **Inputs:**

    - A valid configuration is set, the following trees are configured:
        - One tree for each canonicity condition.

    **Expected Output:**

    - A positive response.
    - A correct output on the write interface.

<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->

!!! test-card "Correct handling of a noncanonical tree"

    A valid configuration is set for the component. The computation is executed and
    returns successfully. The result written to the write interface is correct.

    **Inputs:**

    - A valid configuration is set, the following trees are configured:
        - One tree for each canonicity condition.

    **Expected Output:**

    - A positive response.
    - A correct output on the write interface.

<!-- prettier-ignore-end -->

#### Negative Tests

<!-- prettier-ignore-start -->

!!! test-card "Computation not executed"

    The result interface is called before compute has been run.

    **Inputs:**

    - None.

    **Expected Output:**

    A negative response.

<!-- prettier-ignore-end -->

## Doxygen Documentation

```{doxygenfile} comp_wptt_canonicity.h

```

```{doxygenfile} comp_wptt_canonicity.c

```
