---
date: 2025-06-16
authors:
  - joe_starr
contact: dr@joe-starr.com
abstract: A unit description for computation of arborescent tangle vertex canonicity.
---

# Unit Description

## Class Diagram

```mermaid
classDiagram
    comp_wptt_to_path ..|> computation
    comp_wptt_to_path_result_t ..|> comp_result_t
    comp_wptt_to_path_result_t ..> notation_plpath
    comp_wptt_to_path_config_t ..|> comp_config_t
    comp_wptt_to_path_config_t ..> notation_wptt
    comp_wptt_to_path_config_t ..> notation_plpath
    comp_wptt_to_path_segment_set_t..> comp_sum_parity_parity_e
    comp_wptt_to_path_segment_set_t ..> note_plpath_segment_t
    comp_wptt_to_path ..> comp_sum_parity
    comp_wptt_to_path *-- comp_wptt_to_path_result_t
    comp_wptt_to_path *-- comp_wptt_to_path_config_t
    comp_wptt_to_path *-- comp_wptt_to_path_segment_set_t

    class computation {
    <<External Interface>>
    }

    class comp_wptt_to_path {
    - segment_set build_vit(uint64_t weight)
    - segment_set build_hit(uint64_t weight)
    - segment_set process_knotted_component(segment_set A, segment_set B)
    - segment_set do_plus(segment_set A, segment_set B)
    - segment_set do_vee(segment_set A, segment_set B)
    - note_plpath_point_t reverse_segment(note_plpath_point_t head)
    }

    class comp_sum_parity_parity_e {
    <<External Enum>>
    }

    class comp_sum_parity{
    <<External>>
    }

    class notation_plpath{
    <<External>>
    }

    class notation_wptt{
    <<External>>
    }

    class note_plpath_segment_t{
    <<External>>
    }

    class comp_wptt_to_path_segment_set_t {
    + note_plpath_segment_t * NW_seg
    + note_plpath_point_t * NW_seg_end
    + note_plpath_segment_t * second_seg
    + note_plpath_point_t * second_seg_end
    + note_plpath_segment_t *knotted_segs
    + comp_wptt_vertex_parity_parity_e parity
    }

    class comp_wptt_to_path_config_t {
    + notation_wptt *wptt
    + note_plpath_t *out_path
    }

    class comp_config_t {
    <<External Interface>>
    }

    class comp_wptt_to_path_result_t {
    + note_plpath_t *path
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

- [Notation Weighted Planar Tangle Tree][note-wptt]
- [Notation PL Path][note-plpath]
- [Computation Parity of Tangle Sums][comp-sum_parity]

## Libraries

None

## Functionality

### Public Structures

#### Configuration Structure

The configuration structure contains the data needed for computing a PL path for an input ITT.

This includes:

- A pointer to the ITT tree.
- A pointer to the output location to where the PL path will be stored.

#### Result Structure

The result structure contains a pointer to the output PL path.

> [!warning]
>
> The pointer found in the result should be checked for consistency with the configured pointer.

### Private Structures

#### Segment Set

A segment contains:

- A segment defined to start at the NW corner of the tangle.
- A pointer to the end of the NW segment.
- A second segment starting at either the $SW$ or $NE$ corner depending on a configured parity for
    the tangle.
- A pointer to the end of the second segment.
- A segment list containing all internal knotted components.

| Tangle Parity | Second Segment Start |
| ------------- | -------------------- |
| $\chi$        | SW                   |
| $0$           | SW                   |
| $\infty$      | NE                   |

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

The compute function carries out the arborescent tangle vertex canonicity computation. The function
may contain submachines that can be broken out into functions in the implementation. The walk the
tree function should be implemented with a stack-based iterative approach.

This process is described in the following state machines:

```mermaid
stateDiagram-v2
    forvert:"for each vertex"
    state forvert {
    state is_depth <<choice>>
    state is_infinf <<choice>>
    state is_zeze <<choice>>
    state is_final_h <<choice>>
    state is_final_v <<choice>>
    state "Build horizontal integral tangle from weight" as bhit
    state "Build vertical integral tangle from weight" as bvit
    state "Process child" as pch
    state "Process child" as pcv
    state "Compute vertical sum" as vs
    state "Compute horizontal sum" as hs
    state "Compute vertical sum" as vs2
    state "Compute horizontal sum" as hs2
    state "Process knoted component" as pkvc
    state "Process knoted component" as pkhc

    [*]-->is_depth
    is_depth --> bvit: Is odd distance from root
    bvit --> is_zeze
    is_zeze -->  pkvc : Sumands have parity zero
    is_zeze --> vs : At least one sumand has parity non-zero
    pkvc --> vs
    vs --> is_final_v
    is_final_v --> pcv: else
    pcv --> vs2
    vs2 --> bvit

    is_depth --> bhit: Is even distance from root
    bhit --> is_infinf
    is_infinf-->  pkhc: Sumands have parity infinity
    is_infinf--> hs: At least one sumand has parity non-infinity
    pkhc --> hs
    hs --> is_final_h
    is_final_h --> pch: else
    pch --> hs2
    hs2 --> bhit

    is_final_v --> [*] : Is final weight
    is_final_h --> [*] : is final weight
    }

    [*] --> forvert
    forvert --> [*]

