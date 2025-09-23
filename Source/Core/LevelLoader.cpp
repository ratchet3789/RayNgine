#include "LevelLoader.h"
#include <fstream>

#include "NodeFactory.h"
#include "../Debugging/Logger.h"

World *LevelLoader::Load(std::string Path)
{
	std::ifstream File(Path);
	if (File.fail())
	{
		g_Logger.LogError("Failed to open file %s", Path.c_str());
		return nullptr;
	}

	std::string JsonStr{""};
	std::string Line{""};
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

void LevelLoader::ParseTree(const rapidjson::Document &Doc)
{
	const auto &NodeTree = Doc["Nodes"].GetArray()[0];

	const char* RootNodeClass = NodeTree["Type"].GetString();

	if (strcmp(RootNodeClass, ROOT) != 0)
	{
		g_Logger.LogError("Failed to get the WorldRoot. Got %s instead", NodeTree["Type"].GetString());
		return;
	}

	ParseNode(NodeTree, nullptr);
}

void LevelLoader::ParseNode(const rapidjson::GenericValue<rapidjson::UTF8<> > &ChildNode, Node* Parent)
{
	const char *NodeClassName = ChildNode["Type"].GetString();
	const char *NodeHeirarchyName = ChildNode["Name"].GetString();

	const auto &Pos = ChildNode["Transform"]["Pos"].GetArray();
	const auto &Rot = ChildNode["Transform"]["Rot"].GetArray();;
	const auto &Scale = ChildNode["Transform"]["Scale"].GetArray();;
	NodeTransform NT{Vec3ToArray(Pos), Vec4ToArray(Rot), Vec3ToArray(Scale)};

	Node* _Node;

	auto it = GetNodeRegistry().find(NodeClassName);
	if (it != GetNodeRegistry().end())
	{
		_Node = it->second(Parent, NodeHeirarchyName, NT);
	}
	else
	{
		g_Logger.LogError("Unknown node type: %s. Bypassing.", NodeClassName);
		_Node = new Node("InvalidObject", NodeTransform{});
	}

	if (Parent)
		Parent->AddChild(_Node);

	if (ChildNode.HasMember("Children"))
	{
		const auto &Children = ChildNode["Children"].GetArray();
		for (const auto &Node: Children)
		{
			ParseNode(Node, _Node);
		}
	}
}

const Vector3 LevelLoader::Vec3ToArray(
	rapidjson::GenericArray<true, rapidjson::GenericValue<rapidjson::UTF8<> > > JsonArray)
{
	return Vector3(
		JsonArray[0].GetFloat(),
		JsonArray[1].GetFloat(),
		JsonArray[2].GetFloat());
}

const Vector4 LevelLoader::Vec4ToArray(
	rapidjson::GenericArray<true, rapidjson::GenericValue<rapidjson::UTF8<> > > JsonArray)
{
	return Vector4(
		JsonArray[0].GetFloat(),
		JsonArray[1].GetFloat(),
		JsonArray[2].GetFloat(),
		JsonArray[3].GetFloat());
}

LevelLoader g_LevelLoader;
