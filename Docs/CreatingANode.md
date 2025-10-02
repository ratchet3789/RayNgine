# Creating A Node
Relatively simple, pretty easy, a few steps.

I promise it's not painful.

## Creating your C++ Class
Literally just create a C++ class and inherit Node

Then you just need to add this to ensure we automatically call the Node constructor
```cpp
public:
    using Node::Node;
```
or just add it to your constructor.

## Variable Serialization
``DECLARE_DATA_TABLE(T)``
creates a Field Descriptor that lets our Reflection System know at compile time that this object exists and may potentially have variables.

We also took a page out of Source's book and to define variables that can be serialized you need to define a data table.
Its pretty easy. In our example I've defined a class called Circle2D and fed in the Velocity and CircleRadius, we inform it of the Class we're calling it from, the Type this variable is (from a pre-defined list of types stored in Node.h) and we have a void ptr at the end incase we need to do any callbacks.

Realistically you probably won't use the variable at the end.
```cpp
START_DATA_TABLE(Circle2D)
	DATA_TABLE_ENTRY("Velocity", Circle2D, Velocity, FIELD_VEC3, nullptr)
	DATA_TABLE_ENTRY("CircleRadius", Circle2D, CircleRadius, FIELD_FLOAT, nullptr)
END_DATA_TABLE()
```

If you want the useful "Print Class" functionality you can also add this to the header below the class.

``REGISTER_NODE(Circle2D)``