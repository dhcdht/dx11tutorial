/********************************************************************
	created:	2012/03/24
	created:	24:3:2012   21:33
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial4\cameraClass.cpp
	file path:	D:\Documents\C\DX11Tutorial\Tutorial4
	file base:	cameraClass
	file ext:	cpp
	author:		dhc
	
	purpose:	
*********************************************************************/
#include "cameraClass.h"

CameraClass::CameraClass()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;
	
	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
}

CameraClass::CameraClass( const CameraClass &aCameraClass )
{

}

CameraClass::~CameraClass()
{

}

void CameraClass::setPosition( float aX, float aY, float aZ )
{
	m_positionX = aX;
	m_positionY = aY;
	m_positionZ = aZ;

	return ;
}

void CameraClass::setRotation( float aX, float aY, float aZ )
{
	m_rotationX = aX;
	m_rotationY = aY;
	m_rotationZ = aZ;

	return ;
}

D3DXVECTOR3 CameraClass::getPosition()
{
	return D3DXVECTOR3(m_positionX, m_positionY, m_positionZ);
}

D3DXVECTOR3 CameraClass::getRotation()
{
	return D3DXVECTOR3(m_rotationX, m_rotationY, m_rotationZ);
}

void CameraClass::render()
{
	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;

	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	pitch = m_rotationX;
	yaw = m_rotationY;
	roll = m_rotationZ;

	D3DXMatrixRotationYawPitchRoll(&rotationMatrix,
		yaw, pitch, roll);

	D3DXVec3TransformCoord(
		&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(
		&up, &up, &rotationMatrix);

	lookAt = position + lookAt;

	D3DXMatrixLookAtLH(
		&m_viewMatrix, &position, &lookAt, &up);

	return ;
}

void CameraClass::getViewMatrix( D3DXMATRIX &viewMatrix )
{
	viewMatrix = m_viewMatrix;
	return ;
}
