//8.2.3 A Simple FX File
//Now that we have studied the vertex and pixel shaders for this chapter, we can look at the entire.fx file that describes the effect — namely rendering our geometry
//in wireframe mode.
//==================================================================
// transform.fx by Frank Luna (C) 2004 All Rights Reserved.
//
// Basic FX that simply transforms geometry from local space to
// homogeneous clip space, and draws the geometry in wireframe mode.
//==================================================================
// FX parameter (global variable to the shader).

//The new properties are in bold, and we have also updated Vertex.h / .cpp.
//Now our vertices have an extra color component; therefore, our vertex shader has an extra input parameter :

//9.2 Vertex Colors
uniform extern float4x4 gWVP;
uniform extern float gEyePos;
uniform extern float4 gFogColor;
uniform extern float gFogStart;
uniform extern float gFogRange;

// Structure
struct OutputVS
{
	float4 posW: POSITION0;
	float4 color: COLOR0;

	float fogLerpParam: TEXCOORD3;
};

// Vertex shader
OutputVS TransformVS(float3 posL: POSITION0, float4 c: COLOR0 )
{
	// Zero out our output.
	OutputVS outVS = (OutputVS)0;

	// Transform to homogeneous clip space.
	outVS.posW = mul(float4(posL, 1.0), gWVP);

	//Just pass the vertex color into the pixel shader.
	outVS.color = c;

	// Done--return the output.
	return outVS;
}

// Pixel shader
float4 TransformPS(OutputVS outVS): COLOR0
{
	//return float4(0.0f, 0.0f, 0.0f, 1.0f);
	return outVS.color;
}
// Vertex shader
OutputVS ColorVS(float3 posL: POSITION0, float4 c : COLOR0)
{
	// Zero out our output.
	OutputVS outVS = (OutputVS)0;
	// Transform to homogeneous clip space.
	outVS.posW = mul(float4(posL, 1.0), gWVP);

	outVS.color = c;

	float dist = distance(outVS.posW.xyz, gEyePos);
	// Transform to homogeneous clip space.
	outVS.fogLerpParam = saturate((dist - gFogStart) / gFogRange);

	// Done--return the output.
	return outVS;
}
// Pixel shader
float4 ColorPS(OutputVS outVS): COLOR0
{

	return lerp(outVS.color, gFogColor, outVS.fogLerpParam);
	//return float4(0.0f, 0.0f, 0.0f, 1.0f);
	//return c;
}

technique TransformTech
{
	pass P0
	{
		// Specify the vertex and pixel shader associated
		// with this pass.
		vertexShader = compile vs_2_0 TransformVS();
		//pixelShader = compile ps_2_0 TransformPS();

		// Specify the render/device states associated with

		// this pass.
		//FillMode = Wireframe;
	}
}

//Finally, the technique looks like this:
technique ColorTech
{
	pass P0
	{
		// Specify the vertex and pixel shader associated
		// with this pass.
		vertexShader = compile vs_2_0 ColorVS();
		pixelShader = compile ps_2_0 ColorPS();
	
		// Specify the render/device states associated with

		// this pass.
		//FillMode = Wireframe;
		//CullMode = None;
	}
}
//Note The.fx file all this is in is called color.fx.