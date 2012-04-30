/********************************************************************
	created:	2012/04/30
	created:	30:4:2012   9:27
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial16\frustumClass.cpp
	file path:	D:\Documents\C\DX11Tutorial\Tutorial16
	file base:	frustumClass
	file ext:	cpp
	author:		dhc
	
	purpose:	
*********************************************************************/
#include "frustumClass.h"

FrustumClass::FrustumClass()
{

}

FrustumClass::FrustumClass( const FrustumClass &other )
{

}

FrustumClass::~FrustumClass()
{

}

void FrustumClass::constructFrustum( 
	float aScreenDepth, 
	D3DXMATRIX aProjectionMatrix, D3DXMATRIX aViewMatrix )
{
	float zMinimum, r;
	D3DXMATRIX matrix;

	
	zMinimum = -aProjectionMatrix._43 / aProjectionMatrix._33;
	r = aScreenDepth / (aScreenDepth - zMinimum);
	aProjectionMatrix._33 = r;
	aProjectionMatrix._43 = -r * zMinimum;
	/*
	D3DXMatrixMultiply(&matrix, &aViewMatrix, &aProjectionMatrix);

	//近
	m_planes[0].a = matrix._14 + matrix._13;
	m_planes[0].b = matrix._24 + matrix._23;
	m_planes[0].c = matrix._34 + matrix._33;
	m_planes[0].d = matrix._44 + matrix._43;
	D3DXPlaneNormalize(&m_planes[0], &m_planes[0]);

	//远
	m_planes[1].a = matrix._14 - matrix._13; 
	m_planes[1].b = matrix._24 - matrix._23;
	m_planes[1].c = matrix._34 - matrix._33;
	m_planes[1].d = matrix._44 - matrix._43;
	D3DXPlaneNormalize(&m_planes[1], &m_planes[1]);

	//左
	m_planes[2].a = matrix._14 + matrix._11; 
	m_planes[2].b = matrix._24 + matrix._21;
	m_planes[2].c = matrix._34 + matrix._31;
	m_planes[2].d = matrix._44 + matrix._41;
	D3DXPlaneNormalize(&m_planes[2], &m_planes[2]);

	//右
	m_planes[3].a = matrix._14 - matrix._11; 
	m_planes[3].b = matrix._24 - matrix._21;
	m_planes[3].c = matrix._34 - matrix._31;
	m_planes[3].d = matrix._44 - matrix._41;
	D3DXPlaneNormalize(&m_planes[3], &m_planes[3]);

	//上
	m_planes[4].a = matrix._14 - matrix._12; 
	m_planes[4].b = matrix._24 - matrix._22;
	m_planes[4].c = matrix._34 - matrix._32;
	m_planes[4].d = matrix._44 - matrix._42;
	D3DXPlaneNormalize(&m_planes[4], &m_planes[4]);

	//下
	m_planes[5].a = matrix._14 + matrix._12;
	m_planes[5].b = matrix._24 + matrix._22;
	m_planes[5].c = matrix._34 + matrix._32;
	m_planes[5].d = matrix._44 + matrix._42;
	D3DXPlaneNormalize(&m_planes[5], &m_planes[5]);
	*/

	D3DXMatrixMultiply(&matrix, &aViewMatrix, &aProjectionMatrix);

	//近
	m_planes[0].a = matrix._13;
	m_planes[0].b = matrix._23;
	m_planes[0].c = matrix._33;
	m_planes[0].d = matrix._43;
	D3DXPlaneNormalize(&m_planes[0], &m_planes[0]);

	//远
	m_planes[1].a = matrix._14 - matrix._13; 
	m_planes[1].b = matrix._24 - matrix._23;
	m_planes[1].c = matrix._34 - matrix._33;
	m_planes[1].d = matrix._44 - matrix._43;
	D3DXPlaneNormalize(&m_planes[1], &m_planes[1]);

	//左
	m_planes[2].a = matrix._14 + matrix._11;
	m_planes[2].b = matrix._24 + matrix._21;
	m_planes[2].c = matrix._34 + matrix._31;
	m_planes[2].d = matrix._44 + matrix._41;
	D3DXPlaneNormalize(&m_planes[2], &m_planes[2]);

	//右
	m_planes[3].a = matrix._14 - matrix._11; 
	m_planes[3].b = matrix._24 - matrix._21;
	m_planes[3].c = matrix._34 - matrix._31;
	m_planes[3].d = matrix._44 - matrix._41;
	D3DXPlaneNormalize(&m_planes[3], &m_planes[3]);

	//上
	m_planes[4].a = matrix._14 - matrix._12; 
	m_planes[4].b = matrix._24 - matrix._22;
	m_planes[4].c = matrix._34 - matrix._32;
	m_planes[4].d = matrix._44 - matrix._42;
	D3DXPlaneNormalize(&m_planes[4], &m_planes[4]);

	//下
	m_planes[5].a = matrix._14 + matrix._12;
	m_planes[5].b = matrix._24 + matrix._22;
	m_planes[5].c = matrix._34 + matrix._32;
	m_planes[5].d = matrix._44 + matrix._42;
	D3DXPlaneNormalize(&m_planes[5], &m_planes[5]);

	return ;
}

