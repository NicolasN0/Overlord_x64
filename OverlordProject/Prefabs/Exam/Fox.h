#pragma once
#include "Scenegraph/GameObject.h"
#include <Materials\DiffuseMaterial_Skinned.h>
class Fox :
    public GameObject
{
public:
	Fox(int posX, int posZ);
	~Fox() override = default;

	Fox(const Fox& other) = delete;
	Fox(Fox&& other) noexcept = delete;
	Fox& operator=(const Fox& other) = delete;
	Fox& operator=(Fox&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext & sceneContext) override;
	void Update(const SceneContext & sceneContext) override;

private:
	DiffuseMaterial_Skinned* m_pMaterial{};


	int m_Width{};
	float m_CurX{};
	int m_PosZ{};
	int m_Speed{};

	float m_Counter{};
	//one start before move is 7 with animation speed 1
	float m_DelayTimer{ 3.5f };
	bool m_CanMove{};
};

