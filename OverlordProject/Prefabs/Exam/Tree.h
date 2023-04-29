#pragma once
#include "C:\DAE\JAAR2P2\GP2\OverlordEngine_x64_Start\OverlordEngine\Scenegraph\GameObject.h"
#include <Materials/ColorMaterial.h>
class Tree :
    public GameObject
{
public:
	Tree(int posX,int posZ);
	~Tree() override = default;

	Tree(const Tree& other) = delete;
	Tree(Tree&& other) noexcept = delete;
	Tree& operator=(const Tree& other) = delete;
	Tree& operator=(Tree&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext & sceneContext) override;
	void Update(const SceneContext&) override;

private:
	ColorMaterial* m_pMaterial{};
	int m_PosX{};
	int m_PosZ{};
};

