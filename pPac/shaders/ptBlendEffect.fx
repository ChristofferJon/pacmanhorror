//---------------------------------------------
// ptBlendEffect
//---------------------------------------------

matrix World;
matrix View;
matrix Projection;

Texture2D TEXTURE;

SamplerState linearSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

//------------------------------------
// input/output
//------------------------------------

struct VS_INPUT
{
	float3 p : POSITION;
	float2 t : TEXCOORD;
};

struct PS_INPUT
{
	float4 p : SV_POSITION;
	float2 t : TEXCOORD;
};

//-----------------------------------------
// VertexShader
//-----------------------------------------
PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output;
	float4 pos = float4( input.p, 1.0f );
	pos = mul ( pos, World );
	pos = mul ( pos, View );
	output.p = mul( pos, Projection );

	output.t = input.t;

	return output;
}

//-------------------------------------------
// PixelShader
//-------------------------------------------
float4 PS( PS_INPUT input ) : SV_Target
{
	float4 tex = TEXTURE.Sample( linearSampler, input.t );
	return tex;
}

//------------------------------------------
// Techniques
//------------------------------------------
technique10 PTBLEND_RENDER
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
	}
}