#pragma once
#include "C:\DAE\JAAR2P2\GP2\OverlordEngine_x64_Start\OverlordEngine\Scenegraph\GameScene.h"
#include <Materials/ColorMaterial.h>
#include <Materials/DiffuseMaterial.h>
class ModelTestScene final : public GameScene
{
public:
	ModelTestScene();
	~ModelTestScene() override = default;

	ModelTestScene(const ModelTestScene& other) = delete;
	ModelTestScene(ModelTestScene&& other) noexcept = delete;
	ModelTestScene& operator=(const ModelTestScene& other) = delete;
	ModelTestScene& operator=(ModelTestScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void OnGUI() override;

private:
	GameObject* m_pObject{};
	//ColorMaterial* m_pMaterial{};
	DiffuseMaterial* m_pMaterial{};
};
