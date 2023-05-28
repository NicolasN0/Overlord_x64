#include "stdafx.h"
#include "MainMenuScene.h"
#include <Materials/ColorMaterial.h>
#include "CrossyRoadScene.h"

void MainMenuScene::Initialize()
{
	m_SceneContext.settings.enableOnGUI = true;
	m_SceneContext.settings.drawGrid = false;

	m_SceneContext.settings.clearColor = XMFLOAT4(40.f/255.f, 160.f/255.f, 125.f/255.f, 1);
	
	//name
	SetName("CrossyMenu");

	m_pFixedCamera = new GameObject();
	AddChild(m_pFixedCamera);
	auto cameraComp = m_pFixedCamera->AddComponent(new CameraComponent());
	cameraComp->SetActive(true);
	cameraComp->UseOrthographicProjection();
	cameraComp->SetOrthoSize(10);


	const auto pMaterial = PxGetPhysics().createMaterial(.5f, .5f, .5f);
	//test
	// 
	/*m_pTestHeight = new GameObject();
	const auto pRigidBodyT = m_pTestHeight->AddComponent(new RigidBodyComponent(true));
	pRigidBodyT->AddCollider(PxBoxGeometry{ 1.8f,0.6f,0.1f }, *pMaterial);
	m_pTestHeight->GetTransform()->Translate(0.3f, 1.35f, 2.f);
	m_pTestHeight->GetTransform()->Scale(1.f);
	AddChild(m_pTestHeight);*/


	////mainBack
	m_pSpriteButton = new GameObject();
	m_pSpriteButton->AddComponent(new SpriteComponent(L"Textures/Exam/MainMenu/MainMenuBack.png", { 0.5f,0.5f }));
	AddChild(m_pSpriteButton);
	m_pSpriteButton->GetTransform()->Translate(m_SceneContext.windowWidth / 2.f, m_SceneContext.windowHeight / 2.f, .9f);
	m_pSpriteButton->GetTransform()->Scale(1.f);
	 
	
	//play sprite
	m_pSpriteButton = new GameObject();
	m_pSpriteButton->SetTag(L"Play");
	m_pSpriteButton->AddComponent(new SpriteComponent(L"Textures/Exam/MainMenu/Play.png", { 0.5f,0.5f }));
	m_pSpriteButton->GetTransform()->Translate(m_SceneContext.windowWidth / 2.f, m_SceneContext.windowHeight / 2.f, .8f);
	AddChild(m_pSpriteButton);
	//play collider
	m_pSpriteButton = new GameObject();
	m_pSpriteButton->SetTag(L"Play");
	const auto pRigidBody = m_pSpriteButton->AddComponent(new RigidBodyComponent(true));
	pRigidBody->AddCollider(PxBoxGeometry{ 1.7f,0.45f,0.1f }, *pMaterial);
	m_pSpriteButton->GetTransform()->Translate(0.3f, 1.4f, 2.f);
	m_pSpriteButton->GetTransform()->Scale(1.f);
	AddChild(m_pSpriteButton);


	////Settings sprite
	m_pSpriteButton = new GameObject();
	m_pSpriteButton->AddComponent(new SpriteComponent(L"Textures/Exam/MainMenu/Settings.png", { 0.5f,0.5f }));
	m_pSpriteButton->GetTransform()->Translate(m_SceneContext.windowWidth / 2.f, m_SceneContext.windowHeight / 2.f, .7f);
	m_pSpriteButton->GetTransform()->Scale(1.f);
	AddChild(m_pSpriteButton);
	//Settings collider
	m_pSpriteButton = new GameObject();
	m_pSpriteButton->SetTag(L"Settings");
	const auto pRigidBodyS = m_pSpriteButton->AddComponent(new RigidBodyComponent(true));
	pRigidBodyS->AddCollider(PxBoxGeometry{ 1.7f,0.45f,0.1f }, *pMaterial);
	m_pSpriteButton->GetTransform()->Translate(0.3f, -1.f, 2.f);
	m_pSpriteButton->GetTransform()->Scale(1.f);
	AddChild(m_pSpriteButton);


	////Exit sprite
	m_pSpriteButton = new GameObject();
	m_pSpriteButton->AddComponent(new SpriteComponent(L"Textures/Exam/MainMenu/Exit.png", { 0.5f,0.5f }));
	m_pSpriteButton->GetTransform()->Translate(m_SceneContext.windowWidth / 2.f, m_SceneContext.windowHeight / 2.f, .6f);
	m_pSpriteButton->GetTransform()->Scale(1.f);
	AddChild(m_pSpriteButton);
	//exit collider
	m_pSpriteButton = new GameObject();
	m_pSpriteButton->SetTag(L"Exit");
	const auto pRigidBodyE = m_pSpriteButton->AddComponent(new RigidBodyComponent(true));
	pRigidBodyE->AddCollider(PxBoxGeometry{ 1.7f,0.45f,0.1f }, * pMaterial);
	m_pSpriteButton->GetTransform()->Translate(0.3f, 0.2f, 2.f);
	m_pSpriteButton->GetTransform()->Scale(1.f);
	AddChild(m_pSpriteButton);

	

	
}

void MainMenuScene::Update()
{

	//m_pTestHeight->GetTransform()->Translate(0.3f,m_Height, 2.f);
	
	if (InputManager::IsMouseButton(InputState::pressed, VK_LBUTTON))
	{
		if (const auto pPickedObject = m_SceneContext.pCamera->Pick())
		{
			if(pPickedObject->GetTag() == L"Play")
			{
				std::cout << "Play";

			

				auto manager = SceneManager::Get();
				auto crossyScene = manager->GetSceneByName("CrossyRoad");
				if(crossyScene != NULL)
				{
					manager->RemoveGameScene(manager->GetSceneByName("CrossyRoad"), true);
				}
				manager->AddGameScene(new CrossyRoadScene());
				/*manager->NextScene();*/
				manager->SetSceneByName("CrossyRoad");
			}

			if (pPickedObject->GetTag() == L"Exit")
			{
				std::cout << "Exit";
				
			}

			if (pPickedObject->GetTag() == L"Settings")
			{
				//std::cout << "Settings";
				auto manager = SceneManager::Get();
				manager->SetSceneByName("ControlsScene");
			}
		}
	}
}

void MainMenuScene::OnGUI()
{
	
	ImGui::DragFloat("Rotation bone 1", &m_Height, 1.f, -10.f, 10.f, "%.3f", 1.f);
}