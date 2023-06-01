#include "stdafx.h"
#include "ParticleEmitterComponent.h"
#include "Misc/ParticleMaterial.h"

ParticleMaterial* ParticleEmitterComponent::m_pParticleMaterial{};

ParticleEmitterComponent::ParticleEmitterComponent(const std::wstring& assetFile, const ParticleEmitterSettings& emitterSettings, UINT particleCount):
	m_ParticlesArray(new Particle[particleCount]),
	m_ParticleCount(particleCount), //How big is our particle buffer?
	m_MaxParticles(particleCount), //How many particles to draw (max == particleCount)
	m_AssetFile(assetFile),
	m_EmitterSettings(emitterSettings)
{
	m_enablePostDraw = true; //This enables the PostDraw function for the component

	//test
	m_pParticleBuffer = new VertexParticle[particleCount];
}

ParticleEmitterComponent::~ParticleEmitterComponent()
{
	//TODO_W9(L"Implement Destructor")
	delete[] m_ParticlesArray;
	delete[] m_pParticleBuffer;
	m_pVertexBuffer->Release();
}

void ParticleEmitterComponent::Initialize(const SceneContext& sceneContext)
{
	//TODO_W9(L"Implement Initialize")
	if (m_pParticleMaterial == nullptr)
	{
		m_pParticleMaterial = MaterialManager::Get()->CreateMaterial<ParticleMaterial>();
	}
	CreateVertexBuffer(sceneContext);
	m_pParticleTexture = ContentManager::Load<TextureData>(m_AssetFile);



}

void ParticleEmitterComponent::CreateVertexBuffer(const SceneContext& sceneContext)
{
	//TODO_W9(L"Implement CreateVertexBuffer")

	if (m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
	}

	D3D11_BUFFER_DESC vertBufferDesc{};
	vertBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertBufferDesc.ByteWidth = sizeof(VertexParticle) * m_ParticleCount;
	vertBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertBufferDesc.MiscFlags = 0;
	HANDLE_ERROR(sceneContext.d3dContext.pDevice->CreateBuffer(&vertBufferDesc, nullptr, &m_pVertexBuffer))



}

void ParticleEmitterComponent::Update(const SceneContext& sceneContext)
{
	//TODO_W9(L"Implement Update")



	float particleInterval = ((m_EmitterSettings.maxEnergy + m_EmitterSettings.minEnergy) / 2) / m_ParticleCount;

	m_LastParticleSpawn += sceneContext.pGameTime->GetElapsed();

	m_ActiveParticles = 0;

	D3D11_MAPPED_SUBRESOURCE subResource;
	sceneContext.d3dContext.pDeviceContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);

	//VertexParticle* pBuffer = reinterpret_cast<VertexParticle*>(subResource.pData);

	

	for (UINT i{}; i< m_ParticleCount;i++)
	{
		auto& curParticle = m_ParticlesArray[i];

		if(curParticle.isActive)
		{
			UpdateParticle(curParticle, sceneContext.pGameTime->GetElapsed());
		}

		if(!curParticle.isActive && m_LastParticleSpawn >= particleInterval)
		{
			SpawnParticle(curParticle);
		}

		m_pParticleBuffer[m_ActiveParticles] = curParticle.vertexInfo;

		if(curParticle.isActive)
		{
			//pBuffer[m_ActiveParticles] = curParticle.vertexInfo;
			//m_pParticleBuffer[m_ActiveParticles] = curParticle.vertexInfo;
			m_ActiveParticles++;
		}


	}
	memcpy(subResource.pData, m_pParticleBuffer,sizeof(VertexParticle) * m_ActiveParticles);
	sceneContext.d3dContext.pDeviceContext->Unmap(m_pVertexBuffer, 0);


}

void ParticleEmitterComponent::UpdateParticle(Particle& p, float elapsedTime) const
{
	//TODO_W9(L"Implement UpdateParticle")
	if(!p.isActive)
	{
		return;
	}

	p.currentEnergy -= elapsedTime;

	if(p.currentEnergy < 0)
	{
		p.isActive = false;
		return;
	}

	//weight
	if(p.initialWeight > 0)
	{
		p.particleVelocity.y -= p.initialWeight * elapsedTime;
	}

	p.vertexInfo.Position.x += p.particleVelocity.x * elapsedTime;
	p.vertexInfo.Position.y += p.particleVelocity.y * elapsedTime;
	p.vertexInfo.Position.z += p.particleVelocity.z * elapsedTime;

	/*p.vertexInfo.Position.x += m_EmitterSettings.velocity.x * elapsedTime;
	p.vertexInfo.Position.y += m_EmitterSettings.velocity.y * elapsedTime;
	p.vertexInfo.Position.z += m_EmitterSettings.velocity.z * elapsedTime;*/

	float lifePercent{ p.currentEnergy / p.totalEnergy };
	float delayFade{ 2.f };

	p.vertexInfo.Color = m_EmitterSettings.color;
	p.vertexInfo.Color.w *= lifePercent * delayFade;
	
	p.vertexInfo.Size = p.initialSize + p.initialSize * (p.sizeChange - 1.f) * (1.f - lifePercent);



	

}

