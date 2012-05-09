// matrices
matrix World;
matrix View;
matrix Projection;

// vertex shader inputs
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


//   VERTEX SHADER   //

PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output;

	output.p = float4( input.p, 1 );
	output.p = mul( output.p, World );
	output.p = mul( output.p, View );
	output.p = mul( output.p, Projection );

	output.c = input.c;

	return output;
}

//   PIXEL SHADER   //

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