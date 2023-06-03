#pragma once
//#include "C:\DAE\JAAR2P2\GP2\OverlordEngine_x64_Start\OverlordEngine\Scenegraph\GameObject.h"
#include "Scenegraph/GameObject.h"
#include <Materials/ColorMaterial.h>
#include <Materials/DiffuseMaterial.h>
class Lily :
    public GameObject
{
public:
	Lily(int posX, int posZ);
	~Lily() override = default;

	Lily(const Lily& other) = delete;
	Lily(Lily&& other) noexcept = delete;
	Lily& operator=(const Lily& other) = delete;
	Lily& operator=(Lily&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext & sceneContext) override;
	void Update(const SceneContext&) override;

private:
	DiffuseMaterial* m_pMaterial{};
	int m_PosX{};
	int m_PosZ{};


	FMOD::Sound* m_pSoundSplash{};
	FMOD::Channel* m_pSoundChannel{};
};

