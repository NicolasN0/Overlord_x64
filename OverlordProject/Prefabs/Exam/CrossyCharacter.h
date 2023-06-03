#pragma once
#include "Scenegraph/GameObject.h"
#include <Materials/ColorMaterial.h>
#include <Materials/DiffuseMaterial_Skinned.h>
#include <Materials/DiffuseMaterial.h>
class LaneManager;

struct CrossyCharacterDesc
{
	CrossyCharacterDesc() {};
	CrossyCharacterDesc(
		PxMaterial* pMaterial,
		float radius = .2f,
		float height = 2.f)
	{
		controller.setToDefault();
		controller.radius = radius;
		controller.height = height;
		controller.material = pMaterial;
	}

	float maxMoveSpeed{ 15.f };
	float maxFallSpeed{ 15.f };

	float JumpSpeed{ 15.f };

	float moveAccelerationTime{ .3f };
	float fallAccelerationTime{ .3f };

	PxCapsuleControllerDesc controller{};

	float rotationSpeed{ 60.f };

	int actionId_MoveLeft{ -1 };
	int actionId_MoveRight{ -1 };
	int actionId_MoveForward{ -1 };
	int actionId_MoveBackward{ -1 };
	
};


class CrossyCharacter :
    public GameObject
{
public:
	CrossyCharacter(LaneManager* manager, const CrossyCharacterDesc& characterDesc);
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
	void Dies();
	void IncreaseCoins();

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
	void MoveCheckLogic(const SceneContext&);
	void MoveTimer(const SceneContext&);
	void MoveChar(const SceneContext&);


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
	//ColorMaterial* m_pMaterial;
	DiffuseMaterial* m_pMaterial{};
	//DiffuseMaterial_Skinned* m_pMaterial;

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

	//sound
	FMOD::Sound* m_pSoundBounce{};
	FMOD::Sound* m_pSoundChicken{};
	FMOD::Sound* m_pSoundSplash{};
	//FMOD::Sound* m_pSoundCoin{};
	FMOD::Channel* m_pSoundChannel{};
	
	//chicken soundDelay

	//character
	ControllerComponent* m_pControllerComponent{};

	CrossyCharacterDesc m_CharacterDesc;
	
};

