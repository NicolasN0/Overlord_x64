#pragma once
#include "Scenegraph/GameObject.h"
#include <Materials/DiffuseMaterial.h>
class Train : public GameObject
{
public:
	Train(int posX, int posZ);
	~Train() override = default;

	Train(const Train& other) = delete;
	Train(Train&& other) noexcept = delete;
	Train& operator=(const Train& other) = delete;
	Train& operator=(Train&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext & sceneContext) override;
	void Update(const SceneContext & sceneContext) override;

private:
	DiffuseMaterial* m_pMaterial{};
	int m_Width{};
	float m_CurX{};
	int m_PosZ{};
	int m_CarSpeed{80};
};

