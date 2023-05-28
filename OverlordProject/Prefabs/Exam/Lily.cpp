#include "stdafx.h"
#include "Lily.h"

Lily::Lily(int posX, int posZ)
{
	m_PosX = posX;
	m_PosZ = posZ;
}

void Lily::Initialize(const SceneContext& /*sceneContext*/)
{
	SetTag(L"Lily");
	/*m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(XMFLOAT4{ 0,1,0,1 });*/
	m_pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	m_pMaterial->SetDiffuseTexture(L"Textures/Exam/lilypad.png");


	AddComponent(new ModelComponent(L"Meshes/LilyPad.ovm", false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	
	GetTransform()->Translate(float(m_PosX), -0.5, float(m_PosZ));


	//Collider
	auto material = PxGetPhysics().createMaterial(.5f, .5f, .1f);
	AddComponent(new RigidBodyComponent(false));
	GetComponent<RigidBodyComponent>()->AddCollider(PxBoxGeometry{ 0.3f,0.3f,0.3f }, *material);
	GetComponent<RigidBodyComponent>()->SetKinematic(true);
}

void Lily::Update(const SceneContext&)
{
}
