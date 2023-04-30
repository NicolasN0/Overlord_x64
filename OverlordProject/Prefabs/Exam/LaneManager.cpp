#include "stdafx.h"
#include "LaneManager.h"
#include "Prefabs/Exam/GrassLane.h"

LaneManager::LaneManager()
{
	
}

bool LaneManager::GetIsPassable(int posX, int posZ)
{
	GrassLane* lane = dynamic_cast<GrassLane*>(m_pLanes.at(posZ));
	return !lane->GetObstacles().at(posX);
}

int LaneManager::GetWidth()
{
	return m_Width;
}

void LaneManager::Initialize(const SceneContext& /*sceneContext*/)
{
	for(int i{}; i < 7; i++)
	{
		MakeGrassLane();
	}
	
}

void LaneManager::Update(const SceneContext&)
{
}

void LaneManager::MakeGrassLane()
{
	
	GameObject* lane = GetScene()->AddChild(new GrassLane(m_LaneCounter, m_Width));
	
	m_pLanes.push_back(lane);
	//dont use size when making new one so i can still clean up m_pLanes
	m_LaneCounter++;
}
