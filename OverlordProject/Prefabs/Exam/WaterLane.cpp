#include "stdafx.h"
#include "WaterLane.h"


WaterLane::WaterLane(int count, int width)
{
	m_Count = count;
	m_Width = width;


}

std::vector<bool> WaterLane::GetObstacles()
{
	return m_hasObstacle;
}

void WaterLane::Initialize(const SceneContext& /*sceneContext*/)
{

	//standard lane setup
	m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(XMFLOAT4{ 0,0,1,1 });

	AddComponent(new ModelComponent(L"Meshes/Lane.ovm", false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	GetTransform()->Translate(float(m_Width / 2), -2, float(1 * m_Count));

	

	//initalizeObstacles
	for (int i{}; i < m_Width; i++)
	{
		m_hasObstacle.push_back(false);
	}

}

void WaterLane::Update(const SceneContext& /*sceneContext*/)
{

}