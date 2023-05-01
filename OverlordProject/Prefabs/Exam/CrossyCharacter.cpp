#include "stdafx.h"
#include "CrossyCharacter.h"
#include "Prefabs/Exam/LaneManager.h"

CrossyCharacter::CrossyCharacter(LaneManager* manager)
{
	m_pLaneManager = manager;
}

void CrossyCharacter::Initialize(const SceneContext&)
{
	
	m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(XMFLOAT4{1,0,0,1});

	AddComponent(new ModelComponent(L"Meshes/Chicken.ovm"));
	
	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	PxMaterial* mat = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.5f);

	auto body = AddComponent(new RigidBodyComponent(false));
	body->SetKinematic(true);
	body->AddCollider(PxSphereGeometry(1.0f), *mat, true);

	//set start
	m_StartPos = XMFLOAT3(float(m_pLaneManager->GetWidth()/2),0,0);
	GetTransform()->Translate(m_StartPos);
	m_prevPos = m_StartPos;
	m_futurePos = m_StartPos;
}

void CrossyCharacter::Update(const SceneContext& sceneContext)
{
	if(!m_isMoving)
	{

		if (sceneContext.pInput->IsActionTriggered(MoveUp))
		{
			XMFLOAT3 testPos = m_futurePos;
			testPos.z += 1;
			if(m_pLaneManager->GetIsPassable(int(testPos.x),int(testPos.z)))
			{
				m_futurePos = testPos;
				//m_futurePos.z += 1;
				m_isMoving = true;

			}

			m_pLaneManager->IncreasePlayerCount();

		}
		else if (sceneContext.pInput->IsActionTriggered(MoveDown))
		{
			/*m_futurePos.z -= 1;
			m_isMoving = true;*/

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
			/*m_futurePos.x -= 1;
			m_isMoving = true;*/

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
			/*m_futurePos.x += 1;
			m_isMoving = true;*/

			XMFLOAT3 testPos = m_futurePos;
			testPos.x += 1;
			if (m_pLaneManager->GetIsPassable(int(testPos.x), int(testPos.z)))
			{
				m_futurePos = testPos;
				m_isMoving = true;

			}
			
		}
	}

	if(m_isMoving)
	{
		m_MoveTime += sceneContext.pGameTime->GetElapsed();
		if(m_MoveTime > m_MaxMoveTime)
		{
			m_isMoving = false;
			m_MoveTime = 0.f;

			m_prevPos = m_futurePos;
		}


	}
		float posZ = std::lerp(static_cast<float>(m_prevPos.z), static_cast<float>(m_futurePos.z), m_MoveTime);
		float posX = std::lerp(static_cast<float>(m_prevPos.x), static_cast<float>(m_futurePos.x), m_MoveTime);
		GetTransform()->Translate(posX, 0, posZ);

	//std::cout << GetTransform()->GetPosition().x << " " << GetTransform()->GetPosition().y << " " << GetTransform()->GetPosition().z << std::endl;
}
