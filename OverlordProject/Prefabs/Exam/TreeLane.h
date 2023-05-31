#pragma once
#include "Scenegraph/GameObject.h"
#include <Materials/ColorMaterial.h>
class TreeLane :
    public GameObject
{
public:
	TreeLane(int count, int width);
	~TreeLane() override = default;

	TreeLane(const TreeLane& other) = delete;
	TreeLane(TreeLane&& other) noexcept = delete;
	TreeLane& operator=(const TreeLane& other) = delete;
	TreeLane& operator=(TreeLane&& other) noexcept = delete;

	std::vector<bool> GetObstacles();

protected:
	void Initialize(const SceneContext & sceneContext) override;
	void Update(const SceneContext & sceneContext) override;
	void PlaceObstacles();

private:
	XMFLOAT4 m_Color{};
	ColorMaterial* m_pMaterial{};
	int m_Count{};
	std::vector<GameObject*> m_pObstacles{};
	std::vector<bool> m_hasObstacle{};
	int m_Width{};


};

