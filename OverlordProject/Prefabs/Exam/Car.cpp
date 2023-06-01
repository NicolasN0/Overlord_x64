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
	//m_pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	SetRandomColor();
	//m_pMaterial->SetDiffuseTexture(L"Textures/Exam/car.png");

	AddComponent(new ModelComponent(L"Meshes/Car.ovm"));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	//Collider
	auto material = PxGetPhysics().createMaterial(.5f, .5f, .1f);
	AddComponent(new RigidBodyComponent(false));
	GetComponent<RigidBodyComponent>()->AddCollider(PxBoxGeometry{ 1.0f,1.0f,0.5f }, *material);
	GetComponent<RigidBodyComponent>()->SetKinematic(true);


	SetMovingDirection();

	if (m_isMovingLeft) 
	{
		GetTransform()->Scale(-1, 1, 1);
		GetTransform()->Translate(float(m_Width), 0, float(m_PosZ));

	} else
	{

		GetTransform()->Translate(0, 0, float(m_PosZ));
	}

	GetTransform()->Rotate(0, 90, 0);
}

void Car::Update(const SceneContext& sceneContext)
{
	if(m_isMovingLeft)
	{
		//going left code
		m_CurX -= m_CarSpeed * sceneContext.pGameTime->GetElapsed();
		GetTransform()->Translate(m_CurX, 0, float(m_PosZ));
		if (m_CurX < 0)
		{
			m_CurX = float(m_Width);
		}

	} else
	{
		//going right code
		m_CurX += m_CarSpeed * sceneContext.pGameTime->GetElapsed();
		GetTransform()->Translate(m_CurX, 0, float(m_PosZ));
		if(m_CurX > m_Width)
		{
			m_CurX = 0;
		}
	}
}

void Car::SetRandomColor()
{
	int randomColor = rand() % 3;
	switch(randomColor)
	{
	case 0:
		m_pMaterial->SetDiffuseTexture(L"Textures/Exam/car.png");

		break;
	case 1:
		m_pMaterial->SetDiffuseTexture(L"Textures/Exam/car2.png");

		break;
	case 2:
		m_pMaterial->SetDiffuseTexture(L"Textures/Exam/car3.png");

		break;
	default:
		m_pMaterial->SetDiffuseTexture(L"Textures/Exam/car.png");

	}
}

void Car::SetMovingDirection()
{
	int randDir = rand() % 2;
	if(randDir == 0)
	{
		m_isMovingLeft = false;
	} else
	{
		m_isMovingLeft = true;
	}

}