bool FrustumClass::checkPoint( float x, float y, float z )
{
	for (int i = 0; i < 6; i++)
	{
		if (D3DXPlaneDotCoord(&m_planes[i], 
			&D3DXVECTOR3(x, y, z)) < 0.0f)
		{
			return false;
		}
	}

	return true;
}

bool FrustumClass::checkCube( 
	float xCenter, float yCenter, float zCenter, float radius )
{
	for (int i = 0; i < 6; i++)
	{
		if (D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3(
			xCenter-radius, yCenter-radius, zCenter-radius)) >= 0.0f)
		{
			continue;;
		}
		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((
			xCenter + radius), (yCenter - radius), (zCenter - radius))) 
			>= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((
			xCenter - radius), (yCenter + radius), (zCenter - radius))) 
			>= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((
			xCenter + radius), (yCenter + radius), (zCenter - radius))) 
			>= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((
			xCenter - radius), (yCenter - radius), (zCenter + radius))) 
			>= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((
			xCenter + radius), (yCenter - radius), (zCenter + radius))) 
			>= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((
			xCenter - radius), (yCenter + radius), (zCenter + radius)))
			>= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((
			xCenter + radius), (yCenter + radius), (zCenter + radius))) 
			>= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
}

bool FrustumClass::checkSphere( 
	float xCenter, float yCenter, float zCenter, float radius )
{
	for (int i = 0; i < 6; i++)
	{
		if (D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3(
			xCenter, yCenter, zCenter)) < -radius)
		{
			return false;
		}
	}

	return true;
}

bool FrustumClass::checkRectangle(
	float xCenter, float yCenter, float zCenter,
	float xSize, float ySize, float zSize )
{
	for(int i=0; i<6; i++)
	{
		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3(
			(xCenter - xSize), (yCenter - ySize), (zCenter - zSize))) 
			>= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3(
			(xCenter + xSize), (yCenter - ySize), (zCenter - zSize))) 
			>= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3(
			(xCenter - xSize), (yCenter + ySize), (zCenter - zSize))) 
			>= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3(
			(xCenter - xSize), (yCenter - ySize), (zCenter + zSize))) 
			>= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3(
			(xCenter + xSize), (yCenter + ySize), (zCenter - zSize))) 
			>= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3(
			(xCenter + xSize), (yCenter - ySize), (zCenter + zSize)))
			>= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3(
			(xCenter - xSize), (yCenter + ySize), (zCenter + zSize)))
			>= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3(
			(xCenter + xSize), (yCenter + ySize), (zCenter + zSize))) 
			>= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
}
