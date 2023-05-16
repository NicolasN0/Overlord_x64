#pragma once
#include "C:\DAE\JAAR2P2\GP2\OverlordEngine_x64_Start\OverlordEngine\Scenegraph\GameObject.h"
class LaneManager :
    public GameObject
{
public:
	LaneManager();
	~LaneManager() override = default;

	LaneManager(const LaneManager& other) = delete;
	LaneManager(LaneManager&& other) noexcept = delete;
	LaneManager& operator=(const LaneManager& other) = delete;
	LaneManager& operator=(LaneManager&& other) noexcept = delete;

	bool GetIsPassable(int posX, int posZ);
	int GetWidth();
	void IncreasePlayerCount();
	bool IsOnWater(int posX, int posZ);
protected:
	void Initialize(const SceneContext & sceneContext) override;
	void Update(const SceneContext& sceneContext) override;
	void MakeGrassLane();
	void MakeRoadLane();
	void MakeWaterLane();
	void UpdateLanes();

private:
	std::vector<GameObject*> m_pLanes;
	int m_LaneCounter{};
	int m_Width{25};
	int m_PlayerCount{};

	float m_TestTimer{};
};

