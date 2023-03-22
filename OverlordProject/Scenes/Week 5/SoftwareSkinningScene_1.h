#pragma once
#include "C:\DAE\JAAR2P2\GP2\OverlordEngine_x64_Start\OverlordEngine\Scenegraph\GameScene.h"
#include <Prefabs/BoneObject.h>
class SoftwareSkinningScene_1 :
    public GameScene
{
public:
	SoftwareSkinningScene_1() :GameScene(L"SoftwareSkinningScene_1") {}
	~SoftwareSkinningScene_1() override = default;

	SoftwareSkinningScene_1(const SoftwareSkinningScene_1& other) = delete;
	SoftwareSkinningScene_1(SoftwareSkinningScene_1&& other) noexcept = delete;
	SoftwareSkinningScene_1& operator=(const SoftwareSkinningScene_1& other) = delete;
	SoftwareSkinningScene_1& operator=(SoftwareSkinningScene_1&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void OnGUI() override;

private:
	BoneObject* m_pBone0{}, * m_pBone1{};

	float m_BoneRotation{};
	float m_BoneRot1{};
	float m_BoneRot2{};
	int m_RotationSign{ 1 };
	bool m_AutoRotate{true};
};
