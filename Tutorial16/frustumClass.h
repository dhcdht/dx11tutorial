/********************************************************************
	created:	2012/04/30
	created:	30:4:2012   9:23
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial16\frustumClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial16
	file base:	frustumClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef frustumClass_h__
#define frustumClass_h__

#include <D3DX10math.h>

class FrustumClass
{
public:
	FrustumClass();
	FrustumClass(const FrustumClass &other);
	~FrustumClass();

	void constructFrustum(
		float aScreenDepth,
		D3DXMATRIX aProjectionMatrix,
		D3DXMATRIX aViewMatrix);

	bool checkPoint(float x, float y, float z);
	bool checkCube(
		float xCenter, float yCenter, float zCenter, float radius);
	bool checkSphere(
		float xCenter, float yCenter, float zCenter, float radius);
	bool checkRectangle(
		float xCenter, float yCenter, float zCenter,
		float xSize, float ySize, float zSize);

private:
	D3DXPLANE m_planes[6];
};

#endif // frustumClass_h__