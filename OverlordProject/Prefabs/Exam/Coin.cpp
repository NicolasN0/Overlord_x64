#include "stdafx.h"
#include "Coin.h"

Coin::Coin(int posX, int posZ)
{
	m_PosX = posX;
	m_PosZ = posZ;
}

void Coin::PickedUp(bool picked)
{
	m_PickedUp = picked;
}

void Coin::Initialize(const SceneContext& /*sceneContext*/)
{
	SetTag(L"Coin");


	m_pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	m_pMaterial->SetDiffuseTexture(L"Textures/Exam/Coin.png");

	AddComponent(new ModelComponent(L"Meshes/Coin.ovm", false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	GetTransform()->Translate(float(m_PosX), 0, float(m_PosZ));
	//Collider
	auto material = PxGetPhysics().createMaterial(.5f, .5f, .1f);
	AddComponent(new RigidBodyComponent(false));
	GetComponent<RigidBodyComponent>()->AddCollider(PxBoxGeometry{ 0.3f,0.3f,0.3f }, *material);
	GetComponent<RigidBodyComponent>()->SetKinematic(true);


	
}

void Coin::Update(const SceneContext& /*sceneContext*/)
{
	if(m_PickedUp)
	{
		GetScene()->RemoveChild(this, true);
	}
}
