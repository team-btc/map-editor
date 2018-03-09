float4 gUV;
float Brush_Radius;
float Spray_Radius;
float Density;
float Tex1Density;
float Tex2Density;
float Tex3Density;


texture texture0;
texture texture1;
texture texture2;
texture texture3;
texture AlphaMap;



sampler2D TexSampler0 = sampler_state
{
   Texture = (texture0);
};
sampler2D TexSampler1 = sampler_state
{
   Texture = (texture1);
};
sampler2D TexSampler2 = sampler_state
{
   Texture = (texture2);
};
sampler2D TexSampler3 = sampler_state
{
   Texture = (texture3);
};
sampler2D TexAlpha = sampler_state
{
   Texture = (AlphaMap);
};

struct PS_INPUT
{	
	float2 uv : TEXCOORD;
};

float4 main_0(PS_INPUT Input) : COLOR
{
    float TEX1_DEN = Tex1Density;
    float TEX2_DEN = Tex2Density;
    float TEX3_DEN = Tex3Density;


    //float UVDensity = Density;
	//float4 Tex0 = tex2D(TexSampler0, UV);

    float2 UV = Input.uv;
    UV.x *= TEX1_DEN;
    UV.y *= TEX1_DEN;
	float4 Tex1 = tex2D(TexSampler1, UV);

    UV = Input.uv;
    UV.x *= TEX2_DEN;
    UV.y *= TEX2_DEN;
	float4 Tex2 = tex2D(TexSampler2, UV);
    UV = Input.uv;
    UV.x *= TEX3_DEN;
    UV.y *= TEX3_DEN;
	float4 Tex3 = tex2D(TexSampler3, UV);
	float4 Alpha = tex2D(TexAlpha, Input.uv);
    

	float4 brush = float4(0,0,0,1);
	float r = Brush_Radius;
	float sr = Spray_Radius;
    float d = Alpha.r + Alpha.g + Alpha.b;
    float Rd = Alpha.r / d;
    float Gd = Alpha.g / d;
    float Bd = Alpha.b / d;


	float l;
	float3 vPick = (float3)gUV;
	float3 vPixel = float3(Input.uv.x , 0, Input.uv.y);
	float3 vLen = vPick - vPixel;
	l = length(vLen);
	if (l < r)
	{
		brush = float4(Density * 0.1f, Density * 0.1f, Density * 0.1f, Density);
	}
	if (l > r && l < sr)
	{
		float dV = (sr - l) / (sr - r);
		dV *= Density * 0.1f;
		brush = float4(dV, dV, dV, 1);

        if ( l + 0.002f > sr )
            brush = float4(2.5f, 2.5f, 2.5f, 1);

	}

	return (Tex1 * Alpha.r * Rd + Tex2 * Alpha.g * Gd + Tex3 * Alpha.b * Bd + brush * 0.4f);
};

technique Shader
{
	pass Pass_0
	{
		PixelShader = compile ps_2_0 main_0();
	}
};