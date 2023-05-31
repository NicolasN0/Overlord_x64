#include "stdafx.h"
#include "LaneManager.h"
#include "Prefabs/Exam/GrassLane.h"
#include "Prefabs/Exam/RoadLane.h"
#include "Prefabs/Exam/WaterLane.h"
#include "Prefabs/Exam/TrainLane.h"
#include "Prefabs/Exam/TreeLane.h"

LaneManager::LaneManager()
{
	
}

bool LaneManager::GetIsPassable(int posX, int posZ)
{
	//no out of bounds check
	if(posZ < 0 || posZ > m_pLanes.size() || posX > m_Width - 1 || posX < 0)
	{
		return false;
	}

	if(m_pLanes.at(posZ)->GetTag() == L"GrassLane")
	{
		GrassLane* lane = dynamic_cast<GrassLane*>(m_pLanes.at(posZ));
		return !lane->GetObstacles().at(posX);

	}else if(m_pLanes.at(posZ)->GetTag() == L"RoadLane")
	{
		RoadLane* lane = dynamic_cast<RoadLane*>(m_pLanes.at(posZ));
		return !lane->GetObstacles().at(posX);

	}else if (m_pLanes.at(posZ)->GetTag() == L"TrainLane")
	{
		TrainLane* lane = dynamic_cast<TrainLane*>(m_pLanes.at(posZ));
		return !lane->GetObstacles().at(posX);

	}else if (m_pLanes.at(posZ)->GetTag() == L"WaterLane")
	{
		WaterLane* lane = dynamic_cast<WaterLane*>(m_pLanes.at(posZ));
		return !lane->GetObstacles().at(posX);

	}

	return false;
}

int LaneManager::GetWidth()
{
	return m_Width;
}

void LaneManager::IncreasePlayerCount()
{
	m_PlayerCount += 1;
}

bool LaneManager::IsOnWater(int posX, int posZ)
{
	if(m_pLanes.at(posZ)->GetTag() == L"WaterLane")
	{

		WaterLane* lane = dynamic_cast<WaterLane*>(m_pLanes.at(posZ));

		return !lane->GetLilys().at(posX);

	}
	return false;
}



void LaneManager::Initialize(const SceneContext& /*sceneContext*/)
{
	//for(int i{}; i < 7; i++)
	//{
	//	//MakeGrassLane();
	//	//MakeRoadLane();
	//	//MakeWaterLane();
	//	MakeTrainLane();
	//}

	MakeStarterTreeLanes();


	for (int i{}; i < 3; i++)
	{
		MakeGrassLane();
		MakeRoadLane();
		MakeWaterLane();
		MakeTrainLane();
	}
	
}

void LaneManager::Update(const SceneContext& /*sceneContext*/)
{
	//-2 is seeing one lane infront
	if(m_PlayerCount > m_pLanes.size() - 9)
	{
		//UpdateLanes();
		MakeRandomLane();
	}

	//m_TestTimer += sceneContext.pGameTime->GetElapsed();
	//if(m_TestTimer > 1.f)
	//{
	//	//MakeGrassLane();
	//	MakeRandomLane();
	//	m_TestTimer = 0;
	//}
	
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

void LaneManager::MakeWaterLane()
{
	GameObject* lane = GetScene()->AddChild(new WaterLane(m_LaneCounter, m_Width));
	AddChild(lane);
	m_pLanes.push_back(lane);
	//dont use size when making new one so i can still clean up m_pLanes
	m_LaneCounter++;
}

void LaneManager::MakeTrainLane()
{
	GameObject* lane = GetScene()->AddChild(new TrainLane(m_LaneCounter, m_Width));
	AddChild(lane);
	m_pLanes.push_back(lane);
	//dont use size when making new one so i can still clean up m_pLanes
	m_LaneCounter++;
}

void LaneManager::MakeRandomLane()
{
	int randLane = rand() % 4;
	switch(randLane)
	{

		case 0:
			MakeGrassLane();
			break;
		case 1:
			MakeRoadLane();
			break;
		case 2:
			MakeWaterLane();
			break;
		case 3:
			MakeTrainLane();
			break;
	}

}

void LaneManager::UpdateLanes()
{
	/*for (int i{};i < 2;i++)
	{

		MakeGrassLane();
	}*/
}

void LaneManager::MakeStarterTreeLanes()
{
	for (int i{1}; i < 8;i++)
	{
		GetScene()->AddChild(new TreeLane(-1*i, m_Width));		
		
	}
}
