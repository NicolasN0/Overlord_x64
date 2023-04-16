#include "stdafx.h"
#include "UberMaterialScene.h"


UberMaterialScene::UberMaterialScene() :
	GameScene(L"ModelTestScene") {}

void UberMaterialScene::Initialize()
{
	//m_SceneContext.settings.showInfoOverlay = true;
	//m_SceneContext.settings.drawPhysXDebug = true;
	m_SceneContext.settings.drawGrid = false;
	m_SceneContext.settings.enableOnGUI = true;

	
	m_pObject = new GameObject();
	AddChild(m_pObject);
	m_pObject->GetTransform()->Scale(20.f);
	m_pUberMaterial = MaterialManager::Get()->CreateMaterial<UberMaterial>();
	

	auto pModel = new ModelComponent(L"Meshes/Sphere.ovm");
	pModel->SetMaterial(m_pUberMaterial);
	m_pObject->AddComponent(pModel);


}

void UberMaterialScene::Update()
{
	m_pObject->GetTransform()->Rotate(XMFLOAT3{ 0.f, m_TotalRot, 0.0f }, true);
	m_TotalRot += GetSceneContext().pGameTime->GetElapsed() * 30;

}

void UberMaterialScene::Draw()
{
}

void UberMaterialScene::OnGUI()
{
	m_pUberMaterial->DrawImGui();
}
