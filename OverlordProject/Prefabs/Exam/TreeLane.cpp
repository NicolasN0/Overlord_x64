#include "stdafx.h"
#include "TreeLane.h"
#include "Prefabs/Exam/Tree.h"
#include "Prefabs/Exam/Fox.h"
TreeLane::TreeLane(int count, int width)
{
	m_Count = count;
	m_Width = width;


}

std::vector<bool> TreeLane::GetObstacles()
{
	return m_hasObstacle;
}

void TreeLane::Initialize(const SceneContext& /*sceneContext*/)
{
	//tag
	SetTag(L"TreeLane");

	//mesh
	m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(m_Color);

	AddComponent(new ModelComponent(L"Meshes/Lane.ovm",false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);


	GetTransform()->Translate(float(m_Width / 2), -1, float(1 * m_Count));
	GetTransform()->Scale(2, 1, 1);
	//initalizeObstacles
	for (int i{}; i < m_Width; i++)
	{
		m_hasObstacle.push_back(false);
	}

	//comment for no fox
	//if(m_Count == -2)
	//{
	//	m_hasFox = true;
	//}

	if(!m_hasFox)
	{

		PlaceObstacles();
	} else
	{
		m_pFox = GetScene()->AddChild(new Fox(m_Width, m_Count));
	}
}


void TreeLane::OnSceneDetach(GameScene* pScene)
{
	//cleanUp made gameobjects
	for (int i{}; i < m_pObstacles.size(); i++)
	{
		pScene->RemoveChild(m_pObstacles.at(i), true);
	}

	if(m_hasFox)
	{
		pScene->RemoveChild(m_pFox, true);
	}
}

void TreeLane::Update(const SceneContext& /*sceneContext*/)
{

}

void TreeLane::PlaceObstacles()
{
	for (int i{}; i < m_Width; i++)
	{

		//all trees
		m_hasObstacle.at(i) = true;

		if (m_hasObstacle.at(i) == true)
		{
			GameObject* tree = GetScene()->AddChild(new Tree(i, m_Count));

			m_pObstacles.push_back(tree);
		}

	}
}
