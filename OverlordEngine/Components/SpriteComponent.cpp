#include "stdafx.h"
#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(const std::wstring& spriteAsset, const XMFLOAT2& pivot, const XMFLOAT4& color):
	m_SpriteAsset(spriteAsset),
	m_Pivot(pivot),
	m_Color(color)
{}

void SpriteComponent::Initialize(const SceneContext& /*sceneContext*/)
{
	m_pTexture = ContentManager::Load<TextureData>(m_SpriteAsset);
}

void SpriteComponent::SetTexture(const std::wstring& spriteAsset)
{
	m_SpriteAsset = spriteAsset;
	m_pTexture = ContentManager::Load<TextureData>(m_SpriteAsset);
}

void SpriteComponent::Draw(const SceneContext& sceneContext)
{
    if (!m_pTexture)
        return;

    //Here you need to draw the SpriteComponent using the Draw of the sprite renderer
    // The sprite renderer is a singleton
    auto worldpos{ m_pGameObject->GetTransform()->GetWorldPosition() };
    // you will need to position (X&Y should be in screenspace, Z contains the depth between [0,1]), the rotation and the scale from the owning GameObject
    auto pos{ m_pGameObject->GetTransform()->GetPosition() };
    // You can use the MathHelper::QuaternionToEuler function to help you with the z rotation 
    auto rot{ MathHelper::QuaternionToEuler(m_pGameObject->GetTransform()->GetRotation()) };
    SpriteRenderer::Get()->AppendSprite(m_pTexture, XMFLOAT2{ worldpos.x, worldpos.y }, GetColor(), GetPivot(), XMFLOAT2{ 1,1 }, rot.z, pos.z);
    SpriteRenderer::Get()->Draw(sceneContext);
}
