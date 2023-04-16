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
	
	m_pCubeLeft->GetTransform()->Translate(-10, 5, 0);
	m_pCubeLeft->AddComponent(new RigidBodyComponent(false));
	m_pCubeLeft->GetComponent<RigidBodyComponent>()->AddCollider(PxBoxGeometry{ 1.f,2.f,1.f }, *material);
	m_pCubeLeft->GetComponent<RigidBodyComponent>()->AddCollider(PxBoxGeometry{ 1.f,2.f,1.f }, *material);
	m_pCubeLeft->GetComponent<RigidBodyComponent>()->SetKinematic(true);

	auto colliderInfoL = m_pCubeLeft->GetComponent<RigidBodyComponent>()->GetCollider(0);
	colliderInfoL.SetTrigger(true);

	//rightCube
	m_pCubeRight = new CubePrefab(XMFLOAT3{ 2.f,4.f,2.f });
	AddChild(m_pCubeRight);

	//m_pCubeRight->AddComponent(new TransformComponent());
	m_pCubeRight->GetTransform()->Translate(10, 5, 0);
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
	m_pSphere->GetTransform()->Translate(0, 5, 0);
	m_pSphere->AddComponent(new RigidBodyComponent(false));
	
	m_pSphere->GetComponent<RigidBodyComponent>()->AddCollider(PxSphereGeometry{ 0.5f }, *material);
	//m_pSphere->GetComponent<RigidBodyComponent>()->SetKinematic(false);
	m_pSphere->GetComponent<RigidBodyComponent>()->SetKinematic(true);

	m_ballVelocity = XMFLOAT3{ 2.5,0.5,0.0 };

	//Out of Bounds cubes
	//leftBound
	auto pBoundLeft = new CubePrefab(XMFLOAT3{ 2.f,35.f,2.f });
	AddChild(pBoundLeft);

	pBoundLeft->GetTransform()->Translate(-22, 0, 0);
	pBoundLeft->AddComponent(new RigidBodyComponent(false));
	pBoundLeft->GetComponent<RigidBodyComponent>()->AddCollider(PxBoxGeometry{ 1.f,17.5f,1.f }, *material);
	pBoundLeft->GetComponent<RigidBodyComponent>()->SetKinematic(true);
	auto colliderInfoBL = pBoundLeft->GetComponent<RigidBodyComponent>()->GetCollider(0);
	colliderInfoBL.SetTrigger(true);

	//rightBound
	auto pBoundRight = new CubePrefab(XMFLOAT3{ 2.f,35.f,2.f });
	AddChild(pBoundRight);

	pBoundRight->GetTransform()->Translate(22, 0, 0);
	pBoundRight->AddComponent(new RigidBodyComponent(false));
	pBoundRight->GetComponent<RigidBodyComponent>()->AddCollider(PxBoxGeometry{ 1.f,17.5f,1.f }, *material);
	pBoundRight->GetComponent<RigidBodyComponent>()->SetKinematic(true);
	auto colliderInfoBR = pBoundRight->GetComponent<RigidBodyComponent>()->GetCollider(0);
	colliderInfoBR.SetTrigger(true);

	//bound top
	auto pBoundTop = new CubePrefab(XMFLOAT3{ 40.f,2.f,2.f });
	AddChild(pBoundTop);

	pBoundTop->GetTransform()->Translate(0, 18, 0);
	pBoundTop->AddComponent(new RigidBodyComponent(false));
	pBoundTop->GetComponent<RigidBodyComponent>()->AddCollider(PxBoxGeometry{ 20.f,1.f,1.f }, *material);
	pBoundTop->GetComponent<RigidBodyComponent>()->SetKinematic(true);
	auto colliderInfoBT = pBoundTop->GetComponent<RigidBodyComponent>()->GetCollider(0);
	colliderInfoBT.SetTrigger(true);

	//bound bottom
	auto pBoundBottom = new CubePrefab(XMFLOAT3{ 40,2.f,2.f });
	AddChild(pBoundBottom);

	pBoundBottom->GetTransform()->Translate(0, -10, 0);
	pBoundBottom->AddComponent(new RigidBodyComponent(false));
	pBoundBottom->GetComponent<RigidBodyComponent>()->AddCollider(PxBoxGeometry{ 20.f,1.f,1.f }, *material);
	pBoundBottom->GetComponent<RigidBodyComponent>()->SetKinematic(true);
	auto colliderInfoBB = pBoundBottom->GetComponent<RigidBodyComponent>()->GetCollider(0);
	colliderInfoBB.SetTrigger(true);
	
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
				//m_isGoingLeft = !m_isGoingLeft;
				if (m_isLeftGoingUp) 
				{
					if (m_ballVelocity.y > 0)
					{

						m_ballVelocity.y *= 1;
					}
					else
					{
						m_ballVelocity.y *= -1;
					}
					
					m_ballVelocity.x *= -1;
				} else				
					if (m_isLeftGoingDown)
				{
						if (m_ballVelocity.y > 0)
						{

							m_ballVelocity.y *= -1;
						}
						else
						{
							m_ballVelocity.y *= 1;
						}
					m_ballVelocity.x *= -1;
				} else
				{
					m_ballVelocity.x *= -1;
				}
			}
		});

	m_pCubeRight->SetOnTriggerCallBack([=](GameObject*, GameObject*, PxTriggerAction action)
		{
			if (action == PxTriggerAction::ENTER)
			{
				//m_isGoingLeft = !m_isGoingLeft;

				if (m_isRightGoingUp)
				{
					if(m_ballVelocity.y > 0)
					{

						m_ballVelocity.y *= 1;
					} else
					{
						m_ballVelocity.y *= -1;
					}

					m_ballVelocity.x *= -1;
				} else
				if (m_isRightGoingDown)
				{
					if (m_ballVelocity.y > 0)
					{

						m_ballVelocity.y *= -1;
					}
					else
					{
						m_ballVelocity.y *= 1;
					}
					m_ballVelocity.x *= -1;
				} else
				{
					m_ballVelocity.x *= -1;
				}
			}
		});

	pBoundLeft->SetOnTriggerCallBack([=](GameObject*, GameObject*, PxTriggerAction action)
		{
			if (action == PxTriggerAction::ENTER)
			{
				ResetLevel();
			}
		});

	pBoundRight->SetOnTriggerCallBack([=](GameObject*, GameObject*, PxTriggerAction action)
		{
			if (action == PxTriggerAction::ENTER)
			{
				ResetLevel();
			}
		});

	pBoundTop->SetOnTriggerCallBack([=](GameObject*, GameObject*, PxTriggerAction action)
		{
			if (action == PxTriggerAction::ENTER)
			{
				ResetLevel();
			}
		});
}

