// HLSL
// High level shading language

uniform extern float4x4 gWVP;
uniform extern float gEyePos;
uniform extern float4 gFogColor;
uniform extern float gFogStart;
uniform extern float gFogRange;

struct OutputVS
{
				// Semantic
	float4 posW: POSITION0;
	float4 col: COLOR0;

	float fogLerpParam: TEXCOORD3;
};

// Vertex shader
OutputVS TransformVS(float3 posL: POSITION0, float4 col: COLOR0 )
{
	OutputVS outVS = (OutputVS)0;
	outVS.posW = mul(float4(posL, 1.0), gWVP);
	outVS.col = col;
	return outVS;
}

// Pixel shader
float4 TransformPS(OutputVS outVS): COLOR0
{
	return outVS.col;
}

OutputVS FogVS(float3 posL: POSITION0, float4 col : COLOR0)
{
	OutputVS outVS = (OutputVS)0;
	outVS.posW = mul(float4(posL, 1.0), gWVP);
	outVS.col = col;

	float dist = distance(outVS.posW.xyz, gEyePos);
	outVS.fogLerpParam = saturate((dist - gFogStart) / gFogRange);

	return outVS;
}

float4 FogPS(OutputVS outVS): COLOR0
{
	return lerp(outVS.col, gFogColor, outVS.fogLerpParam);
}

technique TransformTech
{
	pass P0
	{
		vertexShader = compile vs_2_0 TransformVS();
	}
}

technique FogTech
{
	pass P0
	{
		vertexShader = compile vs_2_0 FogVS();
		pixelShader = compile ps_2_0 FogPS();

		//FillMode = WireFrame;
		CullMode = None;
	}
}