#include "stdafx.h"
#include "Train.h"

Train::Train(int posX, int posZ)
{
	m_Width = posX;
	m_PosZ = posZ;
	m_CurX = 0;
}

void Train::Initialize(const SceneContext& /*sceneContext*/)
{
	//Set Tag
	SetTag(L"Enemy");

	//Material and Model
	m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(XMFLOAT4{ 1,0,1,1 });

	AddComponent(new ModelComponent(L"Meshes/Lane.ovm", false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	//Collider
	auto material = PxGetPhysics().createMaterial(.5f, .5f, .1f);
	AddComponent(new RigidBodyComponent(false));
	GetComponent<RigidBodyComponent>()->AddCollider(PxBoxGeometry{ 20.f,1.f,1.f }, *material);
	GetComponent<RigidBodyComponent>()->SetKinematic(true);
	/*auto colliderInfo = GetComponent<RigidBodyComponent>()->GetCollider(0);
	colliderInfo.SetTrigger(true);*/


	GetTransform()->Translate(0, 0, float(m_PosZ));
}

void Train::Update(const SceneContext& sceneContext)
{
	m_CurX += m_CarSpeed * sceneContext.pGameTime->GetElapsed();
	GetTransform()->Translate(m_CurX, 0, float(m_PosZ));
	if (m_CurX > m_Width * 2)
	{
		//m_CurX = 0;
		m_CurX = float(-m_Width) ;
	}
}
