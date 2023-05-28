#pragma once
#include "Scenegraph/GameScene.h"
class ControlsScene :
    public GameScene
{
public:
	ControlsScene() : GameScene(L"ControlsScene") {	}
	~ControlsScene() override = default;
	ControlsScene(const ControlsScene& other) = delete;
	ControlsScene(ControlsScene&& other) noexcept = delete;
	ControlsScene& operator=(const ControlsScene& other) = delete;
	ControlsScene& operator=(ControlsScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void OnGUI() override;
private:
	GameObject* m_pFixedCamera;
	CameraComponent* m_pCameraComponent;

	
	GameObject* m_pSpriteButton;

	GameObject* m_pTestHeight;

	XMFLOAT3 m_PosSetting{};
	float m_Height{};

	//font
	SpriteFont* m_pFont{};
	

	std::string m_TextW{ "Jump one space ahead" };
	std::string m_TextA{ "Jump one to the left" };
	std::string m_TextS{ "Jump one space back" };
	std::string m_TextD{ "Jump one to the right" };
	std::string m_TextEsc{ "Pause game" };
	std::string m_TextTest{ "Test" };
	XMFLOAT2 m_TextPosition{};
	XMFLOAT2 m_TextPositionW{495.f,120.f};
	XMFLOAT2 m_TextPositionA{ 495.f,227.f };
	XMFLOAT2 m_TextPositionS{ 495.f,334.f };
	XMFLOAT2 m_TextPositionD{ 495.f,440.f };
	XMFLOAT2 m_TextPositionEsc{ 495.f,545.f };
	XMFLOAT4 m_TextColor{ 1.f,1.f,1.f,1.f };
};

