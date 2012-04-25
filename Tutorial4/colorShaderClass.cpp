/********************************************************************
	created:	2012/03/24
	created:	24:3:2012   20:19
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial4\colorShaderClass.cpp
	file path:	D:\Documents\C\DX11Tutorial\Tutorial4
	file base:	colorShaderClass
	file ext:	cpp
	author:		dhc
	
	purpose:	
*********************************************************************/
#include "colorShaderClass.h"

ColorShaderClass::ColorShaderClass()
{
	m_vertexShader = NULL;
	m_pixelShader = NULL;
	m_layout = NULL;
	m_matrixBuffer = NULL;
}

ColorShaderClass::ColorShaderClass( const ColorShaderClass &aColorShaderClass )
{

}

ColorShaderClass::~ColorShaderClass()
{

}

bool ColorShaderClass::initialize( ID3D11Device *aD3DDevice, HWND aHwnd )
{
	bool result;

	result = initializeShader(aD3DDevice, aHwnd,
		L"color.vs", L"color.ps");

	return result;
}

void ColorShaderClass::shutdown()
{
	shutdownShader();

	return ;
}

bool ColorShaderClass::render( ID3D11DeviceContext *aD3DDeviceContext, int aIndexCount, D3DXMATRIX aWorldMatrix, D3DXMATRIX aViewMatrix, D3DXMATRIX aProjectionMatrix )
{
	bool result;

	result = setShaderParameters(
		aD3DDeviceContext, aWorldMatrix,
		aViewMatrix, aProjectionMatrix);
	if (!result)
	{
		return false;
	}

	renderShader(aD3DDeviceContext, aIndexCount);

	return true;
}

bool ColorShaderClass::initializeShader( 
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

	errorMessage = NULL;
	vertexShaderBuffer = NULL;
	pixelShaderBuffer = NULL;

	result = D3DX11CompileFromFile(
		aVSFileName, NULL, NULL, "colorVertexShader",
		"vs_4_0", D3D10_SHADER_ENABLE_STRICTNESS,
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
				L"Missing Shader File", MB_OK);
		}

		return false;
	}

	result = D3DX11CompileFromFile(
		aPSFileName, NULL, NULL, "colorPixelShader",
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
				L"Missing Shader File", MB_OK);
		}

		return false;
	}

	result = aD3DDevice->CreateVertexShader(
		vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(),
		NULL, &m_vertexShader);
	if (FAILED(result))
	{
		return false;
	}

	result = aD3DDevice->CreatePixelShader(
		pixelShaderBuffer->GetBufferPointer(),
		pixelShaderBuffer->GetBufferSize(),
		NULL, &m_pixelShader);
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

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
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
	vertexShaderBuffer = NULL;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = NULL;

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

	return true;
}

void ColorShaderClass::shutdownShader()
{
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

void ColorShaderClass::outputShaderErrorMessage( ID3D10Blob *aError, HWND aHwnd, WCHAR *aFileName )
{
	char *compileErrors;
	unsigned long bufferSize;
	unsigned long i;
	ofstream fout;

	compileErrors = (char *)(aError->GetBufferPointer());

	bufferSize = aError->GetBufferSize();

	fout.open("shader-error.txt");

	for (i = 0; i < bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	fout.close();

	aError->Release();
	aError = NULL;

	MessageBox(aHwnd, L"Compile shader error",
		aFileName, MB_OK);

	return ;
}

bool ColorShaderClass::setShaderParameters( ID3D11DeviceContext *aD3DDeviceContext, D3DXMATRIX aWorldMatrix, D3DXMATRIX aViewMatrix, D3DXMATRIX aProjectionMatrix )
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType *pData;
	unsigned int bufferNumber;

	D3DXMatrixTranspose(&aWorldMatrix, &aWorldMatrix);
	D3DXMatrixTranspose(&aViewMatrix, &aViewMatrix);
	D3DXMatrixTranspose(&aProjectionMatrix, &aProjectionMatrix);

	result = aD3DDeviceContext->Map(
		m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 
		0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	pData = (MatrixBufferType *)mappedResource.pData;

	pData->world = aWorldMatrix;
	pData->view = aViewMatrix;
	pData->projection = aProjectionMatrix;

	aD3DDeviceContext->Unmap(m_matrixBuffer, 0);

	bufferNumber = 0;
	aD3DDeviceContext->VSSetConstantBuffers(
		bufferNumber, 1, &m_matrixBuffer);

	return true;
}

void ColorShaderClass::renderShader( ID3D11DeviceContext *aD3DDeviceContext, int aIndexCount )
{
	aD3DDeviceContext->IASetInputLayout(m_layout);

	aD3DDeviceContext->VSSetShader(m_vertexShader, NULL, 0);
	aD3DDeviceContext->PSSetShader(m_pixelShader, NULL, 0);

	aD3DDeviceContext->DrawIndexed(aIndexCount, 0, 0);

	return ;
}
