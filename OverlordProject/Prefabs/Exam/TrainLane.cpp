#include "stdafx.h"
#include "TrainLane.h"
#include "Prefabs/Exam/Train.h"

TrainLane::TrainLane(int count, int width)
{
	m_Count = count;
	m_Width = width;
}

std::vector<bool> TrainLane::GetObstacles()
{
	return m_hasObstacle;
}

void TrainLane::Initialize(const SceneContext& /*sceneContext*/)
{
	//tag
	SetTag(L"TrainLane");


	//particle
	m_ParticleSettings.velocity = { 0.f,0.f,0.f };
	m_ParticleSettings.minSize = 0.25f;
	m_ParticleSettings.maxSize = 0.25f;
	m_ParticleSettings.minEnergy = 0.1f;
	m_ParticleSettings.maxEnergy = 0.2f;
	m_ParticleSettings.minScale = 5.5f;
	m_ParticleSettings.maxScale = 5.5f;
	m_ParticleSettings.minEmitterRadius = .0f;
	m_ParticleSettings.maxEmitterRadius = .0f;
	m_ParticleSettings.minWeight = 0.f;
	m_ParticleSettings.maxWeight = 0.f;
	m_ParticleSettings.color = { 1.f,1.f,1.f, 1.f };


	m_ParticlePos = GetTransform()->GetPosition();

	/*m_pParticleSystemObject = AddChild(new GameObject);

	m_pEmitter = m_pParticleSystemObject->AddComponent(new ParticleEmitterComponent(L"Textures/Exam/Particle/redlight2.png", m_ParticleSettings, 1));
	m_pEmitter->GetTransform()->Translate(m_ParticlePos.x, m_ParticlePos.y+2.2f, m_ParticlePos.z-0.3f);*/

	//mesh
	m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(XMFLOAT4{ 0.5,0.5,0.5,1 });

	//comp1
	AddComponent(new ModelComponent(L"Meshes/TrainLane.ovm", false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);
	
	//GetTransform()->Translate(float(m_Width / 2), -2, float(1 * m_Count));
	GetTransform()->Translate(float(m_Width / 2), -1.f, float(1 * m_Count));
	//train
	//trainDelay
	m_TrainDelay = rand() % m_TrainMaxDelay + m_TrainMinDelay;

	GetScene()->AddChild(new Train(m_Width, m_Count, m_TrainDelay));

	//initalizeObstacles
	for (int i{}; i < m_Width; i++)
	{
		m_hasObstacle.push_back(false);
	}

	//comp2
	m_pMaterialRail = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	m_pMaterialRail->SetDiffuseTexture(L"Textures/Exam/RailTexture.png");

	auto model2 = AddComponent(new ModelComponent(L"Meshes/RailLong.ovm", false));

	model2->SetMaterial(m_pMaterialRail);
	auto posModel = model2->GetTransform()->GetPosition();
	model2->GetTransform()->Translate(XMFLOAT3(posModel.x, posModel.y/* + 0.5f*/, posModel.z));

	//comp3

	m_pMaterialLight = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterialLight->SetColor(XMFLOAT4{ 0.2f,0.2f,0.2f,1 });

	auto model3 = AddComponent(new ModelComponent(L"Meshes/stoplight.ovm", false));

	model3->SetMaterial(m_pMaterialLight);
	auto posModel2 = model3->GetTransform()->GetPosition();
	model3->GetTransform()->Translate(XMFLOAT3(posModel.x, posModel.y /*+ 0.5f*/, posModel.z /*- 0.5f*/));


	//sound
	SoundManager::Get()->GetSystem()->createStream("Resources/Sounds/TrainWhistle.wav", FMOD_DEFAULT, nullptr, &m_pSound);
	m_pSound->setLoopCount(1);
	//m_pSoundChannel->setVolume(0.05f);
	
	
	
}

void TrainLane::Update(const SceneContext& sceneContext)
{

	m_TrainDelayCounter += sceneContext.pGameTime->GetElapsed();
	if (m_TrainDelayCounter > m_TrainDelay - 1)
	{
		if(!m_ParticleRunning)
		{

			m_pParticleSystemObject = AddChild(new GameObject);

			m_pEmitter = m_pParticleSystemObject->AddComponent(new ParticleEmitterComponent(L"Textures/Exam/Particle/redlight2.png", m_ParticleSettings, 1));
			m_pEmitter->GetTransform()->Translate(m_ParticlePos.x, m_ParticlePos.y + 2.2f, m_ParticlePos.z - 0.3f);
			m_ParticleRunning = true;

			//sound
			//FMOD::Channel* temp{};
			SoundManager::Get()->GetSystem()->playSound(m_pSound, nullptr, false, &m_pSoundChannel);
			//SoundManager::Get()->GetSystem()->playSound(m_pSound, nullptr, false, &temp);
			//temp->setVolume(0.01f);
			m_pSoundChannel->setVolume(0.01f);
		}

		if(m_TrainDelayCounter > m_TrainDelay + 1 && m_ParticleRunning)
		{
			RemoveChild(m_pParticleSystemObject, true);
			m_TrainDelayCounter = 0.f;
			m_ParticleRunning = false;
		}
	} 


}
