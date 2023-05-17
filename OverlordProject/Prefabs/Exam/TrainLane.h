#pragma once
#include "Scenegraph/GameObject.h"
#include <Materials/ColorMaterial.h>
class TrainLane :
    public GameObject
{
public:
	TrainLane(int count, int width);
	~TrainLane() override = default;

	TrainLane(const TrainLane& other) = delete;
	TrainLane(TrainLane&& other) noexcept = delete;
	TrainLane& operator=(const TrainLane& other) = delete;
	TrainLane& operator=(TrainLane&& other) noexcept = delete;

	std::vector<bool> GetObstacles();

protected:
	void Initialize(const SceneContext & sceneContext) override;
	void Update(const SceneContext & sceneContext) override;


private:
	XMFLOAT4 m_Color{};
	ColorMaterial* m_pMaterial{};
	int m_Count{};
	std::vector<GameObject*> m_pObstacles{};
	std::vector<bool> m_hasObstacle{};
	int m_Width{};
};

