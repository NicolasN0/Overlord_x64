#include "stdafx.h"
#include "RoadLane.h"
#include "Prefabs/Exam/Car.h"

RoadLane::RoadLane(int count, int width)
{
	m_Count = count;
	m_Width = width;


}

std::vector<bool> RoadLane::GetObstacles()
{
	return m_hasObstacle;
}

void RoadLane::Initialize(const SceneContext& /*sceneContext*/)
{
	//tag
	SetTag(L"RoadLane");

	//mesh
	m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(XMFLOAT4{ 0.5,0.5,0.5,1 });

	AddComponent(new ModelComponent(L"Meshes/Lane.ovm", false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	GetTransform()->Translate(float(m_Width / 2), -2, float(1 * m_Count));

	/*GameObject* car =*/ GetScene()->AddChild(new Car(m_Width, m_Count));

	//initalizeObstacles
	for (int i{}; i < m_Width; i++)
	{
		m_hasObstacle.push_back(false);
	}

}

void RoadLane::Update(const SceneContext& /*sceneContext*/)
{

}

