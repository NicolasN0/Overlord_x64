#pragma once
#include "Scenegraph/GameObject.h"
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
	void MakeTrainLane();
	void MakeRandomLane();
	void UpdateLanes();

	void MakeStarterTreeLanes();
	void CheckDeleteLanes();
private:
	std::vector<GameObject*> m_pLanes;
	std::vector<GameObject*> m_pStarterLanes;
	int m_LaneCounter{};
	int m_Width{25};
	int m_PlayerCount{};

	float m_TestTimer{};

	//deleting
	int m_DeleteCount{};
	//8 way to go
	int m_DeleteStepsRange{8};
	bool m_Deleted{};
	bool m_StarterLanesDeleted{};
};

