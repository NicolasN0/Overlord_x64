#include "stdafx.h"
#include "RestarterScene.h"
#include "CrossyRoadScene.h"


void RestarterScene::Initialize()
{
	
}

void RestarterScene::Update()
{
	auto manager = SceneManager::Get();
	auto crossyScene = manager->GetSceneByName("CrossyRoad");
	if (crossyScene != NULL)
	{
		manager->RemoveGameScene(manager->GetSceneByName("CrossyRoad"), true);
	}
	manager->AddGameScene(new CrossyRoadScene());
	
	manager->SetSceneByName("CrossyRoad");
}

void RestarterScene::OnGUI()
{
}
