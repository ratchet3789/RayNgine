#pragma once
#include "World.h"
#include <rapidjson/document.h>

#define ROOT "WorldRoot"

class LevelLoader
{
public:
	World* Load(std::string Path);
	// Parse the entire tree
	void ParseTree(const rapidjson::Document& Doc);
	// Parse each Node recursively (Node -> Has Child? Parse Node(Child))
	void ParseNode(const rapidjson::GenericValue<rapidjson::UTF8<>>& ChildNode, Node* Parent);

	const Vec4 Vec4ToArray(rapidjson::GenericArray<true, rapidjson::GenericValue<rapidjson::UTF8<>>> JsonArray);
	const Vec3 Vec3ToArray(rapidjson::GenericArray<true, rapidjson::GenericValue<rapidjson::UTF8<>>> JsonArray);
};

extern LevelLoader g_LevelLoader;