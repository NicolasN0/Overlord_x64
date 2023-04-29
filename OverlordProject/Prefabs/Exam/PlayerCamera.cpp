#include "stdafx.h"
#include "PlayerCamera.h"

void PlayerCamera::Initialize(const SceneContext& /*sceneContext*/)
{
	m_pCamera = new CameraComponent();
	AddComponent(m_pCamera);
	SetRotation(90, 0);
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


void PlayerCamera::Update(const SceneContext& /*sceneContext*/)
{
	XMFLOAT3 playerPos = m_pPlayer->GetTransform()->GetPosition();

	GetTransform()->Translate(XMFLOAT3{playerPos.x + m_Offset.x,playerPos.y + m_Offset.y,playerPos.z + m_Offset.z});


	XMFLOAT3 pos = GetTransform()->GetPosition();
	XMVECTOR eye = XMVECTOR{ pos.x, pos.y, pos.z };
	XMVECTOR focus = XMVECTOR{ playerPos.x, playerPos.y, playerPos.z };
	XMVECTOR up = XMVECTOR{ 0, 1, 0 };
	auto rot = XMQuaternionRotationMatrix(XMMatrixLookAtLH(eye, focus, up));

	GetTransform()->Rotate(m_TotalPitch, m_TotalYaw, 0);
	//GetTransform()->Rotate(rot);

}
