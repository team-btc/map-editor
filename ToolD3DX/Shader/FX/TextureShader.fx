float4 gUV;
float Brush_Radius;
float Spray_Radius;
float Density;

float BackGroundDensity;
float Tex1Density;
float Tex2Density;
float Tex3Density;


texture BackGroundTexture;
texture texture1;
texture texture2;
texture texture3;
texture AlphaMap;

float4x4 gWorldMatrix : World;
float4x4 gViewMatrix : View;
float4x4 gProjectionMatrix : Projection;


sampler2D BackGroundTex = sampler_state
{
    Texture = (BackGroundTexture);
    AddressU = Mirror;
    AddressV = Mirror;
};
sampler2D TexSampler1 = sampler_state
{
    Texture = (texture1);
    AddressU = Mirror;
    AddressV = Mirror;
};

sampler2D TexSampler2 = sampler_state
{
    Texture = (texture2);
    AddressU = Mirror;
    AddressV = Mirror;
};

sampler2D TexSampler3 = sampler_state
{
    Texture = (texture3);
    AddressU = Mirror;
    AddressV = Mirror;
};

sampler2D TexAlpha = sampler_state
{
     Texture = (AlphaMap);
     MINFILTER = LINEAR;
     MAGFILTER = LINEAR;
};



struct VS_INPUT
{
    float4 mPosition : POSITION;
};



struct VS_OUTPUT
{
    float4 mPosition : POSITION;
};

struct PS_INPUT
{
    float2 uv : TEXCOORD;
};

VS_OUTPUT ColorShader_Pass_0_Vertex_Shader_vs_main(VS_INPUT Input)
{
    VS_OUTPUT Output;

    Output.mPosition = mul(Input.mPosition, gWorldMatrix);
    Output.mPosition = mul(Output.mPosition, gViewMatrix);
    Output.mPosition = mul(Output.mPosition, gProjectionMatrix);

    return Output;
}

float4 main_0(PS_INPUT Input) : COLOR
{

    float TEX1_DEN = Tex1Density;
    float TEX2_DEN = Tex2Density;
    float TEX3_DEN = Tex3Density;        
    float BackDensity = BackGroundDensity;
    
    
    float2 UV = Input.uv;   
    UV.x *= BackDensity;   
    UV.y *= BackDensity;   
    
    
    float4 Tex0 = tex2D(BackGroundTex, UV);   
    
    UV = Input.uv;   
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
        
    float Backd = 1.0f - Alpha.r - Alpha.g - Alpha.b;
    Backd = saturate(Backd);
   
      
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
        
        if (l + 0.001f > sr)   
            brush = float4(2.5f, 2.5f, 2.5f, 1);    
    }

    return ((Tex0 * Backd) + (Tex1 * Alpha.r *Rd) + (Tex2 * Alpha.g *Gd) + (Tex3 * Alpha.b *Bd) + brush * 0.35f);

};



technique Shader
{
    pass Pass_0
    {
        PixelShader = compile ps_2_0 main_0();
    }
};