#pragma once
#include "Scenegraph/GameObject.h"
class PlayerCamera :
    public GameObject
{
public:
	PlayerCamera(GameObject* player,XMFLOAT3 offset);
	~PlayerCamera() override = default;
	PlayerCamera(const PlayerCamera& other) = delete;
	PlayerCamera(PlayerCamera&& other) noexcept = delete;
	PlayerCamera& operator=(const PlayerCamera& other) = delete;
	PlayerCamera& operator=(PlayerCamera&& other) noexcept = delete;

	void SetRotation(float pitch, float yaw);
	void SetOffset(float x, float y,float z);
protected:

	void Initialize(const SceneContext & sceneContext) override;
	void Update(const SceneContext & sceneContext) override;

private:

	float m_TotalPitch{}, m_TotalYaw{};
	float m_MoveSpeed{ 10.f }, m_RotationSpeed{ 10.f }, m_SpeedMultiplier{ 10.f };
	CameraComponent* m_pCamera{};
	GameObject* m_pPlayer{};
	XMFLOAT3 m_Offset{};
	XMFLOAT3 m_CurPos{};
	XMFLOAT3 m_FuturePos{};
	float m_CameraSpeed{1.f};
	float m_HorCameraSpeed{ 2.f };
	float m_CameraLerpTimer{};

};

