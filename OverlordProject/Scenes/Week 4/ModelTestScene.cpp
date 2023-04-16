#include "stdafx.h"
#include "ModelTestScene.h"


ModelTestScene::ModelTestScene() :
	GameScene(L"ModelTestScene") {}

void ModelTestScene::Initialize()
{
	//m_SceneContext.settings.showInfoOverlay = true;
	//m_SceneContext.settings.drawPhysXDebug = true;
	//m_SceneContext.settings.drawGrid = true;
	m_SceneContext.settings.enableOnGUI = true;



	auto pMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.5f);
	//chair
	m_pObject = new GameObject();
	AddChild(m_pObject);

	//material
	//ColorMaterial* pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	// 
	//m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	m_pMaterial->SetDiffuseTexture(L"Textures/Chair_Dark.dds");

	m_pObject->AddComponent(new ModelComponent(L"Meshes/Chair.ovm"));
	m_pObject->GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);


	m_pObject->AddComponent(new RigidBodyComponent(false));
	auto convexMesh = ContentManager::Load<PxConvexMesh>(L"Meshes/Chair.ovpc");
	m_pObject->GetComponent<RigidBodyComponent>()->AddCollider(PxConvexMeshGeometry{ convexMesh },*pMaterial);
	
	m_pObject->GetTransform()->Translate(0.f, 10.f, 0.f);
	
	
	//ground
	GameSceneExt::CreatePhysXGroundPlane(*this);
	

	//PxRigidActorExt::createExclusiveShape(*m_pTriangleActor, PxTriangleMeshGeometry(pTriangleMesh), *pDefaultMaterial);

	

}

void ModelTestScene::Update()
{
}

void ModelTestScene::Draw()
{
}

void ModelTestScene::OnGUI()
{
	m_pMaterial->DrawImGui();
}
