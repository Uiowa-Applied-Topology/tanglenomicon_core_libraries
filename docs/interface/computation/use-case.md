# Use Case

The computation interface defines the general form for a component used to perform a knot operation.
When the computation component is invoked, it produces a single output. The computation component
does not allocate memory, it must be configured with sufficient buffer space to successfully
execute. Input data for a computation component shall not be mutated.
