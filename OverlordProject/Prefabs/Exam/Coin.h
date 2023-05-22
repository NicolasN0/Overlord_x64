#pragma once
#include "Scenegraph/GameObject.h"
#include <Materials/DiffuseMaterial.h>
class Coin :
    public GameObject
{
public:
	Coin(int posX, int posZ);
	~Coin() override = default;

	Coin(const Coin& other) = delete;
	Coin(Coin&& other) noexcept = delete;
	Coin& operator=(const Coin& other) = delete;
	Coin& operator=(Coin&& other) noexcept = delete;

	void PickedUp(bool picked);
protected:
	void Initialize(const SceneContext & sceneContext) override;
	void Update(const SceneContext & sceneContext) override;

private:
	DiffuseMaterial* m_pMaterial{};
	int m_Width{};
	int m_PosX{};
	int m_PosZ{};
	int m_CarSpeed{};

	bool m_PickedUp{};
};