void ParticleEmitterComponent::SpawnParticle(Particle& p)
{
	//TODO_W9(L"Implement SpawnParticle")
	p.isActive = true;

	p.currentEnergy = MathHelper::randF(m_EmitterSettings.minEnergy, m_EmitterSettings.maxEnergy);
	p.totalEnergy = MathHelper::randF(m_EmitterSettings.minEnergy, m_EmitterSettings.maxEnergy);

	
	XMVECTOR randomDirection{MathHelper::randF(-XM_PI, XM_PI),MathHelper::randF(-XM_PI, XM_PI),MathHelper::randF(-XM_PI, XM_PI)};
	float randomDistance = MathHelper::randF(m_EmitterSettings.minEmitterRadius, m_EmitterSettings.maxEmitterRadius);
	const XMVECTOR& offset{ XMVector3Normalize(randomDirection) * randomDistance };
	XMStoreFloat3(&p.vertexInfo.Position, XMLoadFloat3(&GetTransform()->GetWorldPosition()) + offset);


	p.vertexInfo.Size = MathHelper::randF(m_EmitterSettings.minSize, m_EmitterSettings.maxSize);
	p.initialSize = p.vertexInfo.Size;
	p.sizeChange = MathHelper::randF(m_EmitterSettings.minScale, m_EmitterSettings.maxScale);
	p.vertexInfo.Rotation = MathHelper::randF(-XM_PI, XM_PI);
	p.vertexInfo.Color = m_EmitterSettings.color;


	//weight
	p.particleVelocity = m_EmitterSettings.velocity;
	p.initialWeight = MathHelper::randF(m_EmitterSettings.minWeight, m_EmitterSettings.maxWeight);
	
}

void ParticleEmitterComponent::PostDraw(const SceneContext& sceneContext)
{
	//TODO_W9(L"Implement PostDraw")
	m_pParticleMaterial->SetVariable_Matrix(L"gWorldViewProj", sceneContext.pCamera->GetViewProjection());
	m_pParticleMaterial->SetVariable_Matrix(L"gViewInverse", sceneContext.pCamera->GetViewInverse());
	m_pParticleMaterial->SetVariable_Texture(L"gParticleTexture",m_pParticleTexture);

	auto techContext = m_pParticleMaterial->GetTechniqueContext();

	auto deviceContext = sceneContext.d3dContext.pDeviceContext;

	deviceContext->IASetInputLayout(techContext.pInputLayout);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	const UINT offset = 0;
	const UINT stride = sizeof(VertexParticle);
	deviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);



	D3DX11_TECHNIQUE_DESC desc{};
	techContext.pTechnique->GetDesc(&desc);
	for (UINT i = 0; i < desc.Passes; i++)
	{
		techContext.pTechnique->GetPassByIndex(i)->Apply(0, deviceContext);
		deviceContext->Draw(static_cast<UINT>(m_ActiveParticles), 0);
	}

	
}

void ParticleEmitterComponent::DrawImGui()
{
	if(ImGui::CollapsingHeader("Particle System"))
	{
		ImGui::SliderUInt("Count", &m_ParticleCount, 0, m_MaxParticles);
		ImGui::InputFloatRange("Energy Bounds", &m_EmitterSettings.minEnergy, &m_EmitterSettings.maxEnergy);
		ImGui::InputFloatRange("Size Bounds", &m_EmitterSettings.minSize, &m_EmitterSettings.maxSize);
		ImGui::InputFloatRange("Scale Bounds", &m_EmitterSettings.minScale, &m_EmitterSettings.maxScale);
		ImGui::InputFloatRange("Radius Bounds", &m_EmitterSettings.minEmitterRadius, &m_EmitterSettings.maxEmitterRadius);
		ImGui::InputFloat3("Velocity", &m_EmitterSettings.velocity.x);
		ImGui::ColorEdit4("Color", &m_EmitterSettings.color.x, ImGuiColorEditFlags_NoInputs);
	}
}