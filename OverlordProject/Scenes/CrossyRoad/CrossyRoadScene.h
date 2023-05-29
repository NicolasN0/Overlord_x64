#pragma once
//#include "C:\DAE\JAAR2P2\GP2\OverlordEngine_x64_Start\OverlordEngine\Scenegraph\GameScene.h"
#include "Scenegraph/GameScene.h"
#include <Materials/Post/PostBlur.h>
#include <Materials/Post/PostGrayscale.h>
#include <Materials/Post/PostVignette.h>

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
	void OnGUI() override;
	void MakePauseMenu();
	void DeletePauseMenu();
	bool CheckPauseButton(XMFLOAT2 pos);

	void PauseScene();
	void UnPauseScene();
	enum InputIds
	{
		MoveUp,
		MoveDown,
		MoveLeft,
		MoveRight,
		Pause
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

	PostBlur* m_pPostBlur{};
	PostGrayscale* m_pPostGrayscale{};
	PostVignette* m_pPostVignette{};

	bool m_isBlurActive{};

	//pauseMenu
	bool m_isPaused{};
	//sprites
	GameObject* m_pSpriteBack;
	GameObject* m_pSpritePlay;
	GameObject* m_pSpriteRestart;
	GameObject* m_pSpriteControls;
	GameObject* m_pSpriteHome;
	//colliders
	GameObject* m_pColliderPlay;
	GameObject* m_pColliderRestart;
	GameObject* m_pColliderControls;
	GameObject* m_pColliderHome;

	//particle
	GameObject* m_pParticleSystemObject;
	float m_ParticleTimer{};
	float m_MaxParticleLifetime{ 1.f };
	bool m_isParticleRunning{};
	ParticleEmitterComponent* m_pEmitter{};
	ParticleEmitterSettings m_ParticleSettings{};

	bool m_canMove{};
};

