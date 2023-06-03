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
    float3 color;
    // Step 1: sample the texture
    color = gTexture.Sample(samPoint, input.TexCoord);
	// Step 2: calculate the mean value
 //   float mean = (color.r + color.g + color.b) / 3;
	//// Step 3: return the color
 //   return float4(mean, mean, mean, 1.f);
    //return float4( 0.0f, 0.0f, 0.0f, 1.0f );
    
    //float rOffset = 0.009;
    //float gOffset = 0.006;
    //float bOffset = -0.006;
    
    float rOffset = 0.004;
    float gOffset = 0.002;
    float bOffset = 0.002;
    
    int width;
    int height;
    //vec2 texSize = textureSize(color, 0).xy;
    gTexture.GetDimensions(width,height);
    float2 texSize = (width, height);
    
    //vec2 texCoord = gl_FragCoord.xy / texSize;
    //float2 texCoord = input.TexCoord.xy / texSize;
    
    
   // vec2 direction = texCoord - mouseFocusPoint;
    float2 direction = input.TexCoord - float2(width / 2, height / 2);
    
    float4 newColor = float4(0,0,0,1);
    newColor.r = gTexture.Sample(samPoint, input.TexCoord - rOffset).r;
    newColor.g = gTexture.Sample(samPoint, input.TexCoord - gOffset).g;
    newColor.b = gTexture.Sample(samPoint, input.TexCoord - bOffset).b;
    
    return newColor;
  
}


//TECHNIQUE
//---------
technique11 ChromaticAberration
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

