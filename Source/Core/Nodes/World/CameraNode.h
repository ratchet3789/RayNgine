// Created by Coby on 2026/05/23.

#ifndef SHOOTER_RAYLIB_CAMERANODE_H
#define SHOOTER_RAYLIB_CAMERANODE_H

#include "raylib.h"
#include "../Node.h"
#include "../../Math/Vector.h"
#include "../../NodeFactory.h"

class CameraNode : public Node
{
public:
	using Node::Node;

	Vec3 m_OriginPosition;
	Vec3 m_Up{0.0f,0.0f,1.0f};
	Vec3 m_Forward{1.0f, 0.0f, 0.0f};
	float m_Fov{60.0f};
	CameraProjection m_Projection{CAMERA_PERSPECTIVE};

	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	void KeyPressed(KeyboardKey Key) override;

protected:
	Camera3D m_Camera;
	DECLARE_DATA_TABLE(CameraNode)
};

REGISTER_NODE(CameraNode)

START_DATA_TABLE(CameraNode)
	DATA_TABLE_ENTRY("OriginPosition", CameraNode, m_OriginPosition, FIELD_VEC3, nullptr)
	DATA_TABLE_ENTRY("Up", CameraNode, m_Up, FIELD_VEC3, nullptr)
	DATA_TABLE_ENTRY("Forward", CameraNode, m_Forward, FIELD_VEC3, nullptr)
	DATA_TABLE_ENTRY("FOV", CameraNode, m_Fov, FIELD_FLOAT, nullptr)
END_DATA_TABLE()

#endif //SHOOTER_RAYLIB_CAMERANODE_H
