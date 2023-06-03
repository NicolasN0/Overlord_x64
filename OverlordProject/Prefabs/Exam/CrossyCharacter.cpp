#include "stdafx.h"
#include "CrossyCharacter.h"
#include "Prefabs/Exam/LaneManager.h"
#include <Prefabs/Exam/Coin.h>

CrossyCharacter::CrossyCharacter(LaneManager* manager, const CrossyCharacterDesc& characterDesc)
{
	m_pLaneManager = manager;
	m_CharacterDesc = characterDesc;
}

int CrossyCharacter::GetCoins()
{
	return m_Coins;
}

void CrossyCharacter::SetCoints(int coins)
{
	m_Coins = coins;
}

int CrossyCharacter::GetScore()
{
	return m_Score;
}

bool CrossyCharacter::GetIsDead()
{
	return m_isDead;
}

void CrossyCharacter::SetMove(bool canMove)
{
	m_CanMove = canMove;
}

void CrossyCharacter::SetSplash(bool splashTriggered)
{
	m_SplashTriggered = splashTriggered;
}

bool CrossyCharacter::isSplashTriggered()
{
	return m_SplashTriggered;
}



void CrossyCharacter::Initialize(const SceneContext&)
{
	SetTag(L"Player");

	////redColor
	//m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	//m_pMaterial->SetColor(XMFLOAT4{1,0,0,1});

	////mouseDiff
	/*m_pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Skinned>();
	m_pMaterial->SetDiffuseTexture(L"Textures/Exam/CharacterDiff.png");*/
	
	//chicken2Diff
	m_pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	m_pMaterial->SetDiffuseTexture(L"Textures/Exam/Chicken2Diff.png");

	//model
	//AddComponent(new ModelComponent(L"Meshes/Chicken.ovm"));
	AddComponent(new ModelComponent(L"Meshes/Chicken2.ovm", false));
	//auto pModel = AddComponent(new ModelComponent(L"Meshes/Mouse.ovm"));

	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);


	//Controller
	
	m_pControllerComponent = AddComponent(new ControllerComponent(m_CharacterDesc.controller));
	
	
	/*auto pAnimator = pModel->GetAnimator();
	pAnimator->SetAnimation(0);
	pAnimator->SetAnimationSpeed(1.f);
	pAnimator->Play();*/


	GetTransform()->Rotate(0, 90, 0);

	//comment for characterController
	//collider
	/*PxMaterial* mat = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.5f);
	auto body = AddComponent(new RigidBodyComponent(false));
	body->SetKinematic(true);
	body->AddCollider(PxSphereGeometry(0.3f), *mat, true);*/

	//set start
	/*m_StartPos = XMFLOAT3(float(m_pLaneManager->GetWidth()/2),0,0);*/
	m_StartPos = XMFLOAT3(float(m_pLaneManager->GetWidth() / 2),0, 0);
	GetTransform()->Translate(m_StartPos);
	m_prevPos = m_StartPos;
	m_futurePos = m_StartPos;


	//SetOnTriggerCallBack([=](GameObject*, GameObject* other, PxTriggerAction action)
	//	{
	//		if (action == PxTriggerAction::ENTER)
	//		{
	//			/*if (other->GetTag() == L"Enemy") 
	//			{
	//				Dies();
	//			}*/

	//			//if (other->GetTag() == L"Coin")
	//			//{
	//			//	m_Coins++;
	//			//	
	//			//	Coin* coin = static_cast<Coin*>(other);
	//			//	coin->PickedUp(true);


	//			//	//sound
	//			//	SoundManager::Get()->GetSystem()->playSound(m_pSoundCoin, nullptr, false, &m_pSoundChannel);
	//			//	m_pSoundChannel->setVolume(0.05f);
	//			//}

	//			//if (other->GetTag() == L"Lily")
	//			//{
	//			//	
	//			//	m_SplashTriggered = true;

	//			//	
	//			//	//sound
	//			//	SoundManager::Get()->GetSystem()->playSound(m_pSoundSplash, nullptr, false, &m_pSoundChannel);
	//			//	m_pSoundChannel->setVolume(0.05f);
	//			//}
	//		}
	//		
	//	});
	
	//sound
	
	SoundManager::Get()->GetSystem()->createStream("Resources/Sounds/bounceEdited.wav", FMOD_DEFAULT, nullptr, &m_pSoundBounce);
	m_pSoundBounce->setLoopCount(1);
	SoundManager::Get()->GetSystem()->createStream("Resources/Sounds/chickenEdited.wav", FMOD_DEFAULT, nullptr, &m_pSoundChicken);
	m_pSoundChicken->setLoopCount(1);
	//SoundManager::Get()->GetSystem()->createStream("Resources/Sounds/watersplashEdited.wav", FMOD_DEFAULT, nullptr, &m_pSoundSplash);
	//SoundManager::Get()->GetSystem()->createStream("Resources/Sounds/coinEdited.wav", FMOD_DEFAULT, nullptr, &m_pSoundCoin);
	
}

