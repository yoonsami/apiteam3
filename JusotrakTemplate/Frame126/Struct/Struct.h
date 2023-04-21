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

// 단위 벡터 : 벡터는 방향이 중요하지 크기는 상대적으로 중요하지 않은 경우가 많다. 그래서 벡터의 크기를 1로 보정을 하여 사용하는데 이렇게 크기가 1인 방향 벡터를 가리켜 단위 벡터라 하며, 단위 벡터로 만드는 과정을 '벡터의 정규화'라고 한다.
// 벡터의 상등 : 두 벡터가 크기와 방향이 같다면 두 벡터는 같은 벡터라는 개념

