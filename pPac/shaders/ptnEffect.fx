//------------------------------------
// PositionTextureNormal
//------------------------------------

#include "lighthelper.fx"

matrix World;
matrix View;
matrix Projection;

Texture2D   TEXTURE;
SamplerState linearSampler 
{
	Filter = MIN_MAG_MIP_LINEAR; 
	AddressU = Wrap;
	AddressV = Wrap;
};

// variables

struct Material
{
	float Ka, Kd, Ks, A;
};

Material material;
float3 eye;
float3 direction;
float dist;
float intensity;

//--------------------------------
// Phong
//--------------------------------

float4 Phong( Material M, float3 N, float3 L, float3 V, float3 R )
{	
	float4 ambientLight = float4( M.A, M.A, M.A, M.A );
	float4 Ia = M.Ka * ambientLight;
	float4 Id = M.Kd * saturate( dot(N,L) );
	float4 Is = M.Ks * pow( saturate(dot(R,V)), M.A );
	
	return Ia * ( Id + Is );
} 

//-------------------------------
// Input/Output
//-------------------------------

struct VS_INPUT
{
	float3 p : POSITION;
	float3 n : NORMAL;
	float2 t : TEXCOORD;
};

struct PS_INPUT
{
	float4 p  : SV_POSITION;
	float4 wp : POSITION;
	float3 n  : NORMAL;
	float2 t  : TEXCOORD;
};

//------------------------------------
// VertexShader
//------------------------------------

PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output;
	
	float4 pos = float4( input.p, 1 );
	output.wp = mul( pos, World );
	output.p = mul( output.wp, View );
	output.p = mul( output.p, Projection );

	output.n = normalize( mul( input.n, (float3x3) World ) );

	output.t = input.t;

	return output;
}

//----------------------------------------
// PixelShader
//----------------------------------------

float4 PS( PS_INPUT input ) : SV_Target
{	
	input.n = normalize( input.n );
	float3 V = normalize( eye - (float3)input.wp );
	float3 R = reflect( direction, input.n );

	float4 I = Phong( material, input.n, -direction, V, R );

	float4 tex = TEXTURE.Sample( linearSampler, input.t );
	//return I;
	return tex * I * dist * intensity;
}

//----------------------------
// Technique
//----------------------------

technique10 PTN_RENDER
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
	}
}