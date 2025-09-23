# DIY Engine

## Entry Point

The entry point of our Program sits at Shooter_Raylib.cpp.

This...
- Loads our default level
- Creates our Window

## INI Parser

The INI Parser...
- loads configs from unique INI files
- supports comments and malformed INIs 

## Window

Handles the creation, destruction and render loop for the window.

## World

The concept of a "Level" sits in a World and is 100% ripped off from the Unreal Engine base understanding of what a world is.

The world holds all of our Active and Inactive nodes, it spawns and destroys nodes, handles their state and processes events like Begin and End Play, Tick, Destroyed. The TLDR is that World is the lifecycle of our actual game engine.

## Level Loader

This extracts the DOM from the JSON object, converts it into Node data and then using our Node Factory spawns each node into the world.

## Node Factory

The Node Factory is a compile time system that allows us to define our Node types in our Node CPP files. This means that ``REGISTER_NODE(T)`` registers whatever cool new Node (Actor, Entity etc) object you create into our world and lets the LevelLoader acknowledge its data to then send to the World to spawn as a defined type rather than a <T> type.

This system exists as we don't have any form of reflection that allows us to just parse T at runtime.

## ID Allocator

The ID allocator is our system pool in the engine. It holds a queue of IDs and their generations

Where... 

ID = The  unique identifier of a Node, this cannot be used more than once at a time, eg there cannot be more than 1 node 4's in a World ever.

Generation = This number increments when you call Destroy on a Node. So if we have a Player with the ID 4 and they die we hit this 3 step plan. 1. We destroy them, this cleans up all of their memory and re-adds their ID (4) to the pool. 2. We Increment the Generation ID of that ID (4), so if we we're on the 1st generation of 4 we'd go from 4,0 to 4,1. This means for example if we had an NPC following that Player in a Multiplayer session and the player died then we reassigned ID 4 to a Butterfly Particle Effect, if the NPC tried to find that player again it would be looking for 4,0 not 4,1 so it wouldn't run off and try catch the butterfly 

When we Destroy an Object the World adds the ID back to a pool of inactive but used IDs. We do this so we don't end up in a 5+ hour session with over 4,294,967,296 Node references for things that have been destroyed. We also utilize Unsigned 32-bit Integers for this reason, more is better for a 4 byte vs 2 byte argument.

## Node

Node is the base of what we understand Actors to be in Unreal or GameObject's in Unity.

The Node is the underlying class that runs all of the logic in the World, so if you wanted to create a Player Node you'd create a PlayerController and extend Node. Then when we place it in the world and save that .JSON level then we utilize ``REGISTER_NODE(T)`` in our PlayerController to define a class and when we load with the LevelLoader we can link our PlayerController as a string to our PlayerController as a C++ Class and spawn an object with a Unique ID.

The Node is essentially the result of a love triangle between the World, NodeFactory and LevelLoader that results in an object in the world that can run unique logic.