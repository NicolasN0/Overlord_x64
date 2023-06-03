//=============================================================================
//// Shader uses position and texture
//=============================================================================
SamplerState samPoint
{
    Filter = MIN_MAG_MIP_POINT;
    AddressU = Mirror;
    AddressV = Mirror;
};

Texture2D gTexture;

/// Create Depth Stencil State (ENABLE DEPTH WRITING)
DepthStencilState depthState
{
    DepthEnable = TRUE;
    DepthWriteMask = ALL;
};
/// Create Rasterizer State (Backface culling) 
RasterizerState rasterState
{
    CullMode = BACK;
};

BlendState EnableBlending
{
    BlendEnable[0] = TRUE;
    SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;
};

//IN/OUT STRUCTS
//--------------
struct VS_INPUT
{
    float3 Position : POSITION;
	float2 TexCoord : TEXCOORD0;

};

struct PS_INPUT
{
    float4 Position : SV_POSITION;
	float2 TexCoord : TEXCOORD1;
};


//VERTEX SHADER
//-------------
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;
	// Set the Position
    output.Position = float4(input.Position, 1.f);
	// Set the TexCoord
    output.TexCoord = input.TexCoord;
	return output;
}


//PIXEL SHADER
//------------
float4 PS(PS_INPUT input): SV_Target
{

    //type1
    //float4 color = float4(0, 0, 0, 1);
    ////float2 dist = input.TexCoord - 0.5f;
    //float2 dist = input.TexCoord * 2.0 - 1.0;
    //dist.x = 1 - dot(dist, dist);
    ////color.a *= 1.0f - saturate(pow(dist.x, 5.5f));
    //color.a *= 1.0f - saturate(pow(dist.x, 1.5f));
    //return color;
    
    
    //type2
    float2 uv = input.TexCoord;
    uv *= 1.0 - uv.yx;
    float vig = uv.x * uv.y * 15.0; // multiply with sth for intensity   
    vig = pow(vig, 0.25); // change pow for modifying the extend of the  vignette    
    float4 color = float4(0, 0, 0, 1 - vig);
    return color;
}




//TECHNIQUE
//---------
technique11 Grayscale
{
    pass P0
    {          
        // Set states...
        SetRasterizerState(rasterState);
        SetBlendState(EnableBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
        SetDepthStencilState(depthState, 0);
		SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}

