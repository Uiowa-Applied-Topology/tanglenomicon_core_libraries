# Use Case: Storage Interface

## Brief

A storage interface describes an interface for reading and writing key value
pairs to/from other components. The most common use case for this is writing out
stringified results from generator and computation components. It's important to
use callback functions for reading a writing, since libraries are often called
from high-level languages. Using callbacks and high-level languages gives some
degree of flexibility without increasing the low-level complexity.

```{raw} latex
    \newpage
```
