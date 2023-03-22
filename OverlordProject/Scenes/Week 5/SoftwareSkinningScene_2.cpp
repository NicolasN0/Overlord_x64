#include "stdafx.h"
#include "SoftwareSkinningScene_2.h"
#include <Materials/ColorMaterial.h>


void SoftwareSkinningScene_2::Initialize()
{
	m_SceneContext.settings.enableOnGUI = true;

	ColorMaterial* pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();

	GameObject* pRoot = new GameObject{};
	m_pBone0 = new BoneObject(pMaterial, 15);
	pRoot->AddChild(m_pBone0);
	m_pBone1 = new BoneObject(pMaterial, 15);
	m_pBone0->AddBone(m_pBone1);

	AddChild(pRoot);

	//PART2
	m_pBone0->CalculateBindPose();

	//test
	m_pBone1->CalculateBindPose();

	GameObject* pBoxDrawer = new GameObject();
	m_pMeshDrawer = pBoxDrawer->AddComponent(new MeshDrawComponent(24,true));
	AddChild(pBoxDrawer);

	InitializeVertices(15);
}

void SoftwareSkinningScene_2::Update()
{
	if (m_AutoRotate)
	{


		if (m_RotationSign == 1)
		{
			m_BoneRotation += 45 * GetSceneContext().pGameTime->GetElapsed();
			if (m_BoneRotation > 45)
			{
				m_RotationSign *= -1;
			}

		}
		else
		{
			m_BoneRotation -= 45 * GetSceneContext().pGameTime->GetElapsed();
			if (m_BoneRotation < -45)
			{
				m_RotationSign *= -1;
			}
		}

		m_pBone0->GetTransform()->Rotate(0, 0, m_BoneRotation);
		m_pBone1->GetTransform()->Rotate(0, 0, m_BoneRotation * 2);
	}
	else
	{

		m_pBone0->GetTransform()->Rotate(0, 0, m_BoneRot1);
		m_pBone1->GetTransform()->Rotate(0, 0, m_BoneRot2);

	}

	//bone1
	auto var1{ m_pBone0->GetBindPose() };
	XMMATRIX pose1{ XMLoadFloat4x4(&var1) };
	auto world1{ XMLoadFloat4x4(&m_pBone0->GetTransform()->GetWorld()) };

	auto matrix1{ XMMatrixMultiply(pose1, world1) };

	//bone2

	auto var2{ m_pBone1->GetBindPose() };
	XMMATRIX pose2{ XMLoadFloat4x4(&var2) };
	auto world2{ XMLoadFloat4x4(&m_pBone1->GetTransform()->GetWorld()) };

	auto matrix2{ XMMatrixMultiply(pose2, world2) };
	
	


	for (int i{}; i < m_SkinnedVertices.size(); i++)
	{

		if(i < 24)
		{
			auto original = XMLoadFloat3(&m_SkinnedVertices[i].originalVertex.Position);
			auto temp = XMVector3TransformCoord(original, matrix1);
			XMFLOAT3 transformed;
			XMStoreFloat3(&transformed, temp);
			m_SkinnedVertices[i].transformedVertex.Position = transformed;
		} else
		{
			auto original = XMLoadFloat3(&m_SkinnedVertices[i].originalVertex.Position);
			auto temp = XMVector3TransformCoord(original, matrix2);
			XMFLOAT3 transformed;
			XMStoreFloat3(&transformed, temp);
			m_SkinnedVertices[i].transformedVertex.Position = transformed;
		}
	
		
	}

	m_pMeshDrawer->RemoveTriangles();
	for (int i{}; i < m_SkinnedVertices.size(); i += 4)
	{
		QuadPosNormCol quad(m_SkinnedVertices[i].transformedVertex, m_SkinnedVertices[i + 1].transformedVertex, m_SkinnedVertices[i + 2].transformedVertex, m_SkinnedVertices[i + 3].transformedVertex);
		m_pMeshDrawer->AddQuad(quad);
	}

	m_pMeshDrawer->UpdateBuffer();
}

