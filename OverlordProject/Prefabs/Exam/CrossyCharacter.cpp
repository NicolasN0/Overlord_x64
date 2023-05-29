#include "stdafx.h"
#include "CrossyCharacter.h"
#include "Prefabs/Exam/LaneManager.h"
#include <Prefabs/Exam/Coin.h>

CrossyCharacter::CrossyCharacter(LaneManager* manager)
{
	m_pLaneManager = manager;
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
	

	
	m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(XMFLOAT4{1,0,0,1});

	//model
	AddComponent(new ModelComponent(L"Meshes/Chicken.ovm"));
	
	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	PxMaterial* mat = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.5f);

	GetTransform()->Rotate(0, 90, 0);
	//collider
	auto body = AddComponent(new RigidBodyComponent(false));
	body->SetKinematic(true);
	body->AddCollider(PxSphereGeometry(0.3f), *mat, true);

	//set start
	m_StartPos = XMFLOAT3(float(m_pLaneManager->GetWidth()/2),0,0);
	GetTransform()->Translate(m_StartPos);
	m_prevPos = m_StartPos;
	m_futurePos = m_StartPos;


	SetOnTriggerCallBack([=](GameObject*, GameObject* other, PxTriggerAction action)
		{
			if (action == PxTriggerAction::ENTER)
			{
				if (other->GetTag() == L"Enemy") 
				{
					Dies();
				}

				if (other->GetTag() == L"Coin")
				{
					m_Coins++;
					
					//GetScene()->RemoveChild(other, true);
					Coin* coin = static_cast<Coin*>(other);
					coin->PickedUp(true);
				}

				if (other->GetTag() == L"Lily")
				{
					
					m_SplashTriggered = true;
				}
			}
			
		});
	
}

void CrossyCharacter::Update(const SceneContext& sceneContext)
{
	//debug
	if(!m_CanMove)
	{
		return;
	}

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
	if(!m_isMoving)
	{
		//Check if is on water
	
		CheckWater();
		//Only able to do something if not sinking
		if(!m_isSinking)
		{

			if (sceneContext.pInput->IsActionTriggered(MoveUp))
			{
				XMFLOAT3 testPos = m_futurePos;
				testPos.z += 1;
				if(m_pLaneManager->GetIsPassable(int(testPos.x),int(testPos.z)))
				{
					m_futurePos = testPos;
					m_isMoving = true;
					m_Score++;

				}

				m_pLaneManager->IncreasePlayerCount();

			}
			else if (sceneContext.pInput->IsActionTriggered(MoveDown))
			{

				XMFLOAT3 testPos = m_futurePos;
				testPos.z -= 1;
				if (m_pLaneManager->GetIsPassable(int(testPos.x), int(testPos.z)))
				{
					m_futurePos = testPos;
					m_isMoving = true;

				}
			}
			else if (sceneContext.pInput->IsActionTriggered(MoveLeft))
			{

				XMFLOAT3 testPos = m_futurePos;
				testPos.x -= 1;
				if (m_pLaneManager->GetIsPassable(int(testPos.x), int(testPos.z)))
				{
					m_futurePos = testPos;
					m_isMoving = true;

				}
			}
			else if (sceneContext.pInput->IsActionTriggered(MoveRight))
			{

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

	//moving itself
	if(m_isMoving)
	{
		m_MoveTime += sceneContext.pGameTime->GetElapsed() * m_CharSpeed;
		if(m_MoveTime > m_MaxMoveTime)
		{
			m_isMoving = false;
			m_MoveTime = 0.f;

			m_prevPos = m_futurePos;
		}


	}

	//moving itself
	if(!m_isSinking)
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

		//GetTransform()->Translate(posX, 0, posZ);
		GetTransform()->Translate(posX, posY, posZ);
	}

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

void CrossyCharacter::Dies()
{
	if(m_isStartupDone)
	{

		m_isDead = true;
		std::cout << "dead";
	}

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
