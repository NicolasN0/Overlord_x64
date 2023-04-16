#include "stdafx.h"
#include "UberMaterial.h"

UberMaterial::UberMaterial() :
	Material<UberMaterial>(L"Effects/UberShader.fx")
{
}

void UberMaterial::InitializeEffectVariables()
{

	SetVariable_Texture(L"gTextureDiffuse", ContentManager::Load<TextureData>(L"Textures/Skulls Textures/Skulls_Diffusemap.tga"));
	SetVariable_Vector(L"gColorDiffuse", XMFLOAT4{ 1,0,0,1 });
	SetVariable_Scalar(L"gUseTextureDiffuse", true);
	SetVariable_Scalar(L"gAmbientIntensity", 0.2f);
	SetVariable_Vector(L"gColorAmbient", XMFLOAT4{ 0.25f, 0.25f, 0.25f, 1.f });

	SetVariable_Texture(L"gTextureNormal", ContentManager::Load<TextureData>(L"Textures/Skulls Textures/Skulls_Normalmap.tga"));
	SetVariable_Scalar(L"gFlipGreenChannel", true);
	SetVariable_Scalar(L"gUseTextureNormal", true);

	SetVariable_Vector(L"gColorSpecular", XMFLOAT4{ 0,1.f, 0.5f, 1.f });
	SetVariable_Scalar(L"gUseTextureSpecularIntensity", true);
	SetVariable_Scalar(L"gUseSpecularPhong", true);
	SetVariable_Scalar(L"gUseSpecularBlinn", false);
	SetVariable_Texture(L"gTextureSpecularIntensity", ContentManager::Load<TextureData>(L"Textures/Skulls Textures/Skulls_Heightmap.tga"));
	SetVariable_Scalar(L"gShininess", 40);


	SetVariable_Texture(L"gCubeEnvironment", ContentManager::Load<TextureData>(L"Textures/Sunol_Cubemap.dds"));
	SetVariable_Scalar(L"gUseEnvironmentMapping", true);
	SetVariable_Scalar(L"gReflectionStrength", 0.4f);
	SetVariable_Scalar(L"gRefractionStrength", 0.5f);
	SetVariable_Scalar(L"gRefractionIndex", 0.7f);
	

	SetVariable_Scalar(L"gUseFresnelFalloff", true);
	SetVariable_Vector(L"gColorFresnel", XMFLOAT4{ 1.f, 1.f, 1.f, 1.f });
	SetVariable_Scalar(L"gFresnelPower", 2.f);
	SetVariable_Scalar(L"gFresnelMultiplier", 1.5f);
	SetVariable_Scalar(L"gFresnelHardness", 1.5f);





}
