float4x4 gWorldMatrix;
float4x4 gViewMatrix;
// float4 ViewPosition;

struct VS_INPUT
{
    float4 mPosition	: POSITION;
};


struct VS_OUTPUT
{
    float4 mPosition	: POSITION;
    float Fog       : FOG;
};

struct PS_INPUT
{
    float Fog : FOG;

};

VS_OUTPUT vs_main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	float4 P = mul(Input.mPosition, gWorldMatrix);

	float fDensity = g_fog.x; 
	float fFogEnd = g_fog.y;

	float fDist = P.y / fFogEnd * 4;
	//float fDistance = distance(P, g_vEyePt);

	float f = exp(-fDist*fDensity);

	//Input.FogVal.x = f;
    Output.FogVal = Fog_Color;
    Output.mPosition = P;
    Output.FogVal.x = f;

    return Output;
}

float4 ps_main(VS_OUTPUT Input) : COLOR
{
    //PS_OUTPUT Output;

	float4 f = float4(Input.FogVal.x, Input.FogVal.x,Input.FogVal.x,Input.FogVal.x);

    //Output.RGBColor = Fog_Color;

    return  f;
	//Output.RGBColor = lerp(Fog_Color, pixelColor0 * Input.Diffuse * pixcelColor1, f);
}

technique Fog
{
    pass Pass_0
    {
        FOGENABLE = TRUE;
        FOGVERTEXMODE = LINEAR;
        FOGTABLEMODE = LINEAR;
        FOGCOLOR = 0X00CCCCCC;
        FOGSTART = 10;
        FOGEND = 1000; 
        VertexShader = compile vs_2_0 vs_main();
        PixelShader = compile ps_2_0 ps_main();
    }
};