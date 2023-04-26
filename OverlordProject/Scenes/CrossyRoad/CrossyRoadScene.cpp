#include "stdafx.h"
#include "CrossyRoadScene.h"
#include "Prefabs/Exam/CrossyCharacter.h"
#include "Prefabs/Exam/GrassLane.h"
#include "Prefabs/Exam/LaneManager.h"


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

	m_pPlayer = AddChild(new CrossyCharacter());
	m_pLaneManager = AddChild(new LaneManager());

	//AddChild(new GrassLane());
	//AddChild(new LaneManager());

	m_SceneContext.pInput->AddInputAction(InputAction(MoveUp, InputState::down, VK_W, -1, XINPUT_GAMEPAD_DPAD_UP));
	m_SceneContext.pInput->AddInputAction(InputAction(MoveDown, InputState::down, VK_S, -1,  XINPUT_GAMEPAD_DPAD_DOWN));
	m_SceneContext.pInput->AddInputAction(InputAction(MoveLeft, InputState::down, VK_A, -1,  XINPUT_GAMEPAD_DPAD_LEFT));
	m_SceneContext.pInput->AddInputAction(InputAction(MoveRight, InputState::down, VK_D, -1, XINPUT_GAMEPAD_DPAD_RIGHT));
	
}

void CrossyRoadScene::Update()
{
}
