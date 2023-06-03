#include "stdafx.h"
#include "Lily.h"
#include <Prefabs\Exam\CrossyCharacter.h>

Lily::Lily(int posX, int posZ)
{
	m_PosX = posX;
	m_PosZ = posZ;
}

void Lily::Initialize(const SceneContext& /*sceneContext*/)
{
	SetTag(L"Lily");
	/*m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(XMFLOAT4{ 0,1,0,1 });*/
	m_pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	m_pMaterial->SetDiffuseTexture(L"Textures/Exam/lilypad.png");


	AddComponent(new ModelComponent(L"Meshes/LilyPad.ovm", false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	
	GetTransform()->Translate(float(m_PosX), -0.5, float(m_PosZ));
	//GetTransform()->Translate(float(m_PosX),-1.5f, float(m_PosZ));


	//Collider
	auto material = PxGetPhysics().createMaterial(.5f, .5f, .1f);
	AddComponent(new RigidBodyComponent(false));
	//GetComponent<RigidBodyComponent>()->AddCollider(PxBoxGeometry{ 0.3f,0.3f,0.3f }, *material,true);
	GetComponent<RigidBodyComponent>()->AddCollider(PxBoxGeometry{ 0.1f,0.1f,0.1f }, *material, true);

	GetComponent<RigidBodyComponent>()->SetKinematic(true);


	SetOnTriggerCallBack([=](GameObject*, GameObject* other, PxTriggerAction action)
		{
			if (action == PxTriggerAction::ENTER)
			{
				if (other->GetTag() == L"Player")
				{

					CrossyCharacter* character = static_cast<CrossyCharacter*>(other);

					character->SetSplash(true);

					//m_SplashTriggered = true;


					//sound
					SoundManager::Get()->GetSystem()->playSound(m_pSoundSplash, nullptr, false, &m_pSoundChannel);
					m_pSoundChannel->setVolume(0.05f);
				}


			}

		});

	SoundManager::Get()->GetSystem()->createStream("Resources/Sounds/watersplashEdited.wav", FMOD_DEFAULT, nullptr, &m_pSoundSplash);
}

void Lily::Update(const SceneContext&)
{
}
