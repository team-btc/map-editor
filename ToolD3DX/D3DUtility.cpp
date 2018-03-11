#include "stdafx.h"
#include "D3DUtility.h"

namespace D3DUTILITY
{
    float GetLength(Vector2 v1, Vector2 v2)
    {
        Vector2 v3 = v1 - v2;
        return D3DXVec2Length(&v3);
    }

    MATERIAL9 InitMtrl(XColor a, XColor d, XColor s, XColor e, float p)
    {
        MATERIAL9 mtrl;
        mtrl.Ambient = a;
        mtrl.Diffuse = d;
        mtrl.Specular = s;
        mtrl.Emissive = e;
        mtrl.Power = p;

        return mtrl;
    }

    void ComputeNormal(Vector3* out, Vector3* p0, Vector3* p1, Vector3* p2)
    {
        Vector3 v01 = *p1 - *p0;
        Vector3 v02 = *p2 - *p0;

        D3DXVec3Cross(out, &v01, &v02);
        D3DXVec3Normalize(out, out);
    }

    LIGHT9 InitDirectional(Vector3* dir, XColor* c)
    {
        LIGHT9 stLight;
        ZeroMemory(&stLight, sizeof(LIGHT9));

        stLight.Type = D3DLIGHT_DIRECTIONAL;
        stLight.Ambient = *c * 0.4f;
        stLight.Diffuse = *c;
        stLight.Specular = *c * 0.6f;
        stLight.Direction = *dir;

        return stLight;
    }

    LIGHT9 InitPoint(Vector3* pos, XColor* c)
    {
        LIGHT9 stLight;
        ZeroMemory(&stLight, sizeof(LIGHT9));

        stLight.Type = D3DLIGHT_POINT;
        stLight.Ambient = *c * 0.4f;
        stLight.Diffuse = *c;
        stLight.Specular = *c * 0.6f;
        stLight.Position = *pos;
        stLight.Range = 20.0f;
        stLight.Falloff = 1.0f;
        stLight.Attenuation0 = 0.005f;
        stLight.Attenuation1 = 0.005f;
        stLight.Attenuation2 = 0.005f;

        return stLight;
    }

    LIGHT9 InitSpot(Vector3* dir, Vector3* pos, XColor* c)
    {
        LIGHT9 stLight;
        ZeroMemory(&stLight, sizeof(LIGHT9));

        stLight.Type = D3DLIGHT_SPOT;
        stLight.Ambient = *c * 0.4f;
        stLight.Diffuse = *c;
        stLight.Specular = *c * 0.6f;
        stLight.Direction = *dir;
        stLight.Position = *pos;
        stLight.Range = 50.0f;
        stLight.Falloff = 1.0f;
        stLight.Theta = 0.0f;
        stLight.Phi = D3DX_PI / 6;
        stLight.Attenuation0 = 0.005f;
        stLight.Attenuation1 = 0.005f;
        stLight.Attenuation2 = 0.005f;

        return stLight;
    }

    float DwordToFloat(DWORD DWORD_Num)
    {
        return *((FLOAT*)&DWORD_Num);
    }

    DWORD FloatToDword(float FLOAT_Num)
    {
        // 플롯의 주소를 DWORD포인터로 만들고 얘의 실체를 보냄
        return  *((DWORD*)&FLOAT_Num);
       
        // 포인터는 비트 자체가 의미 있는 값이므로, 가리키는 대상이 다른 포인터 사이의 형 변환은 
        // 이진 비트열을 파괴하지 않는다.
        // long : 4바이트 –2,147,483,648 ~ 2,147,483,647
        // unsigned long : 4바이트 0 ~ 4,294,967,295
        // float : 4바이트 3.4E+/-38(7개의 자릿수)
    }

    float GetRandomFloat(float fMin, float fMax)
    {
        // rand() 0 ~ 32676 사이의 난수(int)정수 발생
        // RAND_MAX == 32767
        // 4.0f ~ 4.5f
        // 랜덤이 4가 나왔을 때
        // ( (0.5f) * 4 / 32676)    
        return ((fMax - fMin) * ((float)rand() / RAND_MAX)) + fMin;
    }

    D3DXVECTOR3 GetRandomVector3(D3DXVECTOR3 vMin, D3DXVECTOR3 vMax)
    {
        float x = GetRandomFloat(vMin.x, vMax.x);
        float y = GetRandomFloat(vMin.y, vMax.y);
        float z = GetRandomFloat(vMin.z, vMax.z);

        return D3DXVECTOR3(x, y, z);
    }
}