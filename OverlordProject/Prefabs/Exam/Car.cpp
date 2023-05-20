#include "stdafx.h"
#include "Car.h"

Car::Car(int width, int posZ)
{
	m_Width = width;
	m_PosZ = posZ;
	m_CurX = 0;
}

void Car::Initialize(const SceneContext& /*sceneContext*/)
{
	m_CarSpeed = rand() % 3 + 1;

	SetTag(L"Enemy");
	/*m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(XMFLOAT4{ 1,0,1,1 });*/

	m_pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	m_pMaterial->SetDiffuseTexture(L"Textures/Exam/car.png");

	AddComponent(new ModelComponent(L"Meshes/Car.ovm", false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	//Collider
	auto material = PxGetPhysics().createMaterial(.5f, .5f, .1f);
	AddComponent(new RigidBodyComponent(false));
	GetComponent<RigidBodyComponent>()->AddCollider(PxBoxGeometry{ 1.0f,1.0f,0.5f }, *material);
	GetComponent<RigidBodyComponent>()->SetKinematic(true);

	GetTransform()->Translate(0, 0, float(m_PosZ));

	GetTransform()->Rotate(0, 90, 0);
}

void Car::Update(const SceneContext& sceneContext)
{
	m_CurX += m_CarSpeed * sceneContext.pGameTime->GetElapsed();
	GetTransform()->Translate(m_CurX, 0, float(m_PosZ));
	if(m_CurX > m_Width)
	{
		m_CurX = 0;
	}
}