void W3_PongScene::Update()
{
	//ResetAll
	m_isLeftGoingUp = false;
	m_isLeftGoingDown = false;
	m_isRightGoingUp = false;
	m_isRightGoingDown = false;

	//Optional
	if (m_SceneContext.pInput->IsActionTriggered(MoveUpL))
	{
		auto pos = m_pCubeLeft->GetTransform()->GetPosition();
		m_pCubeLeft->GetTransform()->Translate(pos.x, pos.y + (m_Speed * m_SceneContext.pGameTime->GetElapsed()), pos.z);
		m_isLeftGoingUp = true;
	}

	if (m_SceneContext.pInput->IsActionTriggered(MoveDownL))
	{
		auto pos = m_pCubeLeft->GetTransform()->GetPosition();
		m_pCubeLeft->GetTransform()->Translate(pos.x, pos.y - (m_Speed * m_SceneContext.pGameTime->GetElapsed()), pos.z);
		m_isLeftGoingDown = true;
	}

	if (m_SceneContext.pInput->IsActionTriggered(MoveUpR))
	{
		auto pos = m_pCubeRight->GetTransform()->GetPosition();
		m_pCubeRight->GetTransform()->Translate(pos.x, pos.y + (m_Speed * m_SceneContext.pGameTime->GetElapsed()), pos.z);
		m_isRightGoingUp = true;
	}

	if (m_SceneContext.pInput->IsActionTriggered(MoveDownR))
	{
		auto pos = m_pCubeRight->GetTransform()->GetPosition();
		m_pCubeRight->GetTransform()->Translate(pos.x, pos.y - (m_Speed * m_SceneContext.pGameTime->GetElapsed()), pos.z);
		m_isRightGoingDown = true;
	}

	

	m_pSphere->GetTransform()->Translate(
		XMFLOAT3(m_pSphere->GetTransform()->GetPosition().x + m_ballVelocity.x * m_SpeedBall * m_SceneContext.pGameTime->GetElapsed(),
			m_pSphere->GetTransform()->GetPosition().y + m_ballVelocity.y * m_SpeedBall * m_SceneContext.pGameTime->GetElapsed(),
			m_pSphere->GetTransform()->GetPosition().z + m_ballVelocity.z * m_SpeedBall * m_SceneContext.pGameTime->GetElapsed()));
	
	

}

void W3_PongScene::ResetLevel()
{
	m_pCubeLeft->GetTransform()->Translate(-10, 5, 0);
	m_pCubeRight->GetTransform()->Translate(10, 5, 0);
	m_pSphere->GetTransform()->Translate(0, 5, 0);
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
