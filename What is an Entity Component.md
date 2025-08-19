# What (the fuck) is an Entity Component System

[Austin Morlan MVP](https://austinmorlan.com/posts/entity_component_system/)

## Entities
An Entity is simply an ID, it doesn't contain anything.

The ID is used as an index into an array of components.

An array is contiguous in memory which lends itself well to being the data structure of choice.

So the physics system migh thave a list of all entites that have a Transform, Rigidbody and Gravity component and use the Entitys ID 
as an index into the Transform array, into the Rigidbody array and into the Gravity array.

So conceptually its pretty simple...

__Entity__

An ID

__Component__

Struct of Data

__System__

Logic that operates on the components.

__Design Goals__
- Relatively simple and understandable
- Modern C++
- Minimal amount of if conditions
- Minimal virtual inheritance

## The Entity
An Entity is very simple.
```cpp
// Simple type alias
using Entity = std::uint32_t;

// Define the size of arrays later
const Entity MAX_ENTITIES = 5000;
```
``You can of course make Entities and MAX_ENTITIES any size``

## The Component
A component is as simple as an entity. Its a struct with a small chunk of functionally related data.

Eg a __Transform__

```cpp
struct Transform
{
	Vec3 Position;
	Vec3 Rotation;
	Vec3 Scale;
}
```
Each component type (__Transform__, __Rigidbody__, etc) has a Unique ID given to it.
```
using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
```

## The Signature
As an entity is an ID we need to find a way to track which components an entity "has", and a way to track which components a system cares about.

For this a std::bitset was chosen (Modern C++ bitfield), called a Signature.

Each component type has a unique ID (starting from 0), which is used to represent a bit in the signature.

As an example, if __Transform__ has type 0, __Rigidbody__ has type 1 and __Gravity__ has type 2, an Entity that has those 3 components would have a signature of 0b111 (0111)

A system would also register its interest in certain components as another signature. Then its a simple bitwise comparison to ensure that an entities signature contains the system's signature (an entity might have more components than a system requires, which is fine, as long as it has __all__ of the components a system requires)

```cpp
using Signature = std::bitset<MAX_COMPONENTS>;
```

## Entity Manager
The __Entity Manager__ is in charge of distributing entity IDs and keeping a record of which are in use and which are not.

We chose to use a simple std::queue, where on startup the queue is initialized to contain every valid entity ID up to MAX_ENTITIES. When an entity is created it takes an ID from the front of the queue and when its destroyed it puts it at the back of the queue.

``So I'm chosing not to copy-paste this and rather write pseudo code so you can write it yourself. If you really need the OG code its in the link at hte top``

```
Class Entity Manager
	On Constructor Call...
		For each entity from 0 to Max Entities
			push our Entity
			(There's a sneaky bit of optimisation here the developer puts in. Hint: We don't do Entity entity(); as remember, Entities are uint32_t's)
		
	As Entity Create Entity
		Make sure our list of living entities aren't over the list of Max Entities

		Pop a new Entity from the Queue
		Increment our living count

		return our Entity

	Destroy Entity (Entity)
		Make sure our Entity is in range

		in our array of Signatures, get our Entity and .reset() it
		Push it onto teh back of the queue
		decrement our Living Entity count

	Set Signature(Entity, Signature)
		Make sure our entity is within range

		Put this entity's signature in our array of Signatures

	As Signature Get Signature
		Make sure our entity is within range
		get the Signature of our entity from the signature array.

Variables:
	std::queue of Entity called AvailableEntities
	std::array of Signature called Signatures
	uint32_t called Living Entity Count

```

## The Component Array

We need to create a data structure that is essentially a simple array, but is always a packed array, meaning it has no holes.
If an Entity is just an index into an array of components then its simple to grab the relevant component for an entity. But what happens when an Entity is destroyed? That index is no longer valid.

Remember the entire point of an ECS is to keep the data packed into memory, meaning you should be able to iterate over all the indices in teh array without needed any sort of ``if(valid)`` checks. When an entity is destroyed, the component data it had still exists in the arrays. If a system were to try to iterate over the array it would encounter stale data with no entity attached. For this reasonb we need to keep the array packed with valid data at all times.

Austin chose to solve this problem by keeping a mapping from Entity IDs to array indices. When accessing the array, you use the entity ID to look up the actual array index. Then when an entity is destroyed you take teh last valid element in teh array and move it into the deleted entity's spot and update the map so that the entity ID now points to the correct position. There's also a map from teh array indfex to an entity ID so that, when moving the last array element, you know whcih entity was using that index and can update its map.

Lets demonstrate the process visually

Lets assume that __MAX_ENTITIES__ is set to 5. The array starts empty, there is nothing in the maps and the size is 0

```
Start
--------
Array: []
Entity->Index: []
Index->Entity: []
Size: 0
```

We then add ac omponent with value A into Entity 0

Entity 0 maps to Index 0, and Index 0 maps to Entity 0
```
Add A to Entity 0
--------
Array: [A]

Entity->Index:
[0:0] Entity 0's data (A) is at Index 0

Index->Entity:
[0:0] Index 0 holds Entity 0's data (A)

Size: 1
```

We then add a component with Value B to Entity 1

Entity 1 maps to Index 1, and Index 1 maps to Entity 1
```
Array: [A B]

Entity->Index:
[0:0] Entity 0's data (A) is at Index 0
[1:1] Entity 1's data (B) is at Index 1

Index->Entity:
[0:0] Index 0 holds Entity 0's data (A)
[1:1] Index 1 holds Entity 1's data (B)

Size: 2
```

Do that a few more tims times til we have C and D as well.

Everything so far is packed into memory. Then we delete the value B from Entity 1. To keep it packed we move the last element (D) into the spot occupied by B and update the map.

```
Delete B (Index 1 and Data of Entity 1)
Array: [A D C ]

Entity->Index:
[0:0] Entity 0's data (A) is at Index 0
[3:1] Entity 3's data (D) is at Index 1
[2:2] Entity 1's data (C) is at Index 1

Index->Entity:
[0:0] Index 0 holds Entity 0's data (A)
[1:3] Index 1 holds Entity 3's data (D)
[2:2] Index 1 holds Entity 1's data (C)

Size: 3
```

We then delete D from Entity 3, moving the last element (C) into teh spot occupied by D

```
Delete D (Index 1 and Data of Entity 3)
Array: [A C]

Entity->Index:
[0:0] Entity 0's data (A) is at Index 0
[2:1] Entity 2's data (C) is at Index 1

Index->Entity:
[0:0] Index 0 holds Entity 0's data (A)
[1:2] Index 1 holds Entity 2's data (C)

Size: 2
```

```
Add E (Index 2 and Data of Entity 4 due to ABCD)
Array: [A C E]

Entity->Index:
[0:0] Entity 0's data (A) is at Index 0
[2:1] Entity 2's data (C) is at Index 1
[4:2] Entity 4's data (E) is at Index 2

Index->Entity:
[0:0] Index 0 holds Entity 0's data (A)
[1:2] Index 1 holds Entity 2's data (C)
[2:4] Index 2 holds Entity 4's data (E)

Size: 3
```

Now for the code
```
Class IComponentArray
	Public
		virtual Deconstructor defualt
		virtual EntityDestroyed(Entity) = 0;

Template typename T
class ComponentArray inherits IComponentArray

	InsertData(Entity, T)
		assert EntityToIndexMap find (Entity) equals Entity To Index Map End AND "Component added to same entity more than once

		create a new size_t index equal to the mSize
		add the new index to the Entity To Index Map at the Entity element
		add the entity to the index to entity map at the newIndex element
		add the component to teh component array at the newIndex element

	RemoveData(Entity)
		same assert as above

		create a new size_t "index of removed entity" equal to the entity index of entity to index map
		create a new size_t "index of last element" = mSize -1


```

## The Component Manager

## The System

## The System Manager

## The Coordinator

