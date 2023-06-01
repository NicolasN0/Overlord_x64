#pragma once
#include "Scenegraph/GameObject.h"
#include <Materials/ColorMaterial.h>
#include <Materials/DiffuseMaterial.h>
class TrainLane :
    public GameObject
{
public:
	TrainLane(int count, int width);
	~TrainLane() override = default;

	TrainLane(const TrainLane& other) = delete;
	TrainLane(TrainLane&& other) noexcept = delete;
	TrainLane& operator=(const TrainLane& other) = delete;
	TrainLane& operator=(TrainLane&& other) noexcept = delete;

	std::vector<bool> GetObstacles();

protected:
	void Initialize(const SceneContext & sceneContext) override;
	void Update(const SceneContext & sceneContext) override;
	void OnSceneDetach(GameScene* /*pScene*/) override;

private:
	XMFLOAT4 m_Color{};
	ColorMaterial* m_pMaterial{};
	DiffuseMaterial* m_pMaterialRail{};
	ColorMaterial* m_pMaterialLight{};
	int m_Count{};
	std::vector<GameObject*> m_pObstacles{};
	std::vector<bool> m_hasObstacle{};
	int m_Width{};


	//train
	GameObject* m_pTrain{};
	int m_TrainMaxDelay{5};
	int m_TrainMinDelay{3};
	int m_TrainDelay{};
	float m_TrainDelayCounter{};

	//particle
	XMFLOAT3 m_ParticlePos{};
	ParticleEmitterComponent* m_pEmitter{};
	ParticleEmitterSettings m_ParticleSettings{};
	GameObject* m_pParticleSystemObject;
	bool m_ParticleRunning{};

	//sound
	FMOD::Sound* m_pSound{};
	FMOD::Channel* m_pSoundChannel{};
};

