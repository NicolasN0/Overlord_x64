#include "stdafx.h"
#include "Tree.h"


Tree::Tree(int posX, int posZ)
{
	m_PosX = posX;
	m_PosZ = posZ;
}

void Tree::Initialize(const SceneContext& /*sceneContext*/)
{
	
	m_pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	m_pMaterial->SetDiffuseTexture(L"Textures/Exam/tree.png");
	//m_pMaterial->SetDiffuseTexture(L"Textures/Exam/TreeBoxDiff.png");
	AddComponent(new ModelComponent(L"Meshes/Tree.ovm", false));
	//AddComponent(new ModelComponent(L"Meshes/Tree2.ovm", false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	GetTransform()->Translate(float(m_PosX), 0, float(m_PosZ));
}

void Tree::Update(const SceneContext&)
{
}
