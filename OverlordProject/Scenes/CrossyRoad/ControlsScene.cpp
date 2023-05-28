#include "stdafx.h"
#include "ControlsScene.h"

void ControlsScene::Initialize()
{
	m_SceneContext.settings.enableOnGUI = true;
	m_SceneContext.settings.drawGrid = false;

	m_SceneContext.settings.clearColor = XMFLOAT4(40.f / 255.f, 160.f / 255.f, 125.f / 255.f, 1);

	//name
	SetName("ControlsScene");

	m_pFixedCamera = new GameObject();
	AddChild(m_pFixedCamera);
	auto cameraComp = m_pFixedCamera->AddComponent(new CameraComponent());
	cameraComp->SetActive(true);
	cameraComp->UseOrthographicProjection();
	cameraComp->SetOrthoSize(10);





	////main
	m_pSpriteButton = new GameObject();
	m_pSpriteButton->AddComponent(new SpriteComponent(L"Textures/Exam/Controls/ControlsSprite.png", { 0.5f,0.5f }));
	AddChild(m_pSpriteButton);
	m_pSpriteButton->GetTransform()->Translate(m_SceneContext.windowWidth / 2.f - (m_SceneContext.windowWidth / 4.f), m_SceneContext.windowHeight / 2.f, .9f);
	m_pSpriteButton->GetTransform()->Scale(1.f);

	//font
	m_pFont = ContentManager::Load<SpriteFont>(L"SpriteFonts/CrossyRoad.fnt");

	//home button
	m_pSpriteHome = new GameObject();
	m_pSpriteHome->AddComponent(new SpriteComponent(L"Textures/Exam/InGameMenu/Home.png", { 0.5f,0.5f }));
	m_pSpriteHome->GetTransform()->Translate(0,m_SceneContext.windowHeight - 125.f, .5f);
	m_pSpriteHome->GetTransform()->Scale(1.f);
	AddChild(m_pSpriteHome);
}

void ControlsScene::Update()
{
	//TextRenderer::Get()->DrawText(m_pFont, StringUtil::utf8_decode(m_TextTest), m_TextPosition, m_TextColor);

	TextRenderer::Get()->DrawText(m_pFont, StringUtil::utf8_decode(m_TextW), m_TextPositionW, m_TextColor);

	TextRenderer::Get()->DrawText(m_pFont, StringUtil::utf8_decode(m_TextA), m_TextPositionA, m_TextColor);

	TextRenderer::Get()->DrawText(m_pFont, StringUtil::utf8_decode(m_TextS), m_TextPositionS, m_TextColor);

	TextRenderer::Get()->DrawText(m_pFont, StringUtil::utf8_decode(m_TextD), m_TextPositionD, m_TextColor);

	TextRenderer::Get()->DrawText(m_pFont, StringUtil::utf8_decode(m_TextEsc), m_TextPositionEsc, m_TextColor);

	TextRenderer::Get()->DrawText(m_pFont, StringUtil::utf8_decode(m_TextPlay), m_TextPositionPlay, m_TextColor);

	if (InputManager::IsMouseButton(InputState::pressed, VK_LBUTTON))
	{
		auto mouseCor = InputManager::GetMousePosition();
		XMFLOAT2 mousePos{ float(mouseCor.x),float(mouseCor.y) };
		//std::cout << mousePos.x << " " << mousePos.y << std::endl;

		if(mousePos.x > 17.f && mousePos.x < 87.f && mousePos.y > 625.f && mousePos.y < 695.f)
		{
			SceneManager::Get()->SetSceneByName("CrossyMenu");
		} else 
		{
			//just clicked on page so got to game
			SceneManager::Get()->SetSceneByName("CrossyRoad");
		}
	}
}

void ControlsScene::OnGUI()
{
	char buffer[256]{};
	m_TextA.copy(&buffer[0], 256);
	if (ImGui::InputText("Text", &buffer[0], 256))
	{
		m_TextA = std::string(buffer);
	}

	ImGui::SliderFloat2("Position", &m_TextPosition.x, 1, m_SceneContext.windowWidth);
	ImGui::ColorEdit4("Color", &m_TextColor.x, ImGuiColorEditFlags_NoInputs);
}
