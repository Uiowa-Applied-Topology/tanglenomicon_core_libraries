---
date: 2024-09-18
authors:
    - Joe Starr
contact: example@example.com
abstract: A unit description for computation of template.
---

# Unit Description: Template

```{note}
A block diagram for the component under development
```

```mermaid
classDiagram
    comp_template --|> computation
    comp_template_config_t --|> notation_template
    comp_template_config_t --|> comp_config_t
    comp_template_result_t --|> comp_result_t
    comp_template *-- comp_template_config_t
    comp_template *-- comp_template_result_t

    class computation {
        <<interface>>
    }

    class comp_template {
    <<>>
    }

    class notation_template{
    <<>>
    }

    class comp_template_config_t {
    <<struct>>
    - notation_template

    }
    class comp_template_result_t {
    <<struct>>
    - notation_template

    }

    class comp_config_t {
    <<interface>>

    }


```

## Language

```{note}
A description of the language the feature is implemented in.
```

## Implements

```{note}
A list of interfaces implemented by the feature.
```

-   [Computation Interface](../../docs/unit_description/computation-interface.md)

## Uses

```{note}
A list of components and libraries used by the feature.
```

## External Libraries

```{note}
A list of external components and libraries used by the feature.
```

## Functionality

### Public

#### Structures

##### config structure

```
A struct description of the computation config.
```

##### result structure

```
A struct description of the computation config.
```

#### Functions

##### comp_config function

```{note}
A function description for the config interface.
```

##### comp_compute function

```{note}
A function description for the compute interface.
```

##### comp_result function

```{note}
A function description for the result interface.
```

### Private

#### Structures

```
A list of private structures for the notation.
```

#### Function

```{note}
A list of function descriptions for private functions.
```

## Validation

```{note}
This section contains the unit level test description for the component. Each
test that will be implemented should be described here. This should happen at
the same time you are describing the functionality above, NOT after implementing
the features.
```

### Public interface #1

#### Positive Tests

```{note}
A list of positive test cases for the public interface. A positive test
validates that the good path works. Feed the interface good input and expect
good output.
```

##### Test #1

```{note}
A description of the goal of the unit test and how it will be carried out.
```

###### Inputs:

```{note}
A list/description of input for the test.
```

###### Expected Output:

```{note}
A description of what output is expected to be for the test.
```

#### Negative Tests

```{note}
A list of negative test cases for the public interface. A negative test
validates that the bad path works. Feed the interface bad input and expect
correct error handling. This might include boundary checking a list or malformed
input strings.
```

##### Test #2

```{note}
A description of the goal of the unit test and how it will be carried out.
```

###### Inputs:

```{note}
A list/description of input for the test.
```

## Doxygen Documentation

```{doxygenfile} template.h

```

```{doxygenfile} template.c

```

## Bibliography

```{bibliography}
   :filter: docname in docnames
```

```{raw} latex
    \newpage
```
