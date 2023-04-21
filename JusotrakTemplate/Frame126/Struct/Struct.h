#pragma once

typedef struct tagInfo
{
	
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;
	D3DXMATRIX		matWorld;

	float GetLengthDirVec()
	{
		float fLength = 0;
		fLength = sqrtf(vDir.x * vDir.x + vDir.y * vDir.y);
		return fLength;
	}

	void NormalizedToDirVec()
	{
		float fLength = GetLengthDirVec();
		this->vDir.x /= fLength;
		this->vDir.y /= fLength;
		this->vDir.z /= fLength;
	}

	D3DXVECTOR3 GetNormalizedDirVec()
	{
		D3DXVECTOR3 vDir = this->vDir;
		float fLength = GetLengthDirVec();

		vDir.x /= fLength;
		vDir.y /= fLength;
		vDir.z /= fLength;

		return vDir;
	}

	const float GetRadianLookVec()const
	{
		return atan2f(vLook.y, vLook.x);
	}

	const float GetRadianDirVec()const
	{
		return atan2f(vDir.y, vDir.x);
	}

}INFO;

// ���� ���� : ���ʹ� ������ �߿����� ũ��� ��������� �߿����� ���� ��찡 ����. �׷��� ������ ũ�⸦ 1�� ������ �Ͽ� ����ϴµ� �̷��� ũ�Ⱑ 1�� ���� ���͸� ������ ���� ���Ͷ� �ϸ�, ���� ���ͷ� ����� ������ '������ ����ȭ'��� �Ѵ�.
// ������ ��� : �� ���Ͱ� ũ��� ������ ���ٸ� �� ���ʹ� ���� ���Ͷ�� ����

