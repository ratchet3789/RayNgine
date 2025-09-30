#pragma once

//#include <raymath.h>
#include <raylib.h>
#include <rapidjson/document.h>

#include <vector>
#include <string>

#include "../IDAllocator.h"
#include "../Math/Vector.h"
#include "../../Debugging/Logger.h"

#define DECLARE_NODE_CLASS(name) \
	static const char* StaticNodeClassName() { return #name; } \
	virtual const char* GetNodeClassName() const { return #name; }

enum FieldType
{
	FIELD_INT,
	FIELD_FLOAT,
	FIELD_BOOL,
	FIELD_VEC2,
	FIELD_VEC2I,
	FIELD_VEC3,
	FIELD_VEC3I,
	FIELD_VEC4,
	FIELD_VEC4I,
	FIELD_STRING,
	FIELD_VOID
};

struct FieldDesc
{
	const char *Name;
	size_t Offset; // offsetof(Class, Var)
	FieldType Type;
	void *Extra; // Optional Nested DataDesc, Function etc
};

#define CONCAT_DETAIL(x,y) x##y
#define CONCAT(x,y) CONCAT_DETAIL(x,y)

#define DECLARE_DATA_TABLE(T) \
	static FieldDesc CONCAT(s_, CONCAT(T, Fields))[]; \
	FieldDesc *GetDataTable() const override { return CONCAT(s_, CONCAT(T, Fields)); } ;

#define START_DATA_TABLE(T) \
	FieldDesc T::CONCAT(s_, CONCAT(T, Fields))[] = {

#define END_DATA_TABLE() \
	{nullptr, 0, FIELD_VOID, nullptr} /* Sentinel */ \
	};

#define DATA_TABLE_ENTRY(Name, T, Var, Type, Extra) \
	{ #Name, offsetof(T, Var), Type, Extra },

#define SERIALIZE_SCALAR(T, Addr, Field, Alloc, Doc) \
	{ \
		T* val = reinterpret_cast<T*>(Addr); \
		rapidjson::Value Key(Field->Name, Alloc); \
		rapidjson::Value Val(*val); \
		Doc.AddMember(Key, Val, Alloc);	\
	}

#define SERIALIZE_STRING(Addr, Field, Alloc, Doc) \
	{ \
		std::string* val = reinterpret_cast<std::string*>(Addr); \
		rapidjson::Value Key(Field->Name, Alloc); \
		rapidjson::Value Val(val->c_str(), static_cast<rapidjson::SizeType>(val->size()), Alloc); \
		Doc.AddMember(Key, Val, Alloc); \
	}

#define SERIALIZE_VEC2(T, Addr, Field, Alloc, Doc) \
	{ \
		T* val = reinterpret_cast<T*>(Addr); \
		rapidjson::Value Key(Field->Name, Alloc); \
		rapidjson::Value Arr(rapidjson::kArrayType); \
		Arr.PushBack(val->X, Alloc).PushBack(val->Y, Alloc); \
		Doc.AddMember(Key, Arr, Alloc); \
	}


#define SERIALIZE_VEC3(T, Addr, Field, Alloc, Doc) \
	{ \
		T* val = reinterpret_cast<T*>(Addr); \
		rapidjson::Value Key(Field->Name, Alloc); \
		rapidjson::Value Arr(rapidjson::kArrayType); \
		Arr.PushBack(val->X, Alloc).PushBack(val->Y, Alloc).PushBack(val->Z, Alloc); \
		Doc.AddMember(Key, Arr, Alloc); \
	}

#define SERIALIZE_VEC4(T, Addr, Field, Alloc, Doc) \
	{ \
		T* val = reinterpret_cast<T*>(Addr); \
		rapidjson::Value Key(Field->Name, Alloc); \
		rapidjson::Value Arr(rapidjson::kArrayType); \
		Arr.PushBack(val->X, Alloc).PushBack(val->Y, Alloc).PushBack(val->Z, Alloc).PushBack(val->W, Alloc); \
		Doc.AddMember(Key, Arr, Alloc); \
	}

class Node
{
public:
	DECLARE_NODE_CLASS(Node)

	Node(std::string Name, Transform _Transform);

	virtual ~Node() { g_IDAllocator.FreeIdentifier(UniqueID); };

	// Serialization

	virtual FieldDesc *GetDataTable() const { return nullptr; }

	virtual const rapidjson::Document Serialize()
	{
		rapidjson::Document Doc;
		Doc.SetObject();
		rapidjson::MemoryPoolAllocator<> &Alloc = Doc.GetAllocator();

		for (FieldDesc *Field = GetDataTable(); Field->Name != nullptr; ++Field)
		{
			char *base = reinterpret_cast<char *>(this);
			char *Addr = base + Field->Offset;

			switch (Field->Type)
			{
				case FIELD_INT:
					SERIALIZE_SCALAR(int, Addr, Field, Alloc, Doc);
					break;
				case FIELD_FLOAT:
					SERIALIZE_SCALAR(float, Addr, Field, Alloc, Doc);
					break;
				case FIELD_BOOL:
					SERIALIZE_SCALAR(bool, Addr, Field, Alloc, Doc);
					break;
				case FIELD_VEC2:
					SERIALIZE_VEC2(Vec2, Addr, Field, Alloc, Doc);
					break;
				case FIELD_VEC2I:
					SERIALIZE_VEC2(Vec2i, Addr, Field, Alloc, Doc);
					break;
				case FIELD_VEC3:
					SERIALIZE_VEC3(Vec3, Addr, Field, Alloc, Doc);
					break;
				case FIELD_VEC3I:
					SERIALIZE_VEC3(Vec3i, Addr, Field, Alloc, Doc);
					break;
				case FIELD_VEC4:
					SERIALIZE_VEC4(Vec4, Addr, Field, Alloc, Doc);
					break;
				case FIELD_VEC4I:
					SERIALIZE_VEC4(Vec4i, Addr, Field, Alloc, Doc);
					break;
				case FIELD_STRING:
					SERIALIZE_STRING(Addr, Field, Alloc, Doc);
					break;
				case FIELD_VOID:
					// Unsupported (RIP)
					g_Logger.LogWarning("Attempted to parse void type for %s", Field->Name);
					break;
				default:
					g_Logger.LogWarning("Attempted to parse undefined type for %s", Field->Name);
					break;
			}
		}
		return Doc;
	}
	virtual void Deserialize(const rapidjson::GenericValue<rapidjson::UTF8<> > &NodeData)
	{
		for (FieldDesc *Field = GetDataTable(); Field->Name != nullptr; ++Field)
		{
			char *base = reinterpret_cast<char *>(this);
			char *addr = base + Field->Offset;

			if (!NodeData.HasMember(Field->Name))
			{
				g_Logger.LogError("Failed to find and load member %s in %s", Field->Name, GetNodeClassName());
				continue;
			}

			switch (Field->Type)
			{
				case FIELD_INT:
				{
					int *val = reinterpret_cast<int *>(addr);
					*val = NodeData[Field->Name].GetInt();
				}
				break;
				case FIELD_FLOAT:
				{
					float *val = reinterpret_cast<float *>(addr);
					*val = NodeData[Field->Name].GetFloat();
				}
				break;
				case FIELD_BOOL:
				{
					bool *val = reinterpret_cast<bool *>(addr);
					*val = NodeData[Field->Name].GetBool();
				}
				break;
				case FIELD_VEC2:
				{
					Vec2 *val = reinterpret_cast<Vec2 *>(addr);
					auto NodeArr = NodeData[Field->Name].GetArray();
					if (NodeArr.Size() < 2)
						break;
					val->X = NodeArr[0].GetFloat();
					val->Y = NodeArr[1].GetFloat();
				}
				break;
				case FIELD_VEC2I:
				{
					Vec2i *val = reinterpret_cast<Vec2i *>(addr);
					auto NodeArr = NodeData[Field->Name].GetArray();
					if (NodeArr.Size() < 2)
						break;
					val->X = NodeArr[0].GetInt();
					val->Y = NodeArr[1].GetInt();
				}
				break;
				case FIELD_VEC3:
				{
					Vec3 *val = reinterpret_cast<Vec3 *>(addr);
					auto NodeArr = NodeData[Field->Name].GetArray();
					if (NodeArr.Size() < 3)
						break;
					val->X = NodeArr[0].GetFloat();
					val->Y = NodeArr[1].GetFloat();
					val->Z = NodeArr[2].GetFloat();
				}
				break;
				case FIELD_VEC3I:
				{
					Vec3i *val = reinterpret_cast<Vec3i *>(addr);
					auto NodeArr = NodeData[Field->Name].GetArray();
					if (NodeArr.Size() < 3)
						break;
					val->X = NodeArr[0].GetInt();
					val->Y = NodeArr[1].GetInt();
					val->Z = NodeArr[2].GetInt();
				}
				break;
				case FIELD_VEC4:
				{
					Vec4 *val = reinterpret_cast<Vec4 *>(addr);
					const auto NodeArr = NodeData[Field->Name].GetArray();
					if (NodeArr.Size() < 4)
						break;
					val->X = NodeArr[0].GetFloat();
					val->Y = NodeArr[1].GetFloat();
					val->Z = NodeArr[2].GetFloat();
					val->W = NodeArr[3].GetFloat();
				}
				break;
				case FIELD_VEC4I:
				{
					Vec4i *val = reinterpret_cast<Vec4i *>(addr);
					auto NodeArr = NodeData[Field->Name].GetArray();
					if (NodeArr.Size() < 4)
						break;
					val->X = NodeArr[0].GetInt();
					val->Y = NodeArr[1].GetInt();
					val->Z = NodeArr[2].GetInt();
					val->W = NodeArr[3].GetInt();
				}
				break;
				case FIELD_STRING:
				{
					*reinterpret_cast<std::string *>(addr) = NodeData[Field->Name].GetString();
				}
				break;
				case FIELD_VOID:
					// Unsupported (RIP)
					g_Logger.LogWarning("Attempted to parse void type for %s", Field->Name);
					break;
				default:
					g_Logger.LogWarning("Attempted to parse undefined type for %s", Field->Name);
					break;
			}
		}
	}

	// Primarily Called in Editor
	void SetNewParent(Node *ParentNode);

	void AddChild(Node *ChildNode);

	void RemoveChild(Node *ChildNode);

	const IDHandle GetEntityID() const { return UniqueID; }

	// Operator Overloads
	bool operator==(const Node &B) const
	{
		return B.GetEntityID().Id == GetEntityID().Id && B.GetEntityID().Generation == UniqueID.Generation;
	}

	bool operator!=(const Node &B) const { return !(*this == B); }

	// Core
	Transform NodeTransform{};
	std::string GetName() const { return DisplayName; }

	// Base Node Calls
	// Called when object Spawned/Created
	virtual void BeginPlay()
	{
	}

	// Called Per-frame
	virtual void Tick(float DeltaTime)
	{
	}

	// Called per-Physics Tick
	virtual void FixedUpdate(float DeltaTime)
	{
	}

	// Called when Garbage Collected

	virtual void OnDestroy()
	{
	}

	// Called when Enabled by user via Enable()
	virtual void OnEnable()
	{
	}

	// Called when Disabled by user via Disable()
	virtual void OnDisable()
	{
	}

	// Called when Key Press registered in Window
	virtual void KeyPressed(KeyboardKey Key)
	{
	}

	inline bool CanTick() { return bCanTick; }

	Node *Parent;
	std::vector<Node *> Children{};

	bool bEnabled{true};
	bool bCanReorderNode{true};
	bool bCanTick{true};

protected:
	std::string DisplayName;
	IDHandle UniqueID;

private:
	void OnDestroy_World();

	void OnEnable_World();

	void OnDisable_World();
};