void CrossyCharacter::Update(const SceneContext& sceneContext)
{
	//debug uncomment for testing
	//if(!m_CanMove)
	//{
	//	return;
	//}

	//control startup delay for dead
	CheckStartup(sceneContext);


	//sinking
	if(m_isSinking)
	{
		auto pos = GetTransform()->GetPosition();
		GetTransform()->Translate(pos.x, pos.y - sceneContext.pGameTime->GetElapsed(), pos.z);
		std::cout << GetTransform()->GetPosition().y;
		if(GetTransform()->GetPosition().y < - 2)
		{
			Dies();
		}
	}


	//move check logic
	MoveCheckLogic(sceneContext);
	MoveTimer(sceneContext);
	MoveChar(sceneContext);
	//if(!m_isMoving)
	//{
	//	//Check if is on water
	//
	//	CheckWater();
	//	//Only able to do something if not sinking
	//	if(!m_isSinking)
	//	{

	//		if (sceneContext.pInput->IsActionTriggered(MoveUp))
	//		{
	//			//set right rotation
	//			GetTransform()->Rotate(0, 90, 0);


	//			XMFLOAT3 testPos = m_futurePos;
	//			testPos.z += 1;
	//			if(m_pLaneManager->GetIsPassable(int(testPos.x),int(testPos.z)))
	//			{
	//				m_futurePos = testPos;
	//				m_isMoving = true;
	//				if(testPos.z > m_Score)
	//				{
	//					m_Score = int(testPos.z);
	//					m_pLaneManager->IncreasePlayerCount(m_Score);
	//				}
	//				//m_Score++;

	//			}


	//		}
	//		else if (sceneContext.pInput->IsActionTriggered(MoveDown))
	//		{
	//			//set right rotation
	//			GetTransform()->Rotate(0, -90, 0);

	//			XMFLOAT3 testPos = m_futurePos;
	//			testPos.z -= 1;
	//			if (m_pLaneManager->GetIsPassable(int(testPos.x), int(testPos.z)))
	//			{
	//				m_futurePos = testPos;
	//				m_isMoving = true;

	//			}
	//		}
	//		else if (sceneContext.pInput->IsActionTriggered(MoveLeft))
	//		{
	//			//set right rotation
	//			GetTransform()->Rotate(0, 0, 0);

	//			XMFLOAT3 testPos = m_futurePos;
	//			testPos.x -= 1;
	//			if (m_pLaneManager->GetIsPassable(int(testPos.x), int(testPos.z)))
	//			{
	//				m_futurePos = testPos;
	//				m_isMoving = true;

	//			}
	//		}
	//		else if (sceneContext.pInput->IsActionTriggered(MoveRight))
	//		{
	//			GetTransform()->Rotate(0, 180, 0);

	//			XMFLOAT3 testPos = m_futurePos;
	//			testPos.x += 1;
	//			if (m_pLaneManager->GetIsPassable(int(testPos.x), int(testPos.z)))
	//			{
	//				m_futurePos = testPos;
	//				m_isMoving = true;

	//			}
	//		
	//		}

	//	}
	//}

	//moving itself
	//if(m_isMoving)
	//{
	//	m_MoveTime += sceneContext.pGameTime->GetElapsed() * m_CharSpeed;
	//	if(m_MoveTime > m_MaxMoveTime)
	//	{
	//		m_isMoving = false;
	//		m_MoveTime = 0.f;

	//		m_prevPos = m_futurePos;

	//		//landed so play sounds
	//		//sound
	//		SoundManager::Get()->GetSystem()->playSound(m_pSoundBounce, nullptr, false, &m_pSoundChannel);
	//		m_pSoundChannel->setVolume(0.01f);
	//	}


	//}

	//moving itself
	/*if(!m_isSinking)
	{
		float posZ = std::lerp(static_cast<float>(m_prevPos.z), static_cast<float>(m_futurePos.z), m_MoveTime);
		float posX = std::lerp(static_cast<float>(m_prevPos.x), static_cast<float>(m_futurePos.x), m_MoveTime);

		float posY{};
		if(m_MoveTime > 0.5)
		{
			 posY = std::lerp(static_cast<float>(m_JumpHeight), 0.f, m_MoveTime);
		} else
		{
			 posY = std::lerp(0, static_cast<float>(m_JumpHeight), m_MoveTime);
		}

		GetTransform()->Translate(posX, posY, posZ);		
	}*/

}

