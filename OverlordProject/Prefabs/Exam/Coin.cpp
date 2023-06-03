#include "stdafx.h"
#include "Coin.h"
#include <Prefabs\Exam\CrossyCharacter.h>

Coin::Coin(int posX, int posZ,RoadLane* lane)
{
	m_PosX = posX;
	m_PosZ = posZ;

	m_pLane = lane;
}

void Coin::PickedUp(bool picked)
{
	m_PickedUp = picked;
}

void Coin::Initialize(const SceneContext& /*sceneContext*/)
{
	SetTag(L"Coin");


	m_pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	m_pMaterial->SetDiffuseTexture(L"Textures/Exam/Coin.png");

	AddComponent(new ModelComponent(L"Meshes/Coin.ovm", false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	GetTransform()->Translate(float(m_PosX), 0, float(m_PosZ));
	//Collider
	auto material = PxGetPhysics().createMaterial(.5f, .5f, .1f);
	AddComponent(new RigidBodyComponent(false));
	GetComponent<RigidBodyComponent>()->AddCollider(PxBoxGeometry{ 0.3f,0.3f,0.3f }, *material,true);
	GetComponent<RigidBodyComponent>()->SetKinematic(true);

	SetOnTriggerCallBack([=](GameObject*, GameObject* other, PxTriggerAction action)
		{
			if (action == PxTriggerAction::ENTER)
			{
				if (other->GetTag() == L"Player")
				{
					
					CrossyCharacter* character = static_cast<CrossyCharacter*>(other);

					character->IncreaseCoins();

					PickedUp(true);

					//sound
					SoundManager::Get()->GetSystem()->playSound(m_pSoundCoin, nullptr, false, &m_pSoundChannel);
					m_pSoundChannel->setVolume(0.05f);
				}


			}

		});

	SoundManager::Get()->GetSystem()->createStream("Resources/Sounds/coinEdited.wav", FMOD_DEFAULT, nullptr, &m_pSoundCoin);
	
}

void Coin::Update(const SceneContext& /*sceneContext*/)
{
	if(m_PickedUp)
	{
		m_pLane->RemoveCoin(this);
		GetScene()->RemoveChild(this, true);
	}
}
