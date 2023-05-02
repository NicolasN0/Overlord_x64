#pragma once
#include "C:\DAE\JAAR2P2\GP2\OverlordEngine_x64_Start\OverlordEngine\Scenegraph\GameObject.h"
#include <Materials/ColorMaterial.h>
class Car :
    public GameObject
{
public:
	Car(int posX, int posZ);
	~Car() override = default;

	Car(const Car& other) = delete;
	Car(Car&& other) noexcept = delete;
	Car& operator=(const Car& other) = delete;
	Car& operator=(Car&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext & sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:
	ColorMaterial* m_pMaterial{};
	int m_Width{};
	float m_CurX{};
	int m_PosZ{};
	int m_CarSpeed{};
};

