/********************************************************************
	created:	2012/03/25
	created:	25:3:2012   10:54
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial6\lightClass.cpp
	file path:	D:\Documents\C\DX11Tutorial\Tutorial6
	file base:	lightClass
	file ext:	cpp
	author:		dhc
	
	purpose:	
*********************************************************************/
#include "lightClass.h"

LightClass::LightClass()
{

}

LightClass::LightClass( const LightClass &aLightClass )
{

}

LightClass::~LightClass()
{

}

void LightClass::setDiffuseColor( float aRed, float aGreen, float aBlue, float aAlpha )
{
	m_diffuseColor = D3DXVECTOR4(aRed, aGreen, aBlue, aAlpha);

	return ;
}

void LightClass::setDirection( float aX, float aY, float aZ )
{
	m_direction = D3DXVECTOR3(aX, aY, aZ);

	return ;
}

D3DXVECTOR4 LightClass::getDiffuseColor()
{
	return m_diffuseColor;
}

D3DXVECTOR3 LightClass::getDirection()
{
	return m_direction;
}

void LightClass::setAmbientColor( float aRed, float aGreen, float aBlue, float aAlpha )
{
	m_ambientColor = D3DXVECTOR4(aRed, aGreen, aBlue, aAlpha);
	return ;
}

D3DXVECTOR4 LightClass::getAmbientColor()
{
	return m_ambientColor;
}
