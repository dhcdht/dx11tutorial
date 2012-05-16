/********************************************************************
	created:	2012/03/25
	created:	25:3:2012   10:50
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial6\lightClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial6
	file base:	lightClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef lightClass_h__
#define lightClass_h__

#include <D3DX10math.h>

class LightClass
{
public:
	LightClass();
	LightClass(const LightClass &aLightClass);
	~LightClass();

	void setAmbientColor(
		float aRed, float aGreen, float aBlue, float aAlpha);
	void setDiffuseColor(
		float aRed, float aGreen, float aBlue, float aAlpha);
	void setDirection(float aX, float aY, float aZ);
	void setSpecularColor(
		float aRed, float aGreen, float aBlue, float aAlpha);
	void setSpecularPower(float aPower);

	D3DXVECTOR4 getAmbientColor();
	D3DXVECTOR4 getDiffuseColor();
	D3DXVECTOR3 getDirection();
	D3DXVECTOR4 getSpecularColor();
	float getSpecularPower();

private:
	D3DXVECTOR4 m_ambientColor;
	D3DXVECTOR4 m_diffuseColor;
	D3DXVECTOR3 m_direction;
	D3DXVECTOR4 m_specularColor;
	float m_specularPower;
};

#endif // lightClass_h__