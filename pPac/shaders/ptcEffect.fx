//--------------------------------------------------------------------------------------
// meshEffect.fx
//
//--------------------------------------------------------------------------------------

matrix World;
matrix View;
matrix Projection;

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
	float2 TextCoord : TEXTCOORD;
};

Texture2D   TEXTURE;

/*
SamplerState linearSampler 
{
	Filter = MIN_MAG_MIP_LINEAR; 
	AddressU = Wrap;
	AddressV = Wrap;
};*/

cbuffer cbFrame
{

};

//-----------------------------------------------------------------------------------------
// State Structures
//-----------------------------------------------------------------------------------------

// There was a hole here, it's gone now

BlendState Blend
{
	BlendEnable[0] = TRUE;
	SrcBlend = SRC_ALPHA;
	DestBlend = ONE;
	BlendOp = ADD;
	SrcBlendAlpha = ONE;
	DestBlendAlpha = ZERO;
	BlendOpAlpha = ADD;
	RenderTargetWriteMask[0]= 0x0F;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( float3 Pos : POSITION, float2 textCoord : TEXTCOORD, float4 Color : COLOR )
{
	PS_INPUT psInput = (PS_INPUT)0;

	float4 mPos = float4(Pos, 1.0);
	mPos = mul( mPos, World );
    mPos = mul( mPos, View );    
    psInput.Pos = mul( mPos, Projection );

	psInput.TextCoord = textCoord;

	psInput.Color = Color;

    return psInput;  
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( PS_INPUT psInput ) : SV_Target
{
	//float4 Kd = TEXTURE.Sample(linearSampler, psInput.TextCoord);
	float4 intensity = 1.0;
	float4 L = psInput.Color * intensity;
	
	//L = L * Kd;

	//return Kd;
	return psInput.Color;
}

//--------------------------------------------------------------------------------------
technique10 PosTexColRender
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );

	   //SetDepthStencilState( EnableDepth, 0 );
	   //SetBlendState( Blend, float4(0.9f,0.9f,0.9f,0), 0xFFFFFFFF);
    }
}