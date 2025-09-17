//
// Created by addic on 17/09/2025.
//

#ifndef RAYLIBFPS_LEVELLOADER_H
#define RAYLIBFPS_LEVELLOADER_H
#include "World.h"
#include <rapidjson/document.h>

class LevelLoader
{
public:
	std::unique_ptr<World> Load(const char* Path);
	void ParseNode(World* _World, const rapidjson::Document Doc);
};


#endif //RAYLIBFPS_LEVELLOADER_H