```

#### Result Function

When this function is invoked, the result of the vertex canonicity computation process is reported.

### Private Functions

#### Build Horizontal/Vertical Integral Tangle

Since the building process is identical, except the gluing direction, between horizontal and
vertical tangles we're going to work in the abstract case.

```mermaid
stateDiagram-v2
    state is_done <<choice>>
    state is_zero <<choice>>
    state "Output zero/infty tangle" as ozit
    state "Output integral tangle" as oit
    state "Build pm 1 tangle" as bpmot
    state "Translate tangle" as trans
    state "Decrement weight" as dw

    [*] --> is_zero
    is_zero --> ozit: Is zero weight?
    is_zero --> is_done: Else
    is_done --> bpmot : Else
    is_done --> oit : Weights are exhausted?
    bpmot --> trans
    trans --> dw
    dw --> is_done
    ozit --> [*]
    oit --> [*]

```

#### Process Knotted Component

Similar to the building of integral tangles the processing of internal knotted components by a $+$
and $\vee$ is largely identical, as such we will work in the abstract case.

```mermaid
stateDiagram-v2
    state is_aligned <<choice>>
    state "Reverse right sumand's inner segment" as rrsis
    state "Combine inner paths" as cip
    state "Return segment" as rs

    [*] --> is_aligned
    is_aligned --> rrsis: else
    is_aligned --> cip: Inner segment orientations agree
    rrsis --> cip
    cip --> rs
    rs --> [*]

```

#### Do Tangle Sum

Similar to the building of integral tangles the processing of $+$ and $\vee$ is largely identical,
as such we will work in the abstract case.

```mermaid
stateDiagram-v2
    state has_internal <<choice>>
    state is_aligned <<choice>>
    state "Process knotted component" as pkc
    state "Reverse right sumand's NW segment" as rrsnws
    state "Add knotted component to segment set" as akcs
    state "Combine inner paths" as cip
    state "Return segment set" as rs

    [*] --> has_internal
    has_internal --> pkc: Sum parity induces a knotted component
    has_internal --> is_aligned : else
    pkc --> akcs
    akcs --> is_aligned
    is_aligned --> rrsnws: else
    is_aligned --> cip: Inner segment orientations agree
    rrsnws --> cip
    cip --> rs
    rs --> [*]

