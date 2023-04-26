#include "stdafx.h"
#include "LaneManager.h"
#include "Prefabs/Exam/GrassLane.h"

LaneManager::LaneManager()
{
}

void LaneManager::Initialize(const SceneContext& /*sceneContext*/)
{
	MakeGrassLane();
	/*MakeGrassLane();
	MakeGrassLane();*/
}

void LaneManager::Update(const SceneContext&)
{
}

void LaneManager::MakeGrassLane()
{
	/*GameObject* lane = new GrassLane();
	GetScene()->AddChild(lane);*/

	GameObject* lane = GetScene()->AddChild(new GrassLane());
	


	//AddChild(lane);
	m_pLanes.push_back(lane);
	
}
