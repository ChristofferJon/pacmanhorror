// matrices
matrix World;
matrix View;
matrix Projection;

//--------------------------------------------------------------------------------------
// Input/Output
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float3 p : POSITION;
	float4 c : COLOR;
};

//pixel shader inputs
struct PS_INPUT
{
	float4 p : SV_POSITION;
	float4 c : COLOR;	
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output;

	float4 pos = float4( input.p, 1.0f );
	pos = mul( pos, World );
	pos = mul( pos, View );
	output.p = mul( pos, Projection );

	output.c = input.c;

	return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( PS_INPUT input ) : SV_Target
{
	return input.c;
}

//--------------------------------------------------------------------------------------
// Techniques
//--------------------------------------------------------------------------------------
technique10 BASIC_RENDER
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );		
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }    
}