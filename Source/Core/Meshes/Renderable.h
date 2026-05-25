//
// Created by addic on 2026/05/23.
//

#ifndef SHOOTER_RAYLIB_RENDERABLE_H
#define SHOOTER_RAYLIB_RENDERABLE_H

#include "raylib.h"

#include <string>
#include <vector>

/*
 * Given that we're extending the pre-existing RayLib system into a more C++ based polymorphic system
 * we have to define objects in a way that steps around the existing RayLib system, so things like
 * Meshes, Materials, Textures all have to be stored internally as Serialized Renderables
 * We also then want to support Serialization for these objects so we can point to where they exist on device.
 */

/*
 * The way we store data is per-level. We use LibZip to compress the files and a pre-loaded 128 character password
 * to encrypt the zip files.
 * The Encryptor works like this
 * When we run it to compress the games data it goes through all of the .JSON level files and builds a map for each
 * It then compares maps and if it finds any duplicate assets it creates a new Map of General assets.
 * It then mirrors those raw asset directories from our development directory into our ZIP files
 * It calls these the level name .WLD (Wheres the Level Data) and then encrypts them with AES 256 encryption from a password
 * Each level has its own WLD asset, eg "ExampleLevel" is ExampleLevel.wld and contains all the level geo and everything else
 * required to create the level and world.
 * Anything generalized will exist in the Common.WLD directory.
 * stored in a .h file (we're not too concerned about security) and then puts them in a Data directory next to the .exe
 * When we scan for the data in the .exe we have a 3 step failure process
 * 1. We scan the compressed WLD file first
 * 2. We scan the Common WLD assets file
 * 3. We scan your Loose Assets directory.
 */

#define StaticMesh SerializedMeshStatic
#define DynamicMesh SerializedMeshDynamic

#define FMT_MODEL .mdl
#define FMT_AUDIO .af
#define FMT_TEXTURE .tx
#define FMT_MATERIAL .mat

namespace PHYSICS_TEMP_MOVEME
{
	enum EPhysicsCollisionState
	{
		PhysCollisionState_NonSolid,
		PhysCollisionState_Trigger,
		PhysCollisionState_BoundingBox,
		PhysCollisionState_ConvexShape
	};

	class SerializedConvexShape
	{
		std::vector<uint32_t> VertexPoints;
		std::vector<uint32_t> TriGroups;
		std::vector<uint32_t> Faces;
	};
};

class SerializedMaterial;
class SerializedMeshStatic;
class SerializedMeshDynamic;
class SerializedTexture;
class SerialziedMesh;

/*
 * Serialized Mesh is a generic implementation of what a Mesh is
 * Where a Static Mesh is a mesh that will NEVER move. Static Meshes have specific modifiers like the lighting applying Lightmaps directly onto them, ensuring they have fully static geometry etc
 * Dynamic Meshes use realtime lighting, have physics updates and manage their data in real time, they can also be Skeletal Objects like NPCs
 */
class SerializedMesh
{
public:
	Model* m_Model;
	SerializedMaterial* m_Material;
	std::string m_MeshPath;
	bool m_ReceivesShadows{true};
	bool m_CastsShadows{true};
	PHYSICS_TEMP_MOVEME::EPhysicsCollisionState m_CollisionState{PHYSICS_TEMP_MOVEME::PhysCollisionState_ConvexShape};
	int m_LodSteps{4};
	std::vector<float> m_LodDistances{ 100,200,400,600,1000 };
	bool m_DoesLodFade{false};

	Transform m_MeshRelativeTransform;

	const Model* GetModel() const { return m_Model; };
	void SetModel(Model* newModel) { m_Model = newModel;}

	const Mesh* GetMeshes() const { return m_Model->meshes;}
};

class SerializedMeshStatic : public SerializedMesh
{
};

class SerializedMeshDynamic : public SerializedMesh
{
	bool m_UsesDynamicLighting{false};

	// NPC lighting and Logic here!
};

/*
 * A serialized Material is essentially a reference to a Texture with modifiers.
 * In the short term its just a wrapper around a texture and a way to transfer the RayLib material across the engines Serialization border
 * In the long term it will be similar to Unreal's system.
 */
class SerializedMaterial
{
	Material m_Material;
	std::string m_MaterialPath;
	SerializedTexture* m_Texture;
	int m_MaxMips{5};
};

class SerializedTexture
{
	Texture2D m_Texture;
	std::string m_TexturePath;
};

#endif //SHOOTER_RAYLIB_RENDERABLE_H
