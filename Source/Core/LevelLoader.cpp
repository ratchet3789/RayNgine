#include "LevelLoader.h"
#include <fstream>

#include "../Debugging/Logger.h"

std::unique_ptr<World> LevelLoader::Load(std::string Path)
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

	ParseTree(JsonWorldData);
	ParseDataToWorldObjects();
	return nullptr;
}

void LevelLoader::ParseTree(const rapidjson::Document &Doc)
{
	const auto &NodeTree = Doc["Nodes"].GetArray()[0];
	ParseNode(NodeTree, nullptr);

}

void LevelLoader::ParseNode(const rapidjson::GenericValue<rapidjson::UTF8<>>& ChildNode, NodeData* ParentNode)
{
	NodeData ND;
	ND.TypeStr = ChildNode["Type"].GetString();
	ND.ObjectName = ChildNode["Name"].GetString();

	TransformData TD;
	const auto &Pos = ChildNode["Transform"]["Pos"].GetArray();
	const auto &Rot = ChildNode["Transform"]["Rot"].GetArray();;
	const auto &Scale = ChildNode["Transform"]["Scale"].GetArray();;

	TD.Pos[0] = Pos[0].GetFloat();
	TD.Pos[1] = Pos[1].GetFloat();
	TD.Pos[2] = Pos[2].GetFloat();

	TD.Rot[0] = Rot[0].GetFloat();
	TD.Rot[1] = Rot[1].GetFloat();
	TD.Rot[2] = Rot[2].GetFloat();
	TD.Rot[3] = Rot[3].GetFloat();

	TD.Scale[0] = Scale[0].GetFloat();
	TD.Scale[1] = Scale[1].GetFloat();
	TD.Scale[2] = Scale[2].GetFloat();

	ND.Transform = TD;
	Nodes.push_back(ND);

	if (ChildNode.HasMember("Children"))
	{
		const auto& Children = ChildNode["Children"].GetArray();
		for (const auto& Node : Children)
		{
			ParseNode(Node, &ND);
		}
	}
}

void LevelLoader::ParseDataToWorldObjects()
{
}

LevelLoader g_LevelLoader;
