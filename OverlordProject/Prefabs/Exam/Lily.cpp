#include "stdafx.h"
#include "Lily.h"

Lily::Lily(int posX, int posZ)
{
	m_PosX = posX;
	m_PosZ = posZ;
}

void Lily::Initialize(const SceneContext& /*sceneContext*/)
{
	m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(XMFLOAT4{ 0,1,0,1 });

	AddComponent(new ModelComponent(L"Meshes/Tree.ovm", false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	
	GetTransform()->Translate(float(m_PosX), 0, float(m_PosZ));
}

void Lily::Update(const SceneContext&)
{
}
