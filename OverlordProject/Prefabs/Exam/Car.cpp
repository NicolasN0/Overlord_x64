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

	m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(XMFLOAT4{ 1,0,1,1 });

	AddComponent(new ModelComponent(L"Meshes/Sphere.ovm", false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	
	GetTransform()->Translate(0, 0, float(m_PosZ));
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