```

#### Reverse Segment

Standard linked list reversal can be done on the segment list.

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
> A configuration with various null parameters is passed to the function.
>
> **Inputs:**
>
>   - A configuration with null tree.
>
> **Expected Output:**
>
>    A negative response.

### Compute Function

#### Positive Tests

> [!test-card] "A valid configuration with write interface"
>
> A valid configuration is set for the component with write interface configured. The computation is
> executed and returns successfully.
>
> **Inputs:**
>
>   - A valid configuration is set with the following trees:
>     - $i[0]$
>     - $i[0\ 0]$
>     - $i[1]$
>     - $i[-1]$
>     - $i([0][0\ 0])$
>     - $i([0][-1])$
>     - $i([0][0])$
>     - $i([-1][0\ 0])$
>     - $i([-1][-1])$
>     - $i([-1][0])$
>     - $i([0\ 0][0\ 0])$
>     - $i([0\ 0][-1])$
>     - $i([0\ 0][0])$
>     - $i([-3][3\ 0])$
>     - $i([-3][-2])$
>     - $i([-3][2\ 0])$
>     - $i([-2][3\ 0])$
>     - $i([-2][-2])$
>     - $i([-2][2\ 0])$
>     - $i([3\ 0][3\ 0])$
>     - $i([3\ 0][-2])$
>     - $i([3\ 0][2\ 0])$
>     - $i(([0][0\ 0]))$
>     - $i(([0][-1]))$
>     - $i(([0][0]))$
>     - $i(([-1][0\ 0]))$
>     - $i(([-1][-1]))$
>     - $i(([-1][0]))$
>     - $i(([0\ 0][0\ 0]))$
>     - $i(([0\ 0][-1]))$
>     - $i(([0\ 0][0]))$
>     - $i(([-3][3\ 0]))$
>     - $i(([-3][-2]))$
>     - $i(([-3][2\ 0]))$
>     - $i(([-2][3\ 0]))$
>     - $i(([-2][-2]))$
>     - $i(([-2][2\ 0]))$
>     - $i(([3\ 0][3\ 0]))$
>     - $i(([3\ 0][-2]))$
>     - $i(([3\ 0][2\ 0]))$
>
> **Expected Output:**
>
>   - A positive response with the appropriate path. The output can be inspected by hand.

> [!test-card] "A valid configuration with null write interface"
>
> A valid configuration is set for the component with null write. The computation is executed and
> returns successfully.
>
> **Inputs:**
>
>   - A valid configuration is set with the following trees:
>     - $i[0]$
>     - $i[0\ 0]$
>     - $i[1]$
>     - $i[-1]$
>     - $i([0][0\ 0])$
>     - $i([0][-1])$
>     - $i([0][0])$
>     - $i([-1][0\ 0])$
>     - $i([-1][-1])$
>     - $i([-1][0])$
>     - $i([0\ 0][0\ 0])$
>     - $i([0\ 0][-1])$
>     - $i([0\ 0][0])$
>     - $i([-3][3\ 0])$
>     - $i([-3][-2])$
>     - $i([-3][2\ 0])$
>     - $i([-2][3\ 0])$
>     - $i([-2][-2])$
>     - $i([-2][2\ 0])$
>     - $i([3\ 0][3\ 0])$
>     - $i([3\ 0][-2])$
>     - $i([3\ 0][2\ 0])$
>     - $i(([0][0\ 0]))$
>     - $i(([0][-1]))$
>     - $i(([0][0]))$
>     - $i(([-1][0\ 0]))$
>     - $i(([-1][-1]))$
>     - $i(([-1][0]))$
>     - $i(([0\ 0][0\ 0]))$
>     - $i(([0\ 0][-1]))$
>     - $i(([0\ 0][0]))$
>     - $i(([-3][3\ 0]))$
>     - $i(([-3][-2]))$
>     - $i(([-3][2\ 0]))$
>     - $i(([-2][3\ 0]))$
>     - $i(([-2][-2]))$
>     - $i(([-2][2\ 0]))$
>     - $i(([3\ 0][3\ 0]))$
>     - $i(([3\ 0][-2]))$
>     - $i(([3\ 0][2\ 0]))$
>
> **Expected Output:**
>
>   - A positive response with the appropriate path. The output can be inspected by hand.

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

> [!test-card] "A valid configuration with processed"
>
> A valid configuration is set for the component. The computation is executed and
> returns successfully. The result interface is accessed successfully.
>
> **Inputs:**
>
>   - A valid configuration is set with the following trees:
>     - $i[0]$
>     - $i[0\ 0]$
>     - $i[1]$
>     - $i[-1]$
>     - $i([0][0\ 0])$
>     - $i([0][-1])$
>     - $i([0][0])$
>     - $i([-1][0\ 0])$
>     - $i([-1][-1])$
>     - $i([-1][0])$
>     - $i([0\ 0][0\ 0])$
>     - $i([0\ 0][-1])$
>     - $i([0\ 0][0])$
>     - $i([-3][3\ 0])$
>     - $i([-3][-2])$
>     - $i([-3][2\ 0])$
>     - $i([-2][3\ 0])$
>     - $i([-2][-2])$
>     - $i([-2][2\ 0])$
>     - $i([3\ 0][3\ 0])$
>     - $i([3\ 0][-2])$
>     - $i([3\ 0][2\ 0])$
>     - $i(([0][0\ 0]))$
>     - $i(([0][-1]))$
>     - $i(([0][0]))$
>     - $i(([-1][0\ 0]))$
>     - $i(([-1][-1]))$
>     - $i(([-1][0]))$
>     - $i(([0\ 0][0\ 0]))$
>     - $i(([0\ 0][-1]))$
>     - $i(([0\ 0][0]))$
>     - $i(([-3][3\ 0]))$
>     - $i(([-3][-2]))$
>     - $i(([-3][2\ 0]))$
>     - $i(([-2][3\ 0]))$
>     - $i(([-2][-2]))$
>     - $i(([-2][2\ 0]))$
>     - $i(([3\ 0][3\ 0]))$
>     - $i(([3\ 0][-2]))$
>     - $i(([3\ 0][2\ 0]))$
>
> **Expected Output:**
>
>   - A positive response with the appropriate path. The output can be inspected by hand.

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
