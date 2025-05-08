---
date: 2024-09-18
authors:
  - Joe Starr
contact: example@example.com
abstract: A unit description for notation of template.
---

# Unit Description: Template

```{note}
A block diagram for the component under development
```

```mermaid
classDiagram
    note_template --|> notation
    note_template *-- note_template_t
    note_template_t *-- note_template_node_t
    note_template_node_t *-- note_template_node_enum

    class note_template_t {
        <<struct>>
        note_template_node_t* root
    }

    class note_template_node_enum {
        <<enum>>
    }

    class note_template_node_t {
        <<struct>>
    }

    class notation {
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

- [Notations Interface](../../docs/unit_description/notation-interface.md)

## Uses

```{note}
A list of compnents and libraries used by the feature.
```

## External Libraries

```{note}
A list of external compnents and libraries used by the feature.
```

## Functionality

### Public

#### Structures

##### notation structure

```
A struct description of the notation structure.
```

#### encode function

```{note}
A function description for the encode interface.
```

#### decode function

```{note}
A function description for the decode interface.
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
A description of what ourput is expected to be for the test.
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


## Bibliography

```{bibliography}
   :filter: docname in docnames
```

```{raw} latex
    \newpage
```
