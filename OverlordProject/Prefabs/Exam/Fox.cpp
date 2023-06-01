#include "stdafx.h"
#include "Fox.h"


Fox::Fox(int width, int posZ)
{
	m_Width = width;
	m_PosZ = posZ;
	m_CurX = float(width)/2;
}

void Fox::Initialize(const SceneContext& /*sceneContext*/)
{
	m_Speed = rand() % 3 + 1;

	

	m_pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Skinned>();
	m_pMaterial->SetDiffuseTexture(L"Textures/Exam/car.png"); 

	auto pModel = AddComponent(new ModelComponent(L"Meshes/Fox.ovm"));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	auto pAnimator = pModel->GetAnimator();
	pAnimator->SetAnimation(0);
	pAnimator->SetAnimationSpeed(2.f);
	pAnimator->Play();

	GetTransform()->Translate(m_CurX, 0, float(m_PosZ));
	//90 for lloking left
	GetTransform()->Rotate(0, -90, 0);
	GetTransform()->Scale(0.01f);
}

void Fox::Update(const SceneContext& sceneContext)
{

		
		m_Counter += sceneContext.pGameTime->GetElapsed();
		if(m_Counter > m_DelayTimer)
		{
			m_CanMove = true;
		}

		if(m_CanMove)
		{

			//going right code
			m_CurX += m_Speed * sceneContext.pGameTime->GetElapsed();
			GetTransform()->Translate(m_CurX, 0, float(m_PosZ));
			if (m_CurX > m_Width)
			{
				m_CurX = 0;
			}
		}
	
}

