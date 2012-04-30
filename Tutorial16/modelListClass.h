/********************************************************************
	created:	2012/04/30
	created:	30:4:2012   10:31
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial16\modelListClass.h
	file path:	D:\Documents\C\DX11Tutorial\Tutorial16
	file base:	modelListClass
	file ext:	h
	author:		dhc
	
	purpose:	
*********************************************************************/
#ifndef modelListClass_h__
#define modelListClass_h__

#include <D3DX10math.h>
#include <stdlib.h>
#include <time.h>

class ModelListClass
{
private:
	struct ModelInfoType
	{
		D3DXVECTOR4 color;
		float positionX, positionY, positionZ;
	};

public:
	ModelListClass();
	ModelListClass(const ModelListClass &other);
	~ModelListClass();

	bool initialize(int numModels);
	void shutdown();

	int getModelCount();
	void getData(int index, 
		float &positionX, float &positionY, float &positionZ,
		D3DXVECTOR4 &color);

private:
	int m_modelCount;
	ModelInfoType *m_modelInfoList;
};

#endif // modelListClass_h__