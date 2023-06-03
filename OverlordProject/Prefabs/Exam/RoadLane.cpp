#include "stdafx.h"
#include "RoadLane.h"
#include "Prefabs/Exam/Car.h"
#include "Prefabs/Exam/Coin.h"

RoadLane::RoadLane(int count, int width)
{
	m_Count = count;
	m_Width = width;


}

std::vector<bool> RoadLane::GetObstacles()
{
	return m_hasObstacle;
}

void RoadLane::RemoveCoin(Coin* coin)
{
	m_pCoins.erase(std::remove(m_pCoins.begin(), m_pCoins.end(), coin));
	
}

void RoadLane::Initialize(const SceneContext& /*sceneContext*/)
{
	//tag
	SetTag(L"RoadLane");

	//mesh
	/*m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(XMFLOAT4{ 0.5,0.5,0.5,1 });*/

	m_pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();

	m_pMaterial->SetDiffuseTexture(L"Textures/Exam/RoadLaneDiff.png");

	AddComponent(new ModelComponent(L"Meshes/Lane.ovm"));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	//GetTransform()->Translate(float(m_Width / 2), -2, float(1 * m_Count));
	GetTransform()->Translate(float(m_Width / 2), -1, float(1 * m_Count));

	GetTransform()->Scale(2, 1, 1);

	//Car
	/*GameObject* car =*/ 
	m_pCar = GetScene()->AddChild(new Car(m_Width, m_Count));

	//initalizeObstacles
	for (int i{}; i < m_Width; i++)
	{
		m_hasObstacle.push_back(false);
		m_hasCoin.push_back(false);
	}

	PlaceCoins();
}

void RoadLane::Update(const SceneContext& /*sceneContext*/)
{

}

void RoadLane::OnSceneDetach(GameScene* pScene)
{
	//cleanUp made gameobjects
	for (int i{}; i < m_pCoins.size();i++)
	{
		pScene->RemoveChild(m_pCoins.at(i), true);
	}

	pScene->RemoveChild(m_pCar, true);
}

void RoadLane::PlaceCoins()
{
	for (int i{}; i < m_Width; i++)
	{
		
		int randNumb = rand() % 10;

		if (randNumb == 0)
		{
			m_hasCoin.at(i) = true;
		}

		

		if (m_hasCoin.at(i) == true)
		{
			GameObject* coin = GetScene()->AddChild(new Coin(i, m_Count,this));

			m_pCoins.push_back(coin);
		}

	}
}

