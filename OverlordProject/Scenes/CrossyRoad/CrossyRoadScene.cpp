#include "stdafx.h"
#include "CrossyRoadScene.h"
#include "Prefabs/Exam/CrossyCharacter.h"
#include "Prefabs/Exam/GrassLane.h"
#include "Prefabs/Exam/LaneManager.h"

#include <Materials/Post/PostExam.h>

#include "RestarterScene.h"

#define VK_W 0x57
#define VK_S 0x53
#define VK_A 0x41
#define VK_D 0x44

void CrossyRoadScene::Initialize()
{
	m_SceneContext.settings.enableOnGUI = true;
	m_SceneContext.settings.drawGrid = false;

	
	//m_SceneContext.pLights->SetDirectionalLight({ -95.6139526f,66.1346436f,-41.1850471f }, { 0.740129888f, -0.597205281f, 0.309117377f });
	m_SceneContext.pLights->SetDirectionalLight({ 0,10,0 }, { 0.740129888f, -0.597205281f, 0.309117377f });

	//name
	SetName("CrossyRoad");

	const auto pDefaultMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.5f);
	GameSceneExt::CreatePhysXGroundPlane(*this, pDefaultMaterial);

	//manager
	m_pLaneManager = AddChild(new LaneManager());
	//player
	m_pPlayer = AddChild(new CrossyCharacter(m_pLaneManager));


	//Camera
	//const auto pCamera = AddChild(new PlayerCamera(m_pPlayer,XMFLOAT3{3,20,-3}));
	//const auto pCamera = AddChild(new PlayerCamera(m_pPlayer, m_CameraOffset));

	//m_pCameraComponent = pCamera->GetComponent<CameraComponent>();
	//m_pCameraComponent->SetActive(true); //Uncomment to make this camera the active camera

	m_pPlayerCamera = AddChild(new PlayerCamera(m_pPlayer, m_CameraOffset));

	m_pCameraComponent = m_pPlayerCamera->GetComponent<CameraComponent>();
	m_pCameraComponent->SetActive(true); //Uncomment to make this camera the active camera
	
	
	//Inputs
	m_SceneContext.pInput->AddInputAction(InputAction(MoveUp, InputState::down, VK_W, -1, XINPUT_GAMEPAD_DPAD_UP));
	m_SceneContext.pInput->AddInputAction(InputAction(MoveDown, InputState::down, VK_S, -1,  XINPUT_GAMEPAD_DPAD_DOWN));
	m_SceneContext.pInput->AddInputAction(InputAction(MoveLeft, InputState::down, VK_A, -1,  XINPUT_GAMEPAD_DPAD_LEFT));
	m_SceneContext.pInput->AddInputAction(InputAction(MoveRight, InputState::down, VK_D, -1, XINPUT_GAMEPAD_DPAD_RIGHT));
	m_SceneContext.pInput->AddInputAction(InputAction(Pause, InputState::released, VK_ESCAPE, -1, XINPUT_GAMEPAD_START));

	//Font
	m_pFont = ContentManager::Load<SpriteFont>(L"SpriteFonts/Consolas_32.fnt");
	m_TextPosition.x = m_SceneContext.windowWidth - 50;
	m_TextPosition.y = 10;
	m_TextPositionCoins.x = 50;
	m_TextPositionCoins.y = 10;
	
	//Post Processing Stack
//=====================
	m_pPostGrayscale = MaterialManager::Get()->CreateMaterial<PostGrayscale>();
	//m_pPostBlur = ...
	m_pPostBlur = MaterialManager::Get()->CreateMaterial<PostBlur>();

	m_pPostVignette = MaterialManager::Get()->CreateMaterial<PostVignette>();

	auto pPostExam = MaterialManager::Get()->CreateMaterial<PostExam>();

	AddPostProcessingEffect(pPostExam);
	//particle
	//Particle System
	//ParticleEmitterSettings settings{};
	
	m_ParticleSettings.velocity = { 0.f,15.f,0.f };
	m_ParticleSettings.minSize = 0.1f;
	m_ParticleSettings.maxSize = 0.2f;
	m_ParticleSettings.minEnergy = 1.f;
	m_ParticleSettings.maxEnergy = 2.f;
	m_ParticleSettings.minScale = 3.5f;
	m_ParticleSettings.maxScale = 5.5f;
	m_ParticleSettings.minEmitterRadius = .2f;
	m_ParticleSettings.maxEmitterRadius = .5f;
	m_ParticleSettings.minWeight = 50.5f;
	m_ParticleSettings.maxWeight = 70.f;
	m_ParticleSettings.color = { 1.f,1.f,1.f, 1.f };

	
	
}

