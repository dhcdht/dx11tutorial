/********************************************************************
	created:	2012/03/24
	created:	24:3:2012   19:58
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial4\modelClass.cpp
	file path:	D:\Documents\C\DX11Tutorial\Tutorial4
	file base:	modelClass
	file ext:	cpp
	author:		dhc
	
	purpose:	
*********************************************************************/
#include "modelClass.h"

struct TempVertexType 
{
	float x, y, z;
};

struct TempFaceType 
{
	int vIndex1, vIndex2, vIndex3;
	int tIndex1, tIndex2, tIndex3;
	int nIndex1, nIndex2, nIndex3;
};

ModelClass::ModelClass()
{
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;

	m_texture = NULL;

	m_model = 0;
}

ModelClass::ModelClass( const ModelClass &aModelClass )
{

}

ModelClass::~ModelClass()
{

}

bool ModelClass::initialize( ID3D11Device *aD3DDevice, char *aModelFileName, WCHAR *aTextureFileName )
{
	bool result;

	result = loadModel(aModelFileName);
	if (!result)
	{
		return false;
	}

	result = initializeBuffers(aD3DDevice);
	
	result = loadTexture(aD3DDevice, aTextureFileName);
	if (!result)
	{
		return false;
	}

	return result;
}

void ModelClass::shutdown()
{
	releaseTexture();

	shutdownBuffers();

	releaseModel();

	return ;
}

void ModelClass::render( ID3D11DeviceContext *aD3DDeviceContext )
{
	renderBuffers(aD3DDeviceContext);

	return ;
}

int ModelClass::getIndexCount()
{
	return m_indexCount;
}

bool ModelClass::initializeBuffers( ID3D11Device *aD3DDevice )
{
	VertexType *vertices;
	unsigned long *indices;
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	D3D11_SUBRESOURCE_DATA indexData;
	HRESULT result;

	//m_vertexCount = 3;

	//m_indexCount = 3;

	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}

	/*
	vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	vertices[0].texture = D3DXVECTOR2(0.0f, 1.0f);
	vertices[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	vertices[1].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertices[1].texture = D3DXVECTOR2(0.5f, 0.0f);
	vertices[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	vertices[2].texture = D3DXVECTOR2(1.0f, 1.0f);
	vertices[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	*/
	for (int i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = D3DXVECTOR3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = D3DXVECTOR2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = D3DXVECTOR3(m_model[i].nx, m_model[i].ny, m_model[i].nz);

		indices[i] = i;
	}

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = aD3DDevice->CreateBuffer(
		&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = aD3DDevice->CreateBuffer(
		&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}
		
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}

void ModelClass::shutdownBuffers()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = NULL;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = NULL;
	}

	return ;
}

void ModelClass::renderBuffers( ID3D11DeviceContext *aD3DDeviceContext )
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	aD3DDeviceContext->IASetVertexBuffers(
		0, 1, &m_vertexBuffer, &stride, &offset);

	aD3DDeviceContext->IASetIndexBuffer(
		m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	aD3DDeviceContext->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return ;
}

ID3D11ShaderResourceView* ModelClass::getTexture()
{
	return m_texture->getTexture();
}

bool ModelClass::loadTexture( ID3D11Device *aD3DDevice, WCHAR *aFileName )
{
	bool result;

	m_texture = new TextureClass;
	if (NULL == m_texture)
	{
		return false;
	}

	result = m_texture->initialize(aD3DDevice, aFileName);
	if (!result)
	{
		return false;
	}

	return true;
}

void ModelClass::releaseTexture()
{
	if (NULL != m_texture)
	{
		m_texture->shutdown();
		delete m_texture;
		m_texture = NULL;
	}

	return ;
}

bool ModelClass::loadModel( char *aModelFileName )
{
	bool result;
	int vertexCount, textureCount, normalCount, faceCount;
	char garbage;

	result = readFileCounts(aModelFileName, 
		vertexCount, textureCount, normalCount, faceCount);
	if (!result)
	{
		return result;
	}

	result = loadDataStructures(aModelFileName, 
		vertexCount, textureCount, normalCount, faceCount);
	if (!result)
	{
		return result;
	}

	return true;
}

void ModelClass::releaseModel()
{
	if (m_model)
	{
		delete[] m_model;
		m_model = 0;
	}

	return ;
}

bool ModelClass::readFileCounts( char *aModelFileName, int &vertexCount, int &textureCount, int &normalCount, int &faceCount )
{
	ifstream fin;
	char input;

	vertexCount = 0;
	textureCount = 0;
	normalCount = 0;
	faceCount = 0;

	fin.open(aModelFileName);

	if (fin.fail() == true)
	{
		return false;
	}

	fin.get(input);
	while (!fin.eof())
	{
		if ('v' == input)
		{
			fin.get(input);
			if (' ' == input)
			{
				vertexCount++;
			}
			if ('t' == input)
			{
				textureCount++;
			}
			if ('n' == input)
			{
				normalCount++;
			}
		}

		if ('f' == input)
		{
			fin.get(input);
			if (' ' == input)
			{
				faceCount++;
			}
		}

		while ('\n' != input)
		{
			fin.get(input);
		}

		fin.get(input);
	}

	fin.close();

	return true;
}

