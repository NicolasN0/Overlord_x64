#pragma once
#include "Scenegraph/GameObject.h"
#include <Materials/ColorMaterial.h>
#include <Materials\Shadow\DiffuseMaterial_Shadow.h>

class Coin;

class RoadLane :
    public GameObject
{
public:
	RoadLane(int count, int width);
	~RoadLane() override = default;

	RoadLane(const RoadLane& other) = delete;
	RoadLane(RoadLane&& other) noexcept = delete;
	RoadLane& operator=(const RoadLane& other) = delete;
	RoadLane& operator=(RoadLane&& other) noexcept = delete;

	std::vector<bool> GetObstacles();
	void RemoveCoin(Coin* coin);
protected:
	void Initialize(const SceneContext & sceneContext) override;
	void Update(const SceneContext & sceneContext) override;
	void OnSceneDetach(GameScene* /*pScene*/) override;
	void PlaceCoins();

private:
	XMFLOAT4 m_Color{};
	//ColorMaterial* m_pMaterial{};
	DiffuseMaterial_Shadow* m_pMaterial{};
	int m_Count{};
	std::vector<GameObject*> m_pObstacles{};
	std::vector<GameObject*> m_pCoins{};
	GameObject* m_pCar{};
	std::vector<bool> m_hasObstacle{};
	std::vector<bool> m_hasCoin{};
	int m_Width{};
};

