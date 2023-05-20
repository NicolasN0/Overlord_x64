#pragma once
#include "C:\DAE\JAAR2P2\GP2\OverlordEngine_x64_Start\OverlordEngine\Scenegraph\GameScene.h"

class LaneManager;
class CrossyCharacter;

class CrossyRoadScene :
    public GameScene
{
public:
	CrossyRoadScene() : GameScene(L"CrossyRoadScene") {	}
	~CrossyRoadScene() override = default;
	CrossyRoadScene(const CrossyRoadScene& other) = delete;
	CrossyRoadScene(CrossyRoadScene&& other) noexcept = delete;
	CrossyRoadScene& operator=(const CrossyRoadScene& other) = delete;
	CrossyRoadScene& operator=(CrossyRoadScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;

	enum InputIds
	{
		MoveUp,
		MoveDown,
		MoveLeft,
		MoveRight,		
	};

private:
	CrossyCharacter* m_pPlayer;
	LaneManager* m_pLaneManager;
	CameraComponent* m_pCameraComponent;

	SpriteFont* m_pFont{};
	XMFLOAT2 m_TextPosition{};
	XMFLOAT4 m_TextColor{ 1.f,1.f,1.f,1.f };

	XMFLOAT2 m_TextPositionCoins{};
	XMFLOAT4 m_TextColorCoins{ 1.f,1.f,0.f,1.f };
};

