#include "stdafx.h"
#include "TrainLane.h"
#include "Prefabs/Exam/Train.h"

TrainLane::TrainLane(int count, int width)
{
	m_Count = count;
	m_Width = width;
}

std::vector<bool> TrainLane::GetObstacles()
{
	return m_hasObstacle;
}

void TrainLane::Initialize(const SceneContext& /*sceneContext*/)
{
	//tag
	SetTag(L"TrainLane");

	//mesh
	m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(XMFLOAT4{ 0.5,0.5,0.5,1 });

	AddComponent(new ModelComponent(L"Meshes/Lane.ovm", false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	GetTransform()->Translate(float(m_Width / 2), -2, float(1 * m_Count));

	GetScene()->AddChild(new Train(m_Width, m_Count));

	//initalizeObstacles
	for (int i{}; i < m_Width; i++)
	{
		m_hasObstacle.push_back(false);
	}
}

void TrainLane::Update(const SceneContext& /*sceneContext*/)
{
}
