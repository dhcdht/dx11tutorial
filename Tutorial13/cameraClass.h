/********************************************************************
	created:	2012/03/24
	created:	24:3:2012   21:29
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial4\cameraClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial4
	file base:	cameraClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef cameraClass_h__
#define cameraClass_h__

#include <D3DX10math.h>

class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass &aCameraClass);
	~CameraClass();

	void setPosition(float aX, float aY, float aZ);
	void setRotation(float aX, float aY, float aZ);

	D3DXVECTOR3 getPosition();
	D3DXVECTOR3 getRotation();

	void render();
	void getViewMatrix(D3DXMATRIX &viewMatrix);

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	D3DXMATRIX m_viewMatrix;
};

#endif // cameraClass_h__