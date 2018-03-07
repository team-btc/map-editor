float4 gUV;
float Brush_Radius;
float Spray_Radius;
float Density;

texture DiffuseMap_Tex
<
   //string ResourceName = "..\\..\\..\\..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Textures\\Earth.jpg";
>;
sampler2D DiffuseSampler = sampler_state
{
   Texture = (DiffuseMap_Tex);
};

struct PS_INPUT
{	
	float2 uv : TEXCOORD;
};

float4 main_0(PS_INPUT Input) : COLOR
{
	float4 diffuse = tex2D(DiffuseSampler, Input.uv);

	float4 brush = float4(0,0,0,1);
	float r = Brush_Radius;
	float sr = Spray_Radius;
	float d = Density;

	float l;
	float3 vPick = (float3)gUV;
	float3 vPixel = float3(Input.uv.x, 0, Input.uv.y);
	float3 vLen = vPick - vPixel;
	l = length(vLen);
	if (l < r)
	{
		brush = float4(1, 1, 1, 1);
	}
	if (l > r && l < sr)
	{
		float dV = (sr - l) / (sr - r);
		dV *= Density;
		brush = float4(dV, dV, dV, 1);
	}

	return diffuse + brush * 0.25f;
};

technique Shader
{
	pass Pass_0
	{
		PixelShader = compile ps_2_0 main_0();
	}
};