#pragma once
#include "C:\DAE\JAAR2P2\GP2\OverlordEngine_x64_Start\OverlordEngine\Scenegraph\GameObject.h"
#include <Materials/ColorMaterial.h>
class GrassLane :
    public GameObject
{
public:
	GrassLane();
	~GrassLane() override = default;

	GrassLane(const GrassLane& other) = delete;
	GrassLane(GrassLane&& other) noexcept = delete;
	GrassLane& operator=(const GrassLane& other) = delete;
	GrassLane& operator=(GrassLane&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext & sceneContext) override;
	void Update(const SceneContext&) override;

private:
	float m_Width{}, m_Height{}, m_Depth{};
	XMFLOAT4 m_Color{};
	ColorMaterial* m_pMaterial;
};

