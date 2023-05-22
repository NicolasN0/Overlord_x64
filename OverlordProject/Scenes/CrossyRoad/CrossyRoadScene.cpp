#include "stdafx.h"
#include "CrossyRoadScene.h"
#include "Prefabs/Exam/CrossyCharacter.h"
#include "Prefabs/Exam/GrassLane.h"
#include "Prefabs/Exam/LaneManager.h"
#include "Prefabs/Exam/PlayerCamera.h"


#define VK_W 0x57
#define VK_S 0x53
#define VK_A 0x41
#define VK_D 0x44

void CrossyRoadScene::Initialize()
{
	m_SceneContext.settings.enableOnGUI = true;
	m_SceneContext.settings.drawGrid = false;

	const auto pDefaultMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.5f);
	GameSceneExt::CreatePhysXGroundPlane(*this, pDefaultMaterial);

	//manager
	m_pLaneManager = AddChild(new LaneManager());
	//player
	m_pPlayer = AddChild(new CrossyCharacter(m_pLaneManager));
	//Camera
	const auto pCamera = AddChild(new PlayerCamera(m_pPlayer,XMFLOAT3{3,20,-3}));
	m_pCameraComponent = pCamera->GetComponent<CameraComponent>();
	m_pCameraComponent->SetActive(true); //Uncomment to make this camera the active camera

	//AddChild(new GrassLane());
	//AddChild(new LaneManager());

	m_SceneContext.pInput->AddInputAction(InputAction(MoveUp, InputState::down, VK_W, -1, XINPUT_GAMEPAD_DPAD_UP));
	m_SceneContext.pInput->AddInputAction(InputAction(MoveDown, InputState::down, VK_S, -1,  XINPUT_GAMEPAD_DPAD_DOWN));
	m_SceneContext.pInput->AddInputAction(InputAction(MoveLeft, InputState::down, VK_A, -1,  XINPUT_GAMEPAD_DPAD_LEFT));
	m_SceneContext.pInput->AddInputAction(InputAction(MoveRight, InputState::down, VK_D, -1, XINPUT_GAMEPAD_DPAD_RIGHT));

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
	
}

void CrossyRoadScene::Update()
{
	TextRenderer::Get()->DrawText(m_pFont, StringUtil::utf8_decode(std::to_string(m_pPlayer->GetScore())), m_TextPosition, m_TextColor);
	TextRenderer::Get()->DrawText(m_pFont, StringUtil::utf8_decode(std::to_string(m_pPlayer->GetCoins())), m_TextPositionCoins, m_TextColorCoins);

	if(m_pPlayer->GetIsDead() == true)
	{
		if(!m_isBlurActive)
		{
			AddPostProcessingEffect(m_pPostBlur);
			AddPostProcessingEffect(m_pPostGrayscale);
			m_isBlurActive = true;
		}
	} else 
	{
		if(m_isBlurActive)
		{
			RemovePostProcessingEffect(m_pPostBlur);
			RemovePostProcessingEffect(m_pPostGrayscale);
			m_isBlurActive = false;
		}
	}

}
