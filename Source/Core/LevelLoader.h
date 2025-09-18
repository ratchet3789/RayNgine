//
// Created by addic on 17/09/2025.
//

#ifndef RAYLIBFPS_LEVELLOADER_H
#define RAYLIBFPS_LEVELLOADER_H
#include "World.h"
#include <rapidjson/document.h>

struct TransformData
{
	float Pos[3];
	float Rot[4];
	float Scale[3];
};

struct NodeData
{
	std::string TypeStr;
	std::string ObjectName;
	TransformData Transform;
	NodeData* Parent;
	NodeData();
};

class LevelLoader
{
public:
	std::unique_ptr<World> Load(std::string Path);
	// Parse the entire tree
	void ParseTree(const rapidjson::Document& Doc);
	// Parse each Node recursively (Node -> Has Child? Parse Node(Child))
	void ParseNode(const rapidjson::GenericValue<rapidjson::UTF8<>>& ChildNode, NodeData* ParentNode);
	void ParseDataToWorldObjects();

private:
	std::vector<NodeData> Nodes;
};

extern LevelLoader g_LevelLoader;

#endif //RAYLIBFPS_LEVELLOADER_H