void CrossyRoadScene::Update()
{



	//camera
	m_pPlayerCamera->SetOffset(m_CameraOffset.x, m_CameraOffset.y, m_CameraOffset.z);
	m_pPlayerCamera->SetRotation(m_CameraRot.x, m_CameraRot.y);

	m_SceneContext.pLights->SetDirectionalLight({ m_pPlayerCamera->GetTransform()->GetPosition()}, { 0.740129888f, -0.597205281f, 0.309117377f });

	TextRenderer::Get()->DrawText(m_pFont, StringUtil::utf8_decode(std::to_string(m_pPlayer->GetScore())), m_TextPosition, m_TextColor);
	TextRenderer::Get()->DrawText(m_pFont, StringUtil::utf8_decode(std::to_string(m_pPlayer->GetCoins())), m_TextPositionCoins, m_TextColorCoins);

	if(m_pPlayer->GetIsDead() == true)
	{
		if(!m_isBlurActive)
		{
			//AddPostProcessingEffect(m_pPostBlur);
			//AddPostProcessingEffect(m_pPostGrayscale);
			AddPostProcessingEffect(m_pPostVignette);
			m_isBlurActive = true;

			Sleep(DWORD(100.f));
			
			PauseScene();
		}
	} else 
	{
		if(m_isBlurActive)
		{
			//RemovePostProcessingEffect(m_pPostBlur);
			//RemovePostProcessingEffect(m_pPostGrayscale);
			RemovePostProcessingEffect(m_pPostVignette);
			m_isBlurActive = false;
		}
	}


	//Pause
	if (m_SceneContext.pInput->IsActionTriggered(Pause)) 
	{
		if(!m_isPaused)
		{
			PauseScene();
		} else
		{
			UnPauseScene();
		}
	}

	//check button clicks
	if(m_isPaused)
	{
		if (InputManager::IsMouseButton(InputState::released, VK_LBUTTON))
		{
			auto mouseCor = InputManager::GetMousePosition();
			XMFLOAT2 mousePos{ float(mouseCor.x),float(mouseCor.y) };
			CheckPauseButton(mousePos);
		}
	}


	//Splash
	if (m_pPlayer->isSplashTriggered())
	{
		std::cout << "lily";

		m_pPlayer->SetSplash(false);
		auto playerPos = m_pPlayer->GetTransform()->GetPosition();

	

		if(!m_isParticleRunning)
		{


			m_pParticleSystemObject = AddChild(new GameObject);

			m_pEmitter = m_pParticleSystemObject->AddComponent(new ParticleEmitterComponent(L"Textures/Exam/Particle/Drop.png", m_ParticleSettings, 50));
			m_pEmitter->GetTransform()->Translate(playerPos);
			m_isParticleRunning = true;

		}
		

	}

	if(m_isParticleRunning)
	{
		m_ParticleTimer += m_SceneContext.pGameTime->GetElapsed();
		if(m_ParticleTimer > m_MaxParticleLifetime)
		{
			m_ParticleTimer = 0.f;
			m_isParticleRunning = false;
			RemoveChild(m_pParticleSystemObject, true);
		}
	}
}

void CrossyRoadScene::OnGUI()
{
	if(ImGui::Checkbox("canMove",&m_canMove))
	{
		m_pPlayer->SetMove(m_canMove);
	}

	ImGui::Checkbox("Draw ShadowMap", &m_DrawShadowMap);
	ImGui::SliderFloat("ShadowMap Scale", &m_ShadowMapScale, 0.f, 1.f);

	ImGui::SliderFloat2("RotCamera", ConvertUtil::ToImFloatPtr(m_CameraRot), -90, 90);
	ImGui::SliderFloat3("OffsetCamera", ConvertUtil::ToImFloatPtr(m_CameraOffset), -20, 20);
}

void CrossyRoadScene::PostDraw()
{
	if (m_DrawShadowMap) {

		ShadowMapRenderer::Get()->Debug_DrawDepthSRV({ m_SceneContext.windowWidth - 10.f, 10.f }, { m_ShadowMapScale, m_ShadowMapScale }, { 1.f,0.f });
	}
}

