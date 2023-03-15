#include "stdafx.h"
#include "W3_PongScene.h"


#include "Prefabs/CubePrefab.h"
#include "Prefabs/SpherePrefab.h"

#define VK_W 0x57
#define VK_S 0x53
#define VK_I 0x49
#define VK_K 0x4B

W3_PongScene::W3_PongScene() :
	GameScene(L"W3_PongScene") {}

void W3_PongScene::Initialize()
{
	//m_SceneContext.settings.showInfoOverlay = true;
	//m_SceneContext.settings.drawPhysXDebug = true;
	//m_SceneContext.settings.drawGrid = true;
	m_SceneContext.settings.enableOnGUI = true;

	m_SceneContext.pCamera->UseOrthographicProjection();
	


	auto material = PxGetPhysics().createMaterial(.5f, .5f, .1f);
	//leftCube
	m_pCubeLeft = new CubePrefab(XMFLOAT3{ 2.f,4.f,2.f });
	AddChild(m_pCubeLeft);
	
//	m_pCubeLeft->AddComponent(new TransformComponent());
	m_pCubeLeft->GetTransform()->Translate(-10, 10, 0);
	m_pCubeLeft->AddComponent(new RigidBodyComponent(false));
	m_pCubeLeft->GetComponent<RigidBodyComponent>()->AddCollider(PxBoxGeometry{ 1.f,2.f,1.f }, *material);
	m_pCubeLeft->GetComponent<RigidBodyComponent>()->AddCollider(PxBoxGeometry{ 1.f,4.f,1.f }, *material);
	m_pCubeLeft->GetComponent<RigidBodyComponent>()->SetKinematic(true);

	auto colliderInfoL = m_pCubeLeft->GetComponent<RigidBodyComponent>()->GetCollider(0);
	colliderInfoL.SetTrigger(true);

	//rightCube
	m_pCubeRight = new CubePrefab(XMFLOAT3{ 2.f,4.f,2.f });
	AddChild(m_pCubeRight);

	//m_pCubeRight->AddComponent(new TransformComponent());
	m_pCubeRight->GetTransform()->Translate(10, 10, 0);
	m_pCubeRight->AddComponent(new RigidBodyComponent(false));
	m_pCubeRight->GetComponent<RigidBodyComponent>()->AddCollider(PxBoxGeometry{ 1.f,2.f,1.f }, *material);
	m_pCubeRight->GetComponent<RigidBodyComponent>()->AddCollider(PxBoxGeometry{ 1.f,2.f,1.f }, *material);
	m_pCubeRight->GetComponent<RigidBodyComponent>()->SetKinematic(true);

	auto colliderInfo = m_pCubeRight->GetComponent<RigidBodyComponent>()->GetCollider(0);
	colliderInfo.SetTrigger(true);
	//Sphere
	m_pSphere = new SpherePrefab();
	AddChild(m_pSphere);

	//m_pSphere->AddComponent(new TransformComponent());
	m_pSphere->GetTransform()->Translate(0, 10, 0);
	m_pSphere->AddComponent(new RigidBodyComponent(false));
	
	m_pSphere->GetComponent<RigidBodyComponent>()->AddCollider(PxSphereGeometry{ 0.5f }, *material);
	m_pSphere->GetComponent<RigidBodyComponent>()->SetKinematic(false);




	//input
	m_SceneContext.pInput->AddInputAction(InputAction(MoveUpL, InputState::down,VK_W , -1, XINPUT_GAMEPAD_DPAD_LEFT));
	m_SceneContext.pInput->AddInputAction(InputAction(MoveDownL, InputState::down, VK_S, -1, XINPUT_GAMEPAD_DPAD_RIGHT));
	m_SceneContext.pInput->AddInputAction(InputAction(MoveUpR, InputState::down, VK_UP, -1, XINPUT_GAMEPAD_DPAD_UP));
	m_SceneContext.pInput->AddInputAction(InputAction(MoveDownR, InputState::down, VK_DOWN, -1, XINPUT_GAMEPAD_DPAD_DOWN));
	m_SceneContext.pInput->AddInputAction(InputAction(Reset, InputState::down, VK_SPACE, -1, XINPUT_GAMEPAD_DPAD_DOWN));

	m_pCubeLeft->SetOnTriggerCallBack([=](GameObject* , GameObject* , PxTriggerAction action)
		{
			if(action == PxTriggerAction::ENTER)
			{
				m_isGoingLeft = !m_isGoingLeft;
			}
		});

	m_pCubeRight->SetOnTriggerCallBack([=](GameObject*, GameObject*, PxTriggerAction action)
		{
			if (action == PxTriggerAction::ENTER)
			{
				m_isGoingLeft = !m_isGoingLeft;
			}
		});
}

void W3_PongScene::Update()
{
	//Optional
	if (m_SceneContext.pInput->IsActionTriggered(MoveUpL))
	{
		auto pos = m_pCubeLeft->GetTransform()->GetPosition();
		m_pCubeLeft->GetTransform()->Translate(pos.x, pos.y + (m_Speed * m_SceneContext.pGameTime->GetElapsed()), pos.z);
	}

	if (m_SceneContext.pInput->IsActionTriggered(MoveDownL))
	{
		auto pos = m_pCubeLeft->GetTransform()->GetPosition();
		m_pCubeLeft->GetTransform()->Translate(pos.x, pos.y - (m_Speed * m_SceneContext.pGameTime->GetElapsed()), pos.z);
	}

	if (m_SceneContext.pInput->IsActionTriggered(MoveUpR))
	{
		auto pos = m_pCubeRight->GetTransform()->GetPosition();
		m_pCubeRight->GetTransform()->Translate(pos.x, pos.y + (m_Speed * m_SceneContext.pGameTime->GetElapsed()), pos.z);
	}

	if (m_SceneContext.pInput->IsActionTriggered(MoveDownR))
	{
		auto pos = m_pCubeRight->GetTransform()->GetPosition();
		m_pCubeRight->GetTransform()->Translate(pos.x, pos.y - (m_Speed * m_SceneContext.pGameTime->GetElapsed()), pos.z);
	}

	if(!m_isGoingLeft)
	{

		m_pSphere->GetComponent<RigidBodyComponent>()->AddForce(XMFLOAT3{ -5.f,9.81f,0 });
	} else
	{
		m_pSphere->GetComponent<RigidBodyComponent>()->AddForce(XMFLOAT3{ 5.f,9.81f,0 });

	}

	

}

void W3_PongScene::Draw()
{
	//Optional
}

void W3_PongScene::OnGUI()
{
	ImGui::Text("This only activates if\n SceneSettings.enableOnGUI is True.\n\n");
	ImGui::Text("Use ImGui to add custom\n controllable scene parameters!");
	ImGui::ColorEdit3("Demo ClearColor", &m_SceneContext.settings.clearColor.x, ImGuiColorEditFlags_NoInputs);
}
