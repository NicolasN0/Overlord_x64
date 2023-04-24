#pragma once
#include "C:\DAE\JAAR2P2\GP2\OverlordEngine_x64_Start\OverlordEngine\Scenegraph\GameObject.h"
#include <Materials/ColorMaterial.h>
class CrossyCharacter :
    public GameObject
{
public:
	CrossyCharacter();
	~CrossyCharacter() override = default;

	CrossyCharacter(const CrossyCharacter& other) = delete;
	CrossyCharacter(CrossyCharacter&& other) noexcept = delete;
	CrossyCharacter& operator=(const CrossyCharacter& other) = delete;
	CrossyCharacter& operator=(CrossyCharacter&& other) noexcept = delete;

	void DrawImGui();

protected:
	void Initialize(const SceneContext&) override;
	void Update(const SceneContext&) override;
private:
	//CameraComponent* m_pCameraComponent{};
	//ControllerComponent* m_pControllerComponent{};
	enum InputIds
	{
		MoveUp,
		MoveDown,
		MoveLeft,
		MoveRight,
	};

	float m_MoveTime{};
	XMFLOAT3 m_prevPos{};
	XMFLOAT3 m_futurePos{};
	ColorMaterial* m_pMaterial;

	bool m_isMoving{};
	float m_MaxMoveTime{1.f};
};

