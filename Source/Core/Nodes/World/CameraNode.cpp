// Created by Coby on 2026/05/23.

#include "CameraNode.h"


void CameraNode::BeginPlay()
{
	m_Camera.position = VECTOR3_TO_RAYLIB(m_OriginPosition);
	m_Camera.target = VECTOR3_TO_RAYLIB(m_Forward);
	m_Camera.up = VECTOR3_TO_RAYLIB(m_Up);
	m_Camera.fovy = m_Fov;
	m_Camera.projection = m_Projection;
}

void CameraNode::Tick(float DeltaTime)
{
	Node::Tick(DeltaTime);
}

void CameraNode::KeyPressed(KeyboardKey Key)
{
	Node::KeyPressed(Key);
}
