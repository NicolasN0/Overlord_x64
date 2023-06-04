#include "stdafx.h"
#include "Person.h"



Person::Person(int posX, int posZ)
{
	
	m_PosZ = posZ;
	m_PosX = posX;

}

void Person::Initialize(const SceneContext& /*sceneContext*/)
{
	
	m_pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Skinned>();
	m_pMaterial->SetDiffuseTexture(L"Textures/Exam/The_new_character.png");

	auto pModel = AddComponent(new ModelComponent(L"Meshes/person.ovm"));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	auto pAnimator = pModel->GetAnimator();
	pAnimator->SetAnimation(0);
	pAnimator->SetAnimationSpeed(2.f);
	pAnimator->Play();

	GetTransform()->Translate(float(m_PosX), -0.5f, float(m_PosZ));

	
	GetTransform()->Scale(0.3f);
}

void Person::Update(const SceneContext& /*sceneContext*/)
{


	

}

