#pragma once
#include "C:\DAE\JAAR2P2\GP2\OverlordEngine_x64_Start\OverlordEngine\Scenegraph\GameScene.h"
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
	GameObject* m_pPlayer;
	GameObject* m_pLaneManager;
};

