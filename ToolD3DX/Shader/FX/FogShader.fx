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
    Output.mPosition = P;
	

    return Output;
}

float4 ps_main(PS_INPUT Input) : COLOR
{
 
    return Input.Fog;
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