#include "stdafx.h"
#include "GrassLane.h"
#include "Prefabs/Exam/Tree.h"

GrassLane::GrassLane(int count,int width)
{
	m_Count = count;
	m_Width = width;

	
}

std::vector<bool> GrassLane::GetObstacles()
{
	return m_hasObstacle;
}

void GrassLane::Initialize(const SceneContext& /*sceneContext*/)
{
	//tag
	SetTag(L"GrassLane");

	//mesh
	m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(m_Color);

	AddComponent(new ModelComponent(L"Meshes/Lane.ovm", false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	//GetTransform()->Translate(0, -2, float(1 * m_Count));
	//GetTransform()->Translate(float(m_Width/2), -2, float(1 * m_Count));
	GetTransform()->Translate(float(m_Width / 2), -1, float(1 * m_Count));
	GetTransform()->Scale(2, 1, 1);
	//initalizeObstacles
	for(int i{};i < m_Width;i++)
	{
		m_hasObstacle.push_back(false);
	}

	PlaceObstacles();
}

void GrassLane::Update(const SceneContext& /*sceneContext*/)
{

}

void GrassLane::OnSceneDetach(GameScene* pScene)
{
	//cleanUp made gameobjects
	for (int i{}; i < m_pObstacles.size(); i++)
	{
		pScene->RemoveChild(m_pObstacles.at(i), true);
	}
}

void GrassLane::PlaceObstacles()
{
	for (int i{}; i < m_Width;i++)
	{
		if(i == 0 || i == m_Width -1)
		{
			m_hasObstacle.at(i) = true;
		} else
		{
			if(m_Count != 0 && i != m_Width/2)
			{
				int randNumb = rand() % 10;

				if(randNumb == 0)
				{
					m_hasObstacle.at(i) = true;
				}

			}

		}

		if(m_hasObstacle.at(i) == true)
		{
			GameObject* tree = GetScene()->AddChild(new Tree(i,m_Count));

			m_pObstacles.push_back(tree);
		}

	}
}
