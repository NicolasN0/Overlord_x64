#include "stdafx.h"
#include "Tree.h"


Tree::Tree(int posX, int posZ)
{
	m_PosX = posX;
	m_PosZ = posZ;
}

void Tree::Initialize(const SceneContext& /*sceneContext*/)
{
	/*m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(XMFLOAT4{ 1,0,0,1 });*/
	m_pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	//m_pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	m_pMaterial->SetDiffuseTexture(L"Textures/Exam/tree.png");

	AddComponent(new ModelComponent(L"Meshes/Tree.ovm", false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	//GetTransform()->Translate(-12.5f, 0, 0);
	GetTransform()->Translate(float(m_PosX)/* -12.f*/, 0, float(m_PosZ));
}

void Tree::Update(const SceneContext&)
{
}
