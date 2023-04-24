#include "stdafx.h"
#include "CrossyCharacter.h"


CrossyCharacter::CrossyCharacter()
{
}

void CrossyCharacter::Initialize(const SceneContext&)
{
	
	m_pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	m_pMaterial->SetColor(XMFLOAT4{1,0,0,1});

	AddComponent(new ModelComponent(L"Meshes/Sphere.ovm"));
	
	GetComponent<ModelComponent>()->SetMaterial(m_pMaterial);

	PxMaterial* mat = PxGetPhysics().createMaterial(0.f, 0.f, 0.f);

	auto body = AddComponent(new RigidBodyComponent(false));
	body->SetKinematic(true);
	body->AddCollider(PxSphereGeometry(1.0f), *mat, true);
}

void CrossyCharacter::Update(const SceneContext& sceneContext)
{
	if(!m_isMoving)
	{

		if (sceneContext.pInput->IsActionTriggered(MoveUp))
		{
			m_futurePos.z += 1;
			m_isMoving = true;
		}
		else if (sceneContext.pInput->IsActionTriggered(MoveDown))
		{
			m_futurePos.z -= 1;
			m_isMoving = true;
		}
		else if (sceneContext.pInput->IsActionTriggered(MoveLeft))
		{
			m_futurePos.x -= 1;
			m_isMoving = true;
		}
		else if (sceneContext.pInput->IsActionTriggered(MoveRight))
		{
			m_futurePos.x += 1;
			m_isMoving = true;
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

		float posZ = std::lerp(static_cast<float>(m_prevPos.z), static_cast<float>(m_futurePos.z), m_MoveTime);
		float posX = std::lerp(static_cast<float>(m_prevPos.x), static_cast<float>(m_futurePos.x), m_MoveTime);
		GetTransform()->Translate(posX, 0, posZ);

	}

	std::cout << GetTransform()->GetPosition().x << " " << GetTransform()->GetPosition().y << " " << GetTransform()->GetPosition().z << std::endl;
}
