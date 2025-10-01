#include "LevelSerializer.h"
#include <fstream>

#include "NodeFactory.h"
#include "../Debugging/Logger.h"
#include "Math/Vector.h"

World *LevelSerializer::Load(const std::string& Path)
{
	// Destroy our old world before we start to load our new one.
	// Note: Should this be a queued threaded event? If Old World -> Delete -> Done? -> Load New World
	if (g_pWorld != nullptr)
	{
		delete g_pWorld;
	}

	std::ifstream File(Path);
	if (File.fail())
	{
		g_Logger.LogError("Failed to open file %s", Path.c_str());
		return nullptr;
	}

	std::string JsonStr;
	std::string Line;
	while (std::getline(File, Line))
	{
		JsonStr += Line + ' ';
	}

	g_Logger.Log("Json Data: %s", JsonStr.c_str());

	rapidjson::Document JsonWorldData{};
	JsonWorldData.Parse(JsonStr.c_str());
	if (JsonWorldData.HasParseError())
	{
		g_Logger.LogError("Failed to parse Json from file %s. Malformed.", Path.c_str());
		return nullptr;
	}

	g_pWorld = new World();
	ParseTree(JsonWorldData);

	return g_pWorld;
}

bool LevelSerializer::Save(const std::string &FilePath)
{
	return false;
}

void LevelSerializer::ParseTree(const rapidjson::Document &Doc)
{
	const auto &NodeTree = Doc["Nodes"].GetArray()[0];

	const char *RootNodeClass = NodeTree["Type"].GetString();

	if (strcmp(RootNodeClass, ROOT) != 0)
	{
		g_Logger.LogError("Failed to get the WorldRoot. Got %s instead", NodeTree["Type"].GetString());
		return;
	}

	ParseNode(NodeTree, nullptr);
}

void LevelSerializer::ParseNode(const rapidjson::GenericValue<rapidjson::UTF8<>> &ChildNode, Node *Parent)
{
	const char *NodeClassName = ChildNode["Type"].GetString();
	const char *NodeHeirarchyName = ChildNode["Name"].GetString();

	const auto &Pos = ChildNode["Transform"]["Pos"].GetArray();
	const auto &Rot = ChildNode["Transform"]["Rot"].GetArray();;
	const auto &Scale = ChildNode["Transform"]["Scale"].GetArray();;
	Transform NT{Vec3ToArray(Pos), Vec4ToArray(Rot), Vec3ToArray(Scale)};

	Node *WorldNode;

	auto it = GetNodeRegistry().find(NodeClassName);
	if (it != GetNodeRegistry().end())
	{
		WorldNode = it->second(Parent, NodeHeirarchyName, NT);
	}
	else
	{
		g_Logger.LogError("Unknown node type: %s. Bypassing.", NodeClassName);
		WorldNode = new Node("InvalidObject", Transform{});
	}

	// Deserialize all of the data stored on our Node and dump it into our Node.
	if (ChildNode.HasMember("Data") && ChildNode["Data"].IsObject())
	{

		const auto& NodeData = ChildNode["Data"].GetObject();
		WorldNode->Deserialize(NodeData);
	}

	if (Parent)
		Parent->AddChild(WorldNode);

	// Recursively parse children
	if (ChildNode.HasMember("Children"))
	{
		const auto &Children = ChildNode["Children"].GetArray();
		for (const auto &Node: Children)
		{
			ParseNode(Node, WorldNode);
		}
	}
}

const Vec3 LevelSerializer::Vec3ToArray(rapidjson::GenericArray<true, rapidjson::GenericValue<rapidjson::UTF8<>>> JsonArray)
{
	return Vec3(
		JsonArray[0].GetFloat(),
		JsonArray[1].GetFloat(),
		JsonArray[2].GetFloat());
}

const Vec4 LevelSerializer::Vec4ToArray(rapidjson::GenericArray<true, rapidjson::GenericValue<rapidjson::UTF8<> > > JsonArray)
{
	return Vec4(
		JsonArray[0].GetFloat(),
		JsonArray[1].GetFloat(),
		JsonArray[2].GetFloat(),
		JsonArray[3].GetFloat());
}

LevelSerializer g_LevelSerializer;
