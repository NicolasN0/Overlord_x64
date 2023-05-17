#pragma once
#include "Scenegraph/GameObject.h"
#include <Materials/ColorMaterial.h>
class GrassLane :
    public GameObject
{
public:
	GrassLane(int count,int width);
	~GrassLane() override = default;

	GrassLane(const GrassLane& other) = delete;
	GrassLane(GrassLane&& other) noexcept = delete;
	GrassLane& operator=(const GrassLane& other) = delete;
	GrassLane& operator=(GrassLane&& other) noexcept = delete;

	std::vector<bool> GetObstacles();

protected:
	void Initialize(const SceneContext & sceneContext) override;
	void Update(const SceneContext& sceneContext) override;
	void PlaceObstacles();

private:
	XMFLOAT4 m_Color{};
	ColorMaterial* m_pMaterial{};
	int m_Count{};
	std::vector<GameObject*> m_pObstacles{};
	std::vector<bool> m_hasObstacle{};
	int m_Width{};

	
};

