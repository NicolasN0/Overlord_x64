#include "stdafx.h"
#include "Train.h"
#include <Prefabs\Exam\CrossyCharacter.h>

Train::Train(int posX, int posZ, int trainDelay)
{
	m_Width = posX;
	m_PosZ = posZ;
	m_CurX = 0;

	m_TrainDelay = trainDelay;
}

void Train::Initialize(const SceneContext& /*sceneContext*/)
{
	//Set Tag
	SetTag(L"Enemy");

	//Material and Model
	/*m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(XMFLOAT4{ 1,0,1,1 });*/
	m_pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	m_pMaterial->SetDiffuseTexture(L"Textures/Exam/train.png");

	AddComponent(new ModelComponent(L"Meshes/Train.ovm", false));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	//Collider
	auto material = PxGetPhysics().createMaterial(.5f, .5f, .1f);
	AddComponent(new RigidBodyComponent(false));
	GetComponent<RigidBodyComponent>()->AddCollider(PxBoxGeometry{ 15.f,1.0f,0.5f }, *material,true);
	GetComponent<RigidBodyComponent>()->SetKinematic(true);


	SetOnTriggerCallBack([=](GameObject*, GameObject* other, PxTriggerAction action)
		{
			if (action == PxTriggerAction::ENTER)
			{
				if (other->GetTag() == L"Player")
				{
					CrossyCharacter* character = static_cast<CrossyCharacter*>(other);

					character->Dies();
				}


			}

		});


	/*auto colliderInfo = GetComponent<RigidBodyComponent>()->GetCollider(0);
	GetTransform()->Rotate(0, 90, 0);
	colliderInfo.SetTrigger(true);*/


	GetTransform()->Translate(0, 0, float(m_PosZ));

	//Set Train Spawn Delay
	/*m_TrainDelay = rand() % m_TrainMaxDelay + m_TrainMinDelay;*/
	
}

void Train::Update(const SceneContext& sceneContext)
{
	m_CurX += m_CarSpeed * sceneContext.pGameTime->GetElapsed();
	GetTransform()->Translate(m_CurX, 0, float(m_PosZ));
	if (m_CurX > m_Width * 2)
	{
		//m_CurX = 0;
		m_TrainDelayCounter += sceneContext.pGameTime->GetElapsed();
		if(m_TrainDelayCounter > m_TrainDelay)
		{
			m_CurX = float(-m_Width) ;
			m_TrainDelayCounter = 0.f;
		}
	}
}
