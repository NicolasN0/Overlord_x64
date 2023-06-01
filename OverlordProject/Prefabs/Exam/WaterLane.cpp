#include "stdafx.h"
#include "WaterLane.h"
#include "Prefabs/Exam/Lily.h"

WaterLane::WaterLane(int count, int width)
{
	m_Count = count;
	m_Width = width;


}

std::vector<bool> WaterLane::GetObstacles()
{
	return m_hasObstacle;
}

std::vector<bool> WaterLane::GetLilys()
{
	return m_hasLily;
}

void WaterLane::Initialize(const SceneContext& /*sceneContext*/)
{
	//tag
	SetTag(L"WaterLane");

	//mesh
	//standard lane setup
	m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(m_Color);

	AddComponent(new ModelComponent(L"Meshes/Lane.ovm", false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	//GetTransform()->Translate(float(m_Width / 2), -2, float(1 * m_Count));
	GetTransform()->Translate(float(m_Width / 2), -1, float(1 * m_Count));

	GetTransform()->Scale(2, 1, 1);

	//initalizeObstacles
	for (int i{}; i < m_Width; i++)
	{
		m_hasObstacle.push_back(false);
		m_hasLily.push_back(false);
	}

	PlaceLilys();

}

void WaterLane::Update(const SceneContext& /*sceneContext*/)
{

}

void WaterLane::OnSceneDetach(GameScene* pScene)
{
	//cleanUp made gameobjects
	for (int i{}; i < m_pLilys.size(); i++)
	{
		pScene->RemoveChild(m_pLilys.at(i), true);
	}
}

void WaterLane::PlaceLilys()
{
	for (int i{}; i < m_Width; i++)
	{
		if (i == 0 || i == m_Width - 1)
		{
			m_hasLily.at(i) = true;
		}else if(i == 12 || i == 13)
		{
			m_hasLily.at(i) = true;
		}
		else
		{
			int randNumb = rand() % 10;

			if (randNumb == 0)
			{
				m_hasLily.at(i) = true;
			}

		}

		if (m_hasLily.at(i) == true)
		{
			GameObject* lily = GetScene()->AddChild(new Lily(i, m_Count));

			m_pLilys.push_back(lily);
		}

	}
}
