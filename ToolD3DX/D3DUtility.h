#pragma once

#define WHITE   XColor(1.0f, 1.0f, 1.0f, 1.0f)
#define BLACK   XColor(0.0f, 0.0f, 0.0f, 1.0f)
#define RED     XColor(1.0f, 0.0f, 0.0f, 1.0f)
#define GREEN   XColor(0.0f, 1.0f, 0.0f, 1.0f)
#define BLUE    XColor(0.0f, 0.0f, 1.0f, 1.0f)
#define YELLOW  XColor(1.0f, 1.0f, 0.0f, 1.0f)

namespace D3DUTILITY
{
    float GetLength(Vector2 v1, Vector2 v2);

    MATERIAL9 InitMtrl(XColor a, XColor d, XColor s, XColor e, float p);

    const MATERIAL9 WHITE_MTRL = InitMtrl(WHITE, WHITE, WHITE, BLACK, 8.0f);
    const MATERIAL9 RED_MTRL = InitMtrl(RED, RED, RED, BLACK, 8.0f);
    const MATERIAL9 GREEN_MTRL = InitMtrl(GREEN, GREEN, GREEN, BLACK, 8.0f);
    const MATERIAL9 BLUE_MTRL = InitMtrl(BLUE, BLUE, BLUE, BLACK, 8.0f);
    const MATERIAL9 YELLOW_MTRL = InitMtrl(YELLOW, YELLOW, YELLOW, BLACK, 8.0f);

    void ComputeNormal(Vector3* out, Vector3* p0, Vector3* p1, Vector3* p2);

    D3DLIGHT9 InitDirectional(Vector3* dir, XColor* c);
    D3DLIGHT9 InitPoint(Vector3* pos, XColor* c);
    D3DLIGHT9 InitSpot(Vector3* dir, Vector3* pos, XColor* c);

    float DwordToFloat(DWORD DWORD_Num);					// DWORD를 FLOAT으로 변환
    DWORD FloatToDword(float FLOAT_Num);					// FLOAT을 DWORD로 변환
    float GetRandomFloat(float fMin, float fMax);			// 지정된 범위의 FLOAT의 RANDOM 값 반환 
    D3DXVECTOR3 GetRandomVector3(D3DXVECTOR3 vMin, D3DXVECTOR3 vMax);	// 지정된 범위의 D3DXVECTOR3 MIN과 MAX를 받으면 그 범위 안의 RANDOM D3DXVECTOR3 값 반환
}