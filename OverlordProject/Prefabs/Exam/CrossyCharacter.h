#pragma once
#include "Scenegraph/GameObject.h"
#include <Materials/ColorMaterial.h>

class LaneManager;

class CrossyCharacter :
    public GameObject
{
public:
	CrossyCharacter(LaneManager* manager);
	~CrossyCharacter() override = default;

	CrossyCharacter(const CrossyCharacter& other) = delete;
	CrossyCharacter(CrossyCharacter&& other) noexcept = delete;
	CrossyCharacter& operator=(const CrossyCharacter& other) = delete;
	CrossyCharacter& operator=(CrossyCharacter&& other) noexcept = delete;

	void DrawImGui();
	int GetCoins();
	void SetCoints(int coins);
	int GetScore();
	bool GetIsDead();
	
	void SetMove(bool canMove);
	//splash
	void SetSplash(bool splashTriggered);
	bool isSplashTriggered();
protected:
	void Initialize(const SceneContext&) override;
	void Update(const SceneContext&) override;
private:
	//CameraComponent* m_pCameraComponent{};
	//ControllerComponent* m_pControllerComponent{};
	void CheckWater();
	void Dies();

	//startUp check
	bool m_isStartupDone{};
	float m_maxStartupTime{ 2.f };
	float m_curStartupTime{};
	void CheckStartup(const SceneContext& sceneContext);

	enum InputIds
	{
		MoveUp,
		MoveDown,
		MoveLeft,
		MoveRight,
	};
	LaneManager* m_pLaneManager;

	float m_MoveTime{};
	XMFLOAT3 m_prevPos{};
	XMFLOAT3 m_futurePos{};
	XMFLOAT3 m_StartPos{};
	ColorMaterial* m_pMaterial;

	bool m_isMoving{};
	bool m_isSinking{};
	bool m_isDead{false};
	float m_MaxMoveTime{1.f};
	float m_CharSpeed{ 2.5f };
	float m_JumpHeight{ 1.5f };
	int m_Coins{};
	int m_Score{};

	//splash
	int m_SplashTriggered{};

	//debug
	bool m_CanMove{};
	

};