void CrossyCharacter::CheckWater()
{
	if(m_pLaneManager->IsOnWater(int(m_prevPos.x), int(m_prevPos.z)))
	{
		if(m_isSinking != true)
		{
			std::cout << "Sink";
			m_isSinking = true;
		}

	}

}

void CrossyCharacter::MoveCheckLogic(const SceneContext& sceneContext)
{
	if (!m_isMoving)
	{
		//Check if is on water

		CheckWater();
		//Only able to do something if not sinking
		if (!m_isSinking)
		{

			//if (sceneContext.pInput->IsActionTriggered(MoveUp))
			if (sceneContext.pInput->IsActionTriggered((int)m_CharacterDesc.actionId_MoveForward))
			{
				//set right rotation
				GetTransform()->Rotate(0, 90, 0);


				XMFLOAT3 testPos = m_futurePos;
				testPos.z += 1;
				if (m_pLaneManager->GetIsPassable(int(testPos.x), int(testPos.z)))
				{
					m_futurePos = testPos;
					m_isMoving = true;
					if (testPos.z > m_Score)
					{
						m_Score = int(testPos.z);
						m_pLaneManager->IncreasePlayerCount(m_Score);
					}
					//m_Score++;

				}


			}
			else if (sceneContext.pInput->IsActionTriggered((int)m_CharacterDesc.actionId_MoveBackward))
			//else if (sceneContext.pInput->IsActionTriggered(MoveDown))
			{
				//set right rotation
				GetTransform()->Rotate(0, -90, 0);

				XMFLOAT3 testPos = m_futurePos;
				testPos.z -= 1;
				if (m_pLaneManager->GetIsPassable(int(testPos.x), int(testPos.z)))
				{
					m_futurePos = testPos;
					m_isMoving = true;

				}
			}
			else if (sceneContext.pInput->IsActionTriggered((int)m_CharacterDesc.actionId_MoveLeft))
			//else if (sceneContext.pInput->IsActionTriggered(MoveLeft))
			{
				//set right rotation
				GetTransform()->Rotate(0, 0, 0);

				XMFLOAT3 testPos = m_futurePos;
				testPos.x -= 1;
				if (m_pLaneManager->GetIsPassable(int(testPos.x), int(testPos.z)))
				{
					m_futurePos = testPos;
					m_isMoving = true;

				}
			}
			else if (sceneContext.pInput->IsActionTriggered((int)m_CharacterDesc.actionId_MoveRight))
			//else if (sceneContext.pInput->IsActionTriggered(MoveRight))
			{
				GetTransform()->Rotate(0, 180, 0);

				XMFLOAT3 testPos = m_futurePos;
				testPos.x += 1;
				if (m_pLaneManager->GetIsPassable(int(testPos.x), int(testPos.z)))
				{
					m_futurePos = testPos;
					m_isMoving = true;

				}

			}

		}
	}
}

void CrossyCharacter::MoveTimer(const SceneContext& sceneContext)
{
	if (m_isMoving)
	{
		m_MoveTime += sceneContext.pGameTime->GetElapsed() * m_CharSpeed;
		if (m_MoveTime > m_MaxMoveTime)
		{
			m_isMoving = false;
			m_MoveTime = 0.f;

			m_prevPos = m_futurePos;

			//landed so play sounds
			//sound
			SoundManager::Get()->GetSystem()->playSound(m_pSoundBounce, nullptr, false, &m_pSoundChannel);
			m_pSoundChannel->setVolume(0.01f);
		}


	}
}

void CrossyCharacter::MoveChar(const SceneContext& /*sceneContext*/)
{
	if (!m_isSinking)
	{
		float posZ = std::lerp(static_cast<float>(m_prevPos.z), static_cast<float>(m_futurePos.z), m_MoveTime);
		float posX = std::lerp(static_cast<float>(m_prevPos.x), static_cast<float>(m_futurePos.x), m_MoveTime);

		float posY{};
		if (m_MoveTime > 0.5)
		{
			posY = std::lerp(static_cast<float>(m_JumpHeight), 0.f, m_MoveTime);
		}
		else
		{
			posY = std::lerp(0, static_cast<float>(m_JumpHeight), m_MoveTime);
		}

		//GetTransform()->Translate(posX, posY, posZ);
		m_pControllerComponent->Translate(XMFLOAT3(posX, posY, posZ));
	}
}

void CrossyCharacter::Dies()
{
	if(m_isStartupDone)
	{
		m_isDead = true;
		std::cout << "dead";
	}

}

void CrossyCharacter::IncreaseCoins()
{
	m_Coins++;
}

void CrossyCharacter::CheckStartup(const SceneContext& sceneContext)
{
	if(!m_isStartupDone)
	{
		m_curStartupTime += sceneContext.pGameTime->GetElapsed();
		if(m_curStartupTime > m_maxStartupTime)
		{
			m_isStartupDone = true;
		}
	}
}
