#include "stdafx.h"
#include "SoftwareSkinningScene_1.h"
#include <Materials/ColorMaterial.h>


void SoftwareSkinningScene_1::Initialize()
{
	m_SceneContext.settings.enableOnGUI = true;

	ColorMaterial* pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();

	GameObject* pRoot = new GameObject{};
	m_pBone0 = new BoneObject(pMaterial, 15);
	pRoot->AddChild(m_pBone0);
	m_pBone1 = new BoneObject(pMaterial, 15);
	m_pBone0->AddBone(m_pBone1);

	AddChild(pRoot);
}

void SoftwareSkinningScene_1::Update()
{
	if(m_AutoRotate)
	{
	

		if(m_RotationSign == 1)
		{
			m_BoneRotation += 45 * GetSceneContext().pGameTime->GetElapsed();
			if(m_BoneRotation > 45)
			{
				m_RotationSign *= -1;
			}

		} else
		{
			m_BoneRotation -= 45 * GetSceneContext().pGameTime->GetElapsed();
			if (m_BoneRotation < -45)
			{
				m_RotationSign *= -1;
			}
		}

		m_pBone0->GetTransform()->Rotate(0, 0, m_BoneRotation);
		m_pBone1->GetTransform()->Rotate(0, 0, m_BoneRotation * 2);
	} else
	{

		m_pBone0->GetTransform()->Rotate(0, 0, m_BoneRot1);
		m_pBone1->GetTransform()->Rotate(0, 0, m_BoneRot2);

	}
}

void SoftwareSkinningScene_1::OnGUI()
{
	ImGui::DragFloat("Rotation bone 1", &m_BoneRot1, 1.f, -100.f, 100.f, "%.3f", 1.f);
	ImGui::DragFloat("Rotation bone 2", &m_BoneRot2, 1.f, -100.f, 100.f, "%.3f", 1.f);

	ImGui::Checkbox("Auto Rotate", &m_AutoRotate);
}
