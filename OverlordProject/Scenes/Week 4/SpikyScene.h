#pragma once
//#include "C:\DAE\JAAR2P2\GP2\OverlordEngine_x64_Start\OverlordEngine\Scenegraph\GameScene.h"
#include "Scenegraph/GameScene.h"
#include <Materials/ColorMaterial.h>
#include <Materials/DiffuseMaterial.h>
#include <Materials/SpikyMaterial.h>

class SpikyScene final : public GameScene
{
public:
	SpikyScene();
	~SpikyScene() override = default;

	SpikyScene(const SpikyScene& other) = delete;
	SpikyScene(SpikyScene&& other) noexcept = delete;
	SpikyScene& operator=(const SpikyScene& other) = delete;
	SpikyScene& operator=(SpikyScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void OnGUI() override;

private:
	GameObject* m_pObject{};
	//ColorMaterial* m_pMaterial{};
	SpikyMaterial* m_pMaterial{};
};

