/********************************************************************
	created:	2012/04/30
	created:	30:4:2012   10:36
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial16\modelListClass.cpp
	file path:	D:\Documents\C\DX11Tutorial\Tutorial16
	file base:	modelListClass
	file ext:	cpp
	author:		dhc
	
	purpose:	
*********************************************************************/
#include "modelListClass.h"

ModelListClass::ModelListClass()
{
	m_modelInfoList = 0;
}

ModelListClass::ModelListClass( const ModelListClass &other )
{

}

ModelListClass::~ModelListClass()
{

}

bool ModelListClass::initialize( int numModels )
{
	float red, green, blue;

	m_modelCount = numModels;

	m_modelInfoList = new ModelInfoType[numModels];
	if (!m_modelInfoList)
	{
		return false;
	}

	srand((unsigned int)time(NULL));

	for (int i =0; i < m_modelCount; i++)
	{
		red = (float)rand() / RAND_MAX;
		green = (float)rand() / RAND_MAX;
		blue = (float)rand() / RAND_MAX;

		m_modelInfoList[i].color = D3DXVECTOR4(red, green, blue, 1.0f);

		m_modelInfoList[i].positionX = (((float)rand()-(float)rand())/RAND_MAX) * 10.0f;
		m_modelInfoList[i].positionY = (((float)rand()-(float)rand())/RAND_MAX) * 10.0f;
		m_modelInfoList[i].positionZ = ((((float)rand()-(float)rand())/RAND_MAX) * 10.0f) + 5.0f;
	}

	return true;
}

void ModelListClass::shutdown()
{
	if (m_modelInfoList)
	{
		delete[] m_modelInfoList;
		m_modelInfoList = 0;
	}

	return ;
}

int ModelListClass::getModelCount()
{
	return m_modelCount;
}

void ModelListClass::getData(
	int index, float &positionX, float &positionY, 
	float &positionZ, D3DXVECTOR4 &color )
{
	positionX = m_modelInfoList[index].positionX;
	positionY = m_modelInfoList[index].positionY;
	positionZ = m_modelInfoList[index].positionZ;

	color = m_modelInfoList[index].color;

	return ;
}
