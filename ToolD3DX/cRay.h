#pragma once
class cRay
{
private:
	enum eRaySpace
	{
		E_NONE,
		E_VIEW,
		E_WORLD
	};

	eRaySpace m_eRaySpace;		// ���� ������ ��ġ ����(������ ������ ����)

public:
	D3DXVECTOR3 m_vOrg;
	D3DXVECTOR3 m_vDir;

public:
	cRay();
	~cRay();

	static cRay RayAtViewSpace(int x, int y);	// ��ǥ�� �޾Ƽ� �� �����̽������� ���̸� ����
	static cRay RayAtWorldSpace(int x, int y);	// ��ǥ�� �޾Ƽ� ���� �����̽������� ���̸� ����
	
	bool IsPicked(ST_SPHERE* pSphere);	// �� ������ �޾Ƽ� ���� ���̿� �浹 ���� Ȯ��
};

