#include "stdafx.h"
#include "LaneManager.h"
#include "Prefabs/Exam/GrassLane.h"

LaneManager::LaneManager()
{
}

void LaneManager::Initialize(const SceneContext& /*sceneContext*/)
{
	MakeGrassLane();
}

void LaneManager::Update(const SceneContext&)
{
}

void LaneManager::MakeGrassLane()
{
	AddChild(new GrassLane());
}
