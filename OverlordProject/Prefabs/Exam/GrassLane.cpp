#include "stdafx.h"
#include "GrassLane.h"
#include "Prefabs/Exam/Tree.h"

GrassLane::GrassLane(int count,int width)
{
	m_Count = count;
	m_Width = width;
}

void GrassLane::Initialize(const SceneContext& /*sceneContext*/)
{
	m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(XMFLOAT4{ 0,1,0,1 });

	AddComponent(new ModelComponent(L"Meshes/Lane.ovm", false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	GetTransform()->Translate(0, -2, float(1 * m_Count));

	//initalizeObstacles
	for(int i{};i < m_Width;i++)
	{
		m_hasObstacle.push_back(false);
	}

	PlaceObstacles();
}

void GrassLane::Update(const SceneContext&)
{
	
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
			int randNumb = rand() % 10;

			if(randNumb == 0)
			{
				m_hasObstacle.at(i) = true;
			}

		}

		if(m_hasObstacle.at(i) == true)
		{
			GameObject* tree = GetScene()->AddChild(new Tree(i,m_Count));

			m_pObstacles.push_back(tree);
		}

	}
}
