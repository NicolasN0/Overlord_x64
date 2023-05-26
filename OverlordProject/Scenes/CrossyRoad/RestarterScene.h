#pragma once
//#include "C:\DAE\JAAR2P2\GP2\OverlordEngine_x64_Start\OverlordEngine\Scenegraph\GameScene.h"
#include "Scenegraph/GameScene.h"
class RestarterScene :
    public GameScene
{
public:
	RestarterScene() : GameScene(L"RestarterScene") {	}
	~RestarterScene() override = default;
	RestarterScene(const RestarterScene& other) = delete;
	RestarterScene(RestarterScene&& other) noexcept = delete;
	RestarterScene& operator=(const RestarterScene& other) = delete;
	RestarterScene& operator=(RestarterScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void OnGUI() override;
private:
	/*GameObject* m_pFixedCamera;
	CameraComponent* m_pCameraComponent;

	SpriteFont* m_pFont{};
	XMFLOAT2 m_TextPosition{};
	XMFLOAT4 m_TextColor{ 1.f,1.f,1.f,1.f };

	GameObject* m_pSpriteButton;

	GameObject* m_pTestHeight;

	XMFLOAT3 m_PosSetting{};
	float m_Height{};*/
};

