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

	m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(XMFLOAT4{ 1,0,1,1 });

	AddComponent(new ModelComponent(L"Meshes/Lane.ovm", false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);


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
