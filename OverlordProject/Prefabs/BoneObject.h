#pragma once
//#include "C:\DAE\JAAR2P2\GP2\OverlordEngine_x64_Start\OverlordEngine\Scenegraph\GameObject.h"
#include "Scenegraph/GameObject.h"
class BaseMaterial;

class BoneObject :
    public GameObject
{
public:
	BoneObject(BaseMaterial* pMaterial, float length = 5.f);
	~BoneObject() override = default;

	BoneObject(const BoneObject& other) = delete;
	BoneObject(BoneObject&& other) noexcept = delete;
	BoneObject& operator=(const BoneObject& other) = delete;
	BoneObject& operator=(BoneObject&& other) noexcept = delete;

	void AddBone(BoneObject* pBone);

	//PART 2
	const XMFLOAT4X4& GetBindPose() const { return m_BindPose; }
	void CalculateBindPose();
protected:
	void Initialize(const SceneContext & sceneContext) override;

private:
	float m_Length;
	BaseMaterial* m_pMaterial;

	//PART2
	XMFLOAT4X4 m_BindPose;
};