bool ModelClass::loadDataStructures( char *aModelFileName, int aVertexCount, int aTextureCount, int aNormalCount, int aFaceCount )
{
	TempVertexType *vertices, *texcoords, *normals;
	TempFaceType *faces;
	ifstream fin;
	int vertexIndex, texcoordIndex, normalIndex, faceIndex, vIndex, tIndex, nIndex;
	char input, input2;

	vertices = new TempVertexType[aVertexCount];
	if (!vertices)
	{
		return false;
	}

	texcoords = new TempVertexType[aTextureCount];
	if (!texcoords)
	{
		return false;
	}

	normals = new TempVertexType[aNormalCount];
	if (!normals)
	{
		return false;
	}

	faces = new TempFaceType[aFaceCount];
	if (!faces)
	{
		return false;
	}

	vertexIndex = 0;
	texcoordIndex = 0;
	normalIndex = 0;
	faceIndex = 0;

	fin.open(aModelFileName);

	if (true == fin.fail())
	{
		return false;
	}

	fin.get(input);
	while (!fin.eof())
	{
		if ('v' == input)
		{
			fin.get(input);
			if (' ' == input)
			{
				fin >> vertices[vertexIndex].x >> vertices[vertexIndex].y >> vertices[vertexIndex].z;

				//将Z转换到左手坐标系
				vertices[vertexIndex].z = vertices[vertexIndex].z * -1.0f;
				vertexIndex++;
			}

			if ('t' == input)
			{
				fin >> texcoords[texcoordIndex].x >> texcoords[texcoordIndex].y;

				//将V转换成左手坐标系
				texcoords[texcoordIndex].y = 1.0f - texcoords[texcoordIndex].y;
				texcoordIndex++;
			}

			if ('n' == input)
			{
				fin >> normals[normalIndex].x >> normals[normalIndex].y >> normals[normalIndex].z;

				//将Z转换到左手坐标系
				normals[normalIndex].z = normals[normalIndex].z * -1.0f;
				normalIndex++;
			}
		}

		if ('f' == input)
		{
			fin.get(input);
			if (' ' == input)
			{
				//倒叙读取face数据，从而将他们从右手坐标系转换到左手坐标系
				fin >> faces[faceIndex].vIndex3 >> input2 >> faces[faceIndex].tIndex3 >> input2 >> faces[faceIndex].nIndex3
					 >> faces[faceIndex].vIndex2 >> input2 >> faces[faceIndex].tIndex2 >> input2 >> faces[faceIndex].nIndex2
					 >> faces[faceIndex].vIndex1 >> input2 >> faces[faceIndex].tIndex1 >> input2 >> faces[faceIndex].nIndex1;
				faceIndex++;
			}
		}

		while ('\n' != input)
		{
			fin.get(input);
		}

		fin.get(input);
	}

	fin.close();

	m_vertexCount = 3 * faceIndex;
	m_indexCount = m_vertexCount;

	m_model = new ModelType[m_vertexCount];

	for (int i = 0; i < faceIndex; i++)
	{
		vIndex = faces[i].vIndex1 - 1;
		tIndex = faces[i].tIndex1 - 1;
		nIndex = faces[i].nIndex1 - 1;

		m_model[i].x = vertices[vIndex].x;
		m_model[i].y = vertices[vIndex].y;
		m_model[i].z = vertices[vIndex].z;

		m_model[i].tu = texcoords[tIndex].x;
		m_model[i].tv = texcoords[tIndex].y;

		m_model[i].nx = normals[nIndex].x;
		m_model[i].ny = normals[nIndex].y;
		m_model[i].nz = normals[nIndex].z;

		vIndex = faces[i].vIndex2 - 1;
		tIndex = faces[i].tIndex2 - 1;
		nIndex = faces[i].nIndex2 - 1;

		m_model[i].x = vertices[vIndex].x;
		m_model[i].y = vertices[vIndex].y;
		m_model[i].z = vertices[vIndex].z;

		m_model[i].tu = texcoords[tIndex].x;
		m_model[i].tv = texcoords[tIndex].y;

		m_model[i].nx = normals[nIndex].x;
		m_model[i].ny = normals[nIndex].y;
		m_model[i].nz = normals[nIndex].z;

		vIndex = faces[i].vIndex3 - 1;
		tIndex = faces[i].tIndex3 - 1;
		nIndex = faces[i].nIndex3 - 1;

		m_model[i].x = vertices[vIndex].x;
		m_model[i].y = vertices[vIndex].y;
		m_model[i].z = vertices[vIndex].z;

		m_model[i].tu = texcoords[tIndex].x;
		m_model[i].tv = texcoords[tIndex].y;

		m_model[i].nx = normals[nIndex].x;
		m_model[i].ny = normals[nIndex].y;
		m_model[i].nz = normals[nIndex].z;
	}

	if (vertices)
	{
		delete[] vertices;
		vertices = 0;
	}
	if (texcoords)
	{
		delete[] texcoords;
		texcoords = 0;
	}
	if (normals)
	{
		delete[] normals;
		normals = 0;
	}
	if (faces)
	{
		delete[] faces;
		faces = 0;
	}

	return true;
}