void SoftwareSkinningScene_2::OnGUI()
{
	ImGui::DragFloat("Rotation bone 1", &m_BoneRot1, 1.f, -100.f, 100.f, "%.3f", 1.f);
	ImGui::DragFloat("Rotation bone 2", &m_BoneRot2, 1.f, -100.f, 100.f, "%.3f", 1.f);

	ImGui::Checkbox("Auto Rotate", &m_AutoRotate);
}


void SoftwareSkinningScene_2::InitializeVertices(float length)
{
	auto pos = XMFLOAT3(length / 2.f, 0.f, 0.f);
	const auto offset = XMFLOAT3(length / 2.f, 2.5f, 2.5f);
	auto col = XMFLOAT4(1.f, 0.f, 0.f, 0.5f);
#pragma region BOX 1
	//FRONT
	XMFLOAT3 norm = { 0, 0, -1 };
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, offset.y + pos.y, -offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, offset.y + pos.y, -offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, -offset.y + pos.y, -offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, -offset.y + pos.y, -offset.z + pos.z }, norm, col);
	//BACK
	norm = { 0, 0, 1 };
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, offset.y + pos.y, offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, offset.y + pos.y, offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, -offset.y + pos.y, offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, -offset.y + pos.y, offset.z + pos.z }, norm, col);
	//TOP
	norm = { 0, 1, 0 };
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, offset.y + pos.y, offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, offset.y + pos.y, offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, offset.y + pos.y, -offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, offset.y + pos.y, -offset.z + pos.z }, norm, col);
	//BOTTOM
	norm = { 0, -1, 0 };
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, -offset.y + pos.y, -offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, -offset.y + pos.y, -offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, -offset.y + pos.y, offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, -offset.y + pos.y, offset.z + pos.z }, norm, col);
	//LEFT
	norm = { -1, 0, 0 };
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, offset.y + pos.y, offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, offset.y + pos.y, -offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, -offset.y + pos.y, -offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, -offset.y + pos.y, offset.z + pos.z }, norm, col);
	//RIGHT
	norm = { 1, 0, 0 };
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, offset.y + pos.y, -offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, offset.y + pos.y, offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, -offset.y + pos.y, offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, -offset.y + pos.y, -offset.z + pos.z }, norm, col);
#pragma endregion

	col = { 0.f, 1.f, 0.f, 0.5f };
	pos = { 22.5f, 0.f, 0.f };
#pragma region BOX 2
	//FRONT
	norm = { 0, 0, -1 };
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, offset.y + pos.y, -offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, offset.y + pos.y, -offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, -offset.y + pos.y, -offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, -offset.y + pos.y, -offset.z + pos.z }, norm, col);
	//BACK
	norm = { 0, 0, 1 };
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, offset.y + pos.y, offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, offset.y + pos.y, offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, -offset.y + pos.y, offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, -offset.y + pos.y, offset.z + pos.z }, norm, col);
	//TOP
	norm = { 0, 1, 0 };
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, offset.y + pos.y, offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, offset.y + pos.y, offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, offset.y + pos.y, -offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, offset.y + pos.y, -offset.z + pos.z }, norm, col);
	//BOTTOM
	norm = { 0, -1, 0 };
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, -offset.y + pos.y, -offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, -offset.y + pos.y, -offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, -offset.y + pos.y, offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, -offset.y + pos.y, offset.z + pos.z }, norm, col);
	//LEFT
	norm = { -1, 0, 0 };
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, offset.y + pos.y, offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, offset.y + pos.y, -offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, -offset.y + pos.y, -offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ -offset.x + pos.x, -offset.y + pos.y, offset.z + pos.z }, norm, col);
	//RIGHT
	norm = { 1, 0, 0 };
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, offset.y + pos.y, -offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, offset.y + pos.y, offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, -offset.y + pos.y, offset.z + pos.z }, norm, col);
	m_SkinnedVertices.emplace_back(XMFLOAT3{ offset.x + pos.x, -offset.y + pos.y, -offset.z + pos.z }, norm, col);
#pragma endregion
}