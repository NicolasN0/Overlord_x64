#include "stdafx.h"
#include "GrassLane.h"

GrassLane::GrassLane(int count)
{
	m_Count = count;
}

void GrassLane::Initialize(const SceneContext& /*sceneContext*/)
{
	m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(XMFLOAT4{ 0,1,0,1 });

	AddComponent(new ModelComponent(L"Meshes/Lane.ovm", false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	GetTransform()->Translate(0, -2, float(1 * m_Count));
}

void GrassLane::Update(const SceneContext&)
{
	
}
