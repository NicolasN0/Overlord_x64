#pragma once
#include "C:\DAE\JAAR2P2\GP2\OverlordEngine_x64_Start\OverlordEngine\Scenegraph\GameScene.h"
#include <Prefabs/BoneObject.h>
class SoftwareSkinningScene_3 :
	public GameScene
{
public:
	SoftwareSkinningScene_3() :GameScene(L"SoftwareSkinningScene_3") {}
	~SoftwareSkinningScene_3() override = default;

	SoftwareSkinningScene_3(const SoftwareSkinningScene_3& other) = delete;
	SoftwareSkinningScene_3(SoftwareSkinningScene_3&& other) noexcept = delete;
	SoftwareSkinningScene_3& operator=(const SoftwareSkinningScene_3& other) = delete;
	SoftwareSkinningScene_3& operator=(SoftwareSkinningScene_3&& other) noexcept = delete;

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
	bool m_AutoRotate{ true };

	//PART2
	struct VertexSoftwareSkinned
	{
		VertexSoftwareSkinned(XMFLOAT3 position, XMFLOAT3 normal, XMFLOAT4 color,float weight0, float weigth1) :
			transformedVertex{ position,normal,color },
			originalVertex{ position,normal,color },
			blendWeigth0{ weight0 },
			blendWeight1{ weigth1 }{}

		VertexPosNormCol transformedVertex{};
		VertexPosNormCol originalVertex{};
		float blendWeigth0;
		float blendWeight1;
	};

	void InitializeVertices(float length);

	MeshDrawComponent* m_pMeshDrawer{};
	std::vector<VertexSoftwareSkinned> m_SkinnedVertices;
};
