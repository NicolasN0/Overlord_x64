#include "stdafx.h"
#include "LaneManager.h"
#include "Prefabs/Exam/GrassLane.h"
#include "Prefabs/Exam/RoadLane.h"

LaneManager::LaneManager()
{
	
}

bool LaneManager::GetIsPassable(int posX, int posZ)
{
	//GrassLane* lane = dynamic_cast<GrassLane*>(m_pLanes.at(posZ));
	RoadLane* lane = dynamic_cast<RoadLane*>(m_pLanes.at(posZ));
	return !lane->GetObstacles().at(posX);
}

int LaneManager::GetWidth()
{
	return m_Width;
}

void LaneManager::IncreasePlayerCount()
{
	m_PlayerCount += 1;
}

void LaneManager::Initialize(const SceneContext& /*sceneContext*/)
{
	for(int i{}; i < 7; i++)
	{
		//MakeGrassLane();
		MakeRoadLane();
	}
	
}

void LaneManager::Update(const SceneContext& /*sceneContext*/)
{
	/*if(m_PlayerCount > m_pLanes.size() - 2)
	{
		UpdateLanes();
	}*/

	/*m_TestTimer += sceneContext.pGameTime->GetElapsed();
	if(m_TestTimer > 2)
	{
		MakeGrassLane();
		m_TestTimer = 0;
	}*/
	
}

void LaneManager::MakeGrassLane()
{
	
	GameObject* lane = GetScene()->AddChild(new GrassLane(m_LaneCounter, m_Width));
	//AddChild(lane);
	//GameObject* lane = AddChild(new GrassLane(m_LaneCounter, m_Width));
	AddChild(lane);
	m_pLanes.push_back(lane);
	//dont use size when making new one so i can still clean up m_pLanes
	m_LaneCounter++;
}

void LaneManager::MakeRoadLane()
{
	GameObject* lane = GetScene()->AddChild(new RoadLane(m_LaneCounter,m_Width));
	AddChild(lane);
	m_pLanes.push_back(lane);
	//dont use size when making new one so i can still clean up m_pLanes
	m_LaneCounter++;
}

void LaneManager::UpdateLanes()
{
	/*for (int i{};i < 2;i++)
	{

		MakeGrassLane();
	}*/
}
