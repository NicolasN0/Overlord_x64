#include "stdafx.h"
#include "PlayerCamera.h"

void PlayerCamera::Initialize(const SceneContext& /*sceneContext*/)
{
	m_pCamera = new CameraComponent();
	AddComponent(m_pCamera);
	//SetRotation(90, 0);
	SetRotation(70, -30);
}

PlayerCamera::PlayerCamera(GameObject* player, XMFLOAT3 offset)
{
	m_pPlayer = player;
	m_Offset = offset;
}

void PlayerCamera::SetRotation(float pitch, float yaw)
{
	m_TotalPitch = pitch;
	m_TotalYaw = yaw;
}

void PlayerCamera::SetOffset(float x, float y, float z)
{
	m_Offset.x = x;
	m_Offset.y = y;
	m_Offset.z = z;
}


void PlayerCamera::Update(const SceneContext& /*sceneContext*/)
{
	XMFLOAT3 playerPos = m_pPlayer->GetTransform()->GetPosition();

	GetTransform()->Translate(XMFLOAT3{playerPos.x + m_Offset.x,playerPos.y + m_Offset.y,playerPos.z + m_Offset.z});


	GetTransform()->Rotate(m_TotalPitch, m_TotalYaw, 0);
	

}
