#pragma once
#include "C:\DAE\JAAR2P2\GP2\OverlordEngine_x64_Start\OverlordEngine\Scenegraph\GameObject.h"
#include <Materials/ColorMaterial.h>
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