void CrossyRoadScene::MakePauseMenu()
{
	const auto pMaterial = PxGetPhysics().createMaterial(.5f, .5f, .5f);


	////mainBack
	m_pSpriteBack = new GameObject();
	m_pSpriteBack->AddComponent(new SpriteComponent(L"Textures/Exam/InGameMenu/InGameBack.png", { 0.5f,0.5f }));
	AddChild(m_pSpriteBack);
	m_pSpriteBack->GetTransform()->Translate(m_SceneContext.windowWidth / 2.f, m_SceneContext.windowHeight / 2.f, .9f);
	m_pSpriteBack->GetTransform()->Scale(1.f);


	//play sprite
	m_pSpritePlay = new GameObject();
	m_pSpritePlay->SetTag(L"Play");
	m_pSpritePlay->AddComponent(new SpriteComponent(L"Textures/Exam/InGameMenu/Play.png", { 0.5f,0.5f }));
	m_pSpritePlay->GetTransform()->Translate(m_SceneContext.windowWidth / 2.f, m_SceneContext.windowHeight / 2.f, .8f);
	AddChild(m_pSpritePlay);
	////play collider
	m_pColliderPlay = new GameObject();
	m_pColliderPlay->SetTag(L"Play");
	const auto pRigidBody = m_pColliderPlay->AddComponent(new RigidBodyComponent(true));
	pRigidBody->AddCollider(PxBoxGeometry{ 1.7f,0.45f,0.1f }, *pMaterial);

	XMFLOAT3 screenS = { m_SceneContext.windowWidth / 2.f, m_SceneContext.windowHeight / 2.f, .8f };
	XMFLOAT4X4 inv =  m_SceneContext.pCamera->GetViewProjectionInverse();


	m_pColliderPlay->GetTransform()->Translate(0.3f, 1.4f, 2.f);
	m_pColliderPlay->GetTransform()->Scale(1.f);
	AddChild(m_pColliderPlay);


	////Restart sprite
	m_pSpriteRestart = new GameObject();
	m_pSpriteRestart->AddComponent(new SpriteComponent(L"Textures/Exam/InGameMenu/Restart.png", { 0.5f,0.5f }));
	m_pSpriteRestart->GetTransform()->Translate(m_SceneContext.windowWidth / 2.f, m_SceneContext.windowHeight / 2.f, .7f);
	m_pSpriteRestart->GetTransform()->Scale(1.f);
	AddChild(m_pSpriteRestart);
	

	////Settings sprite
	m_pSpriteControls = new GameObject();
	m_pSpriteControls->AddComponent(new SpriteComponent(L"Textures/Exam/InGameMenu/Controls.png", { 0.5f,0.5f }));
	m_pSpriteControls->GetTransform()->Translate(m_SceneContext.windowWidth / 2.f, m_SceneContext.windowHeight / 2.f, .6f);
	m_pSpriteControls->GetTransform()->Scale(1.f);
	AddChild(m_pSpriteControls);
	


	////Home sprite
	m_pSpriteHome = new GameObject();
	m_pSpriteHome->AddComponent(new SpriteComponent(L"Textures/Exam/InGameMenu/Home.png", { 0.5f,0.5f }));
	m_pSpriteHome->GetTransform()->Translate(m_SceneContext.windowWidth / 2.f, m_SceneContext.windowHeight / 2.f, .5f);
	m_pSpriteHome->GetTransform()->Scale(1.f);
	AddChild(m_pSpriteHome);
	
}

void CrossyRoadScene::DeletePauseMenu()
{
	RemoveChild(m_pSpriteBack,true);
	RemoveChild(m_pSpritePlay,true);
	RemoveChild(m_pSpriteRestart, true);
	RemoveChild(m_pSpriteControls, true);
	RemoveChild(m_pSpriteHome, true);
}

bool CrossyRoadScene::CheckPauseButton(XMFLOAT2 pos)
{
	if(pos.x > 550 && pos.x < 620)
	{
		//play
		if (pos.y > 290 && pos.y < 370)
		{
			std::cout << "play";
			UnPauseScene();
		}

		//controls
		if (pos.y > 390 && pos.y < 465)
		{
			std::cout << "controls";
			SceneManager::Get()->SetSceneByName("ControlsScene");
		}
	}

	if(pos.x >657 && pos.x <728)
	{
		//restart
		if(pos.y > 290 && pos.y < 370)
		{
			std::cout << "restart";
			m_SceneContext.pGameTime->Start();
			auto manager = SceneManager::Get();			
			manager->AddGameScene(new RestarterScene());
			manager->NextScene();
		}

		//home
		if(pos.y > 390 && pos.y < 465)
		{
			std::cout << "home";
			//SceneManager::Get()->PreviousScene();
			//Resets gameTime so need to make reset logic
			SceneManager::Get()->SetSceneByName("CrossyMenu");
			
		}

	}
	return false;
}



void CrossyRoadScene::PauseScene()
{
	
	m_isPaused = true;
	m_SceneContext.pGameTime->Stop();
	MakePauseMenu();
}

void CrossyRoadScene::UnPauseScene()
{
	DeletePauseMenu();
	m_isPaused = false;
	m_SceneContext.pGameTime->Start();
}
