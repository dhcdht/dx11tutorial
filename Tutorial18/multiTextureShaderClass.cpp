/********************************************************************
	created:	2012/05/02
	created:	2:5:2012   20:52
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial17\multiTextureShaderClass.cpp
	file path:	D:\Documents\C\DX11Tutorial\Tutorial17
	file base:	multiTextureShaderClass
	file ext:	cpp
	author:		dhc
	
	purpose:	
*********************************************************************/
#include "multiTextureShaderClass.h"

MultiTextureShaderClass::MultiTextureShaderClass()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_matrixBuffer = 0;
	m_sampleState = 0;
}

MultiTextureShaderClass::MultiTextureShaderClass( const MultiTextureShaderClass &other )
{

}

MultiTextureShaderClass::~MultiTextureShaderClass()
{

}

bool MultiTextureShaderClass::initialize( ID3D11Device *aD3DDevice, HWND aHwnd )
{
	bool result;

	result = initializeShader(
		aD3DDevice, aHwnd,
		L"./shader/multiTexture.vsh", L"./shader/multiTexture.psh");
	if (!result)
	{
		return false;
	}

	return true;
}

void MultiTextureShaderClass::shutdown()
{
	shutdownShader();

	return ;
}

bool MultiTextureShaderClass::render( 
	ID3D11DeviceContext *aD3DDeviceContext, 
	int aIndexCount, D3DXMATRIX aWorldMatrix, 
	D3DXMATRIX aViewMatrix, D3DXMATRIX aProjectionMatrix, 
	ID3D11ShaderResourceView **aTextures )
{
	bool result;

	result = setShaderParameters(
		aD3DDeviceContext, aWorldMatrix, aViewMatrix,
		aProjectionMatrix, aTextures);
	if (!result)
	{
		return false;
	}

	renderShader(aD3DDeviceContext, aIndexCount);

	return true;
}

bool MultiTextureShaderClass::initializeShader( 
	ID3D11Device *aD3DDevice, HWND aHwnd, 
	WCHAR *aVSFileName, WCHAR *aPSFileName )
{
	HRESULT result;
	ID3D10Blob *errorMessage;
	ID3D10Blob *vertexShaderBuffer;
	ID3D10Blob *pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_SAMPLER_DESC samplerDesc;

	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	result = D3DX11CompileFromFile(
		aVSFileName, NULL, NULL, "multiTextureVertexShader",
		"vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS,
		0, NULL, &vertexShaderBuffer, &errorMessage, NULL);

	if (FAILED(result))
	{
		if (errorMessage)
		{
			outputShaderErrorMessage(
				errorMessage, aHwnd, aVSFileName);
		}
		else
		{
			MessageBox(aHwnd, aVSFileName,
				L"找不到着色器文件", MB_OK);
		}

		return false;
	}

	result = D3DX11CompileFromFile(
		aPSFileName, NULL, NULL, "multiTexturePixelShader",
		"ps_4_0", D3D10_SHADER_ENABLE_STRICTNESS,
		0, NULL, &pixelShaderBuffer, &errorMessage, NULL);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			outputShaderErrorMessage(
				errorMessage, aHwnd, aPSFileName);
		}
		else
		{
			MessageBox(aHwnd, aPSFileName, 
				L"找不到着色器文件", MB_OK);
		}

		return false;
	}

	result = aD3DDevice->CreateVertexShader(
		vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), NULL,
		&m_vertexShader);
	if (FAILED(result))
	{
		return false;
	}

	result = aD3DDevice->CreatePixelShader(
		pixelShaderBuffer->GetBufferPointer(),
		pixelShaderBuffer->GetBufferSize(), NULL,
		&m_pixelShader);
	if (FAILED(result))
	{
		return false;
	}

	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	result = aD3DDevice->CreateInputLayout(
		polygonLayout, numElements, 
		vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), &m_layout);
	if (FAILED(result))
	{
		return false;
	}

	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	result = aD3DDevice->CreateBuffer(
		&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(result))
	{
		return false;
	}

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	result = aD3DDevice->CreateSamplerState(
		&samplerDesc, &m_sampleState);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void MultiTextureShaderClass::shutdownShader()
{
	if(m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = 0;
	}

	if(m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}

	if(m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}

	if(m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = 0;
	}

	if(m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}

	return;
}

void MultiTextureShaderClass::outputShaderErrorMessage( 
	ID3D10Blob *aError, HWND aHwnd, WCHAR *aFileName )
{
	char* compileErrors;
	unsigned long bufferSize, i;
	ofstream fout;


	compileErrors = (char*)(aError->GetBufferPointer());

	bufferSize = aError->GetBufferSize();

	fout.open("shader-error.txt");

	for(i=0; i<bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	fout.close();

	aError->Release();
	aError = 0;

	MessageBox(aHwnd, 
		L"Error compiling shader.  Check shader-error.txt for message.", 
		aFileName, MB_OK);

	return;
}

bool MultiTextureShaderClass::setShaderParameters( 
	ID3D11DeviceContext *aD3DDeviceContext, 
	D3DXMATRIX aWorldMatrix, D3DXMATRIX aViewMatrix, 
	D3DXMATRIX aProjectionMatrix, 
	ID3D11ShaderResourceView **aTextures )
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	unsigned int bufferNumber;


	D3DXMatrixTranspose(&aWorldMatrix, &aWorldMatrix);
	D3DXMatrixTranspose(&aViewMatrix, &aViewMatrix);
	D3DXMatrixTranspose(&aProjectionMatrix, &aProjectionMatrix);

	result = aD3DDeviceContext->Map(
		m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 
		0, &mappedResource);
	if(FAILED(result))
	{
		return false;
	}

	dataPtr = (MatrixBufferType*)mappedResource.pData;

	dataPtr->world = aWorldMatrix;
	dataPtr->view = aViewMatrix;
	dataPtr->projection = aProjectionMatrix;

	aD3DDeviceContext->Unmap(m_matrixBuffer, 0);

	bufferNumber = 0;

	aD3DDeviceContext->VSSetConstantBuffers(
		bufferNumber, 1, &m_matrixBuffer);

	aD3DDeviceContext->PSSetShaderResources(0, 2, aTextures);

	return true;
}

void MultiTextureShaderClass::renderShader( ID3D11DeviceContext *aD3DDeviceContext, int aIndexCount )
{
	aD3DDeviceContext->IASetInputLayout(m_layout);

	aD3DDeviceContext->VSSetShader(m_vertexShader, NULL, 0);
	aD3DDeviceContext->PSSetShader(m_pixelShader, NULL, 0);

	aD3DDeviceContext->PSSetSamplers(0, 1, &m_sampleState);

	aD3DDeviceContext->DrawIndexed(aIndexCount, 0, 0);

	return ;
}
