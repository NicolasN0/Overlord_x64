#pragma once
#include "Scenegraph/GameObject.h"
#include <Materials/ColorMaterial.h>
class WaterLane :
    public GameObject
{
public:
	WaterLane(int count, int width);
	~WaterLane() override = default;

	WaterLane(const WaterLane& other) = delete;
	WaterLane(WaterLane&& other) noexcept = delete;
	WaterLane& operator=(const WaterLane& other) = delete;
	WaterLane& operator=(WaterLane&& other) noexcept = delete;

	std::vector<bool> GetObstacles();
	std::vector<bool> GetLilys();
protected:
	void Initialize(const SceneContext & sceneContext) override;
	void Update(const SceneContext & sceneContext) override;
	void PlaceLilys();

private:
	XMFLOAT4 m_Color{ 0,0.714f,1,1 };
	ColorMaterial* m_pMaterial{};
	int m_Count{};
	std::vector<bool> m_hasObstacle{};
	std::vector<bool> m_hasLily{};
	std::vector<GameObject*> m_pLilys{};
	bool m_LilyLane{};
	int m_Width{};
};

