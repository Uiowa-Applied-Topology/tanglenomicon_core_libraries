---
date: 2026-03-18
authors:
  - joe_starr
contact: dr@joe-starr.com
abstract: A unit description for computation of arborescent tangle vertex parity.
---

# Unit Description

## Class Diagram

```mermaid
classDiagram
    comp_sum_parity ..|> computation
    comp_sum_parity_config_t ..|> comp_config_t
    comp_sum_parity_result_t ..|> comp_result_t
    comp_sum_parity *-- comp_sum_parity_config_t
    comp_sum_parity *-- comp_sum_parity_result_t
    comp_sum_parity_result_t *-- comp_sum_parity_parity_e
    comp_sum_parity_result_t *-- comp_sum_parity_op_e
    class computation {
    <<External Interface>>
    }

    class comp_sum_parity {
    }

    class comp_sum_parity_config_t {
    + comp_sum_parity_parity_e tangleA
    + comp_sum_parity_parity_e tangleB
    + comp_sum_parity_op_e op
    }

    class comp_config_t {
    <<External Interface>>
    }

    class comp_sum_parity_result_t {
    + comp_sum_parity_parity_e parity
    + uint16_t component_count
    }

    class comp_sum_parity_op_e {
    <<Enumeration>>
     uninit,
     plus,
     vee
    }

    class comp_sum_parity_parity_e {
    <<Enumeration>>
     uninit,
     zero,
     chi,
     infty
    }

    class comp_result_t {
    <<External Interface>>
    }

```

## Language

C

## Implements

- [Computation Interface][interface-computation]

## Uses

None

## Libraries

None

## Functionality

### Public Structures

#### Configuration Structure

The configuration structure contains the data needed for computing the parity of the horizontal or
vertical sum of two tangles.

This includes:

- Two sumand tangles A and B
- An operation to apply

#### Result Structure

The result structure contains the parity of the tangle that results from the sum and a count of
knotted components.

### Public Functions

#### Configuration Function

The configuration function sets the local configuration variable of the computation.

This process is described in the following state machines:

```mermaid
stateDiagram-v2
  state "Initialize local configuration" as Sc

    [*] --> Sc
    Sc --> [*]

```

#### Compute Function

The compute function carries out the computation as described in the use-case. The function may
contain submachines that can be broken out into functions in the implementation. The walk the tree
function should be implemented with a stack-based iterative approach.

This process is described in the following state machines:

```mermaid
stateDiagram-v2

    state is_vert <<choice>>
    state "Compute parity of horizontal sum" as hs
    state "Compute parity of vertical sum" as vs
    [*]-->is_vert
    is_vert --> hs: horizontal sum requested
    is_vert --> vs: vertical sum requested
    hs --> [*]
    vs --> [*]

```

#### Result Function

When this function is invoked, the result of the vertex parity computation process is reported.

## Validation

### Configuration Function

#### Positive Tests

> [!test-card] "Valid Configuration"
>
> A valid configuration for the computation is passed to the function.
>
> **Inputs:**
>
>   - A valid configuration.
>
> **Expected Output:**
>
>    A positive response.

#### Negative Tests

> [!test-card] "Null Configuration"
>
> A null configuration for the computation is passed to the function.
>
> **Inputs:**
>
>   - A null configuration.
>
> **Expected Output:**
>
>    A negative response.

> [!test-card] "Null Configuration Parameters"
>
> A configuration with null parameters is passed to the function.
>
> **Inputs:**
>
>   - A configuration with null WPTT.
>
> **Expected Output:**
>
>    A negative response.

### Compute Function

#### Positive Tests

> [!test-card] "A valid configuration with null write interface"
>
> A valid configuration is set for the component with null write. The computation is executed and
> returns successfully.
>
> **Inputs:**
>
>   - A valid configuration is set.
>
> **Expected Output:**
>
>   - A positive response.

> [!test-card] "Identified vertex is canonical"
>
> A valid configuration with write function is set for the component. The computation executes and
> returns successfully.
>
> **Inputs:**
>
>   - Set a valid configuration for all possible combinations of parities.
>
> **Expected Output:**
>
>   - A positive response.

#### Negative Tests

> [!test-card] "Not Configured"
>
> The compute interface is called before configuration.
>
> **Inputs:**
>
>   - None.
>
> **Expected Output:**
>
>    A negative response.

### Result Function

#### Positive Tests

> [!test-card] "A valid configuration and computation"
>
> A valid configuration is set for the component. The computation is executed and returns
> successfully. The resulting values are correct when read from the result interface.
>
> **Inputs:**
>
>   - Set a valid configuration for all possible combinations of parities.
>
> **Expected Output:**
>
>   - A positive response.

#### Negative Tests

> [!test-card] "Computation not executed"
>
> The result interface is called before compute has been run.
>
> **Inputs:**
>
>   - None.
>
> **Expected Output:**
>
>    A negative response.
