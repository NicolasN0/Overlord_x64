#include "stdafx.h"
#include "TreeLane.h"
#include "Prefabs/Exam/Tree.h"

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
	m_pMaterial->SetColor(XMFLOAT4{ 0,1,0,1 });

	AddComponent(new ModelComponent(L"Meshes/Lane.ovm", false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	//GetTransform()->Translate(0, -2, float(1 * m_Count));
	//GetTransform()->Translate(float(m_Width/2), -2, float(1 * m_Count));
	GetTransform()->Translate(float(m_Width / 2), -1, float(1 * m_Count));

	//initalizeObstacles
	for (int i{}; i < m_Width; i++)
	{
		m_hasObstacle.push_back(false);
	}

	PlaceObstacles();
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
