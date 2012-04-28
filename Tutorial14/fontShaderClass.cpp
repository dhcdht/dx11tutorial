/********************************************************************
	created:	2012/04/25
	created:	25:4:2012   22:11
	filename: 	D:\Documents\C\DX11Tutorial\Tutorial12\fontShaderClass.cpp
	file path:	D:\Documents\C\DX11Tutorial\Tutorial12
	file base:	fontShaderClass
	file ext:	cpp
	author:		dhc
	
	purpose:	
*********************************************************************/
#include "fontShaderClass.h"

FontShaderClass::FontShaderClass()
{
	m_vertexShader = 0;
	m_pixelBuffer = 0;
	m_layout = 0;
	m_constantBuffer = 0;
	m_sampleState = 0;

	m_pixelBuffer = 0;
}

FontShaderClass::FontShaderClass( const FontShaderClass &aFontShaderClass )
{

}

FontShaderClass::~FontShaderClass()
{

}

bool FontShaderClass::initialize( ID3D11Device *aD3DDevice, HWND aHwnd )
{
	bool result;

	result = initializeShader(
		aD3DDevice, aHwnd, L"./shader/font.vsh", L"./shader/font.psh");
	if (!result)
	{
		return false;
	}

	return true;
}

void FontShaderClass::shutdown()
{
	shutdownShader();

	return ;
}

bool FontShaderClass::render( 
	ID3D11DeviceContext *aD3DDevice, int aIndexCount, 
	D3DXMATRIX aWorldMatrix, D3DXMATRIX aViewMatrix, 
	D3DXMATRIX aProjectionMatrix, 
	ID3D11ShaderResourceView *aTexture, 
	D3DXVECTOR4 aPixelColor )
{
	bool result;

	result = setShaderParameters(
		aD3DDevice, aWorldMatrix, aViewMatrix,
		aProjectionMatrix, aTexture, aPixelColor);
	if (!result)
	{
		return false;
	}

	renderShader(aD3DDevice, aIndexCount);

	return true;
}

bool FontShaderClass::initializeShader( ID3D11Device *aD3DDevice, HWND aHwnd, WCHAR *aVSFileName, WCHAR *aPSFileName )
{
	HRESULT result;
	ID3D10Blob *errorMessage;
	ID3D10Blob *vertexShaderBuffer;
	ID3D10Blob *pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC constantBufferDesc;
	D3D11_SAMPLER_DESC samplerDesc;
	D3D11_BUFFER_DESC pixelBufferDesc;

	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	result = D3DX11CompileFromFile(
		aVSFileName, NULL, NULL, "fontVertexShader",
		"vs_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		NULL, &vertexShaderBuffer, &errorMessage, NULL);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			outputShaderErrorMessage(errorMessage, aHwnd, aVSFileName);
		}
		else
		{
			MessageBox(aHwnd, aVSFileName, L"找不到着色器文件", MB_OK);
		}

		return false;
	}

	result = D3DX11CompileFromFile(
		aPSFileName, NULL, NULL, "fontPixelShader",
		"ps_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL,
		&pixelShaderBuffer, &errorMessage, NULL);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			outputShaderErrorMessage(errorMessage, aHwnd, aPSFileName);
		}
		else
		{
			MessageBox(aHwnd, aPSFileName, L"找不到着色器文件", MB_OK);
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

	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesc.ByteWidth = sizeof(ConstantBufferType);
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufferDesc.MiscFlags = 0;
	constantBufferDesc.StructureByteStride = 0;

	result = aD3DDevice->CreateBuffer(
		&constantBufferDesc, NULL, &m_constantBuffer);
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

	pixelBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	pixelBufferDesc.ByteWidth = sizeof(PixelBufferType);
	pixelBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	pixelBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pixelBufferDesc.MiscFlags = 0;
	pixelBufferDesc.StructureByteStride = 0;

	result = aD3DDevice->CreateBuffer(
		&pixelBufferDesc, NULL, &m_pixelBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void FontShaderClass::shutdownShader()
{
	if (m_pixelBuffer)
	{
		m_pixelBuffer->Release();
		m_pixelBuffer = 0;
	}

	if (m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = 0;
	}

	if (m_constantBuffer)
	{
		m_constantBuffer->Release();
		m_constantBuffer = 0;
	}

	if (m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}

	if (m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = 0;
	}

	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}

	return ;
}

void FontShaderClass::outputShaderErrorMessage( 
	ID3D10Blob *aErrorMessage, HWND aHwnd,
	WCHAR *aShaderFileName )
{
	char *compileErrors;
	unsigned int bufferSize;
	ofstream fout;

	compileErrors = (char*)(aErrorMessage->GetBufferPointer());

	bufferSize = aErrorMessage->GetBufferSize();

	fout.open("shader-error.txt");

	for (unsigned int i = 0; i < bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	fout.close();

	aErrorMessage->Release();
	aErrorMessage = 0;

	MessageBox(aHwnd, 
		L"编译着色器文件失败，请检查 shader-error.txt 来获取更多信息",
		aShaderFileName, MB_OK);

	return ;
}

bool FontShaderClass::setShaderParameters( 
	ID3D11DeviceContext *aD3DDeviceContext, 
	D3DXMATRIX aWorldMatrix, D3DXMATRIX aViewMatrix, 
	D3DXMATRIX aProjectionMatrix, 
	ID3D11ShaderResourceView *aTexture, 
	D3DXVECTOR4 aPixelColor )
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ConstantBufferType *dataPtr;
	unsigned int bufferNumber;
	PixelBufferType *dataPtr2;

	result = aD3DDeviceContext->Map(
		m_constantBuffer, 0, D3D11_MAP_WRITE_DISCARD,
		0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	dataPtr = (ConstantBufferType*)mappedResource.pData;

	D3DXMatrixTranspose(&aWorldMatrix, &aWorldMatrix);
	D3DXMatrixTranspose(&aViewMatrix, &aViewMatrix);
	D3DXMatrixTranspose(&aProjectionMatrix, &aProjectionMatrix);

	dataPtr->world = aWorldMatrix;
	dataPtr->view = aViewMatrix;
	dataPtr->projection = aProjectionMatrix;

	aD3DDeviceContext->Unmap(m_constantBuffer, 0);

	bufferNumber = 0;

	aD3DDeviceContext->VSSetConstantBuffers(
		bufferNumber, 1, &m_constantBuffer);

	aD3DDeviceContext->PSSetShaderResources(
		0, 1, &aTexture);

	result = aD3DDeviceContext->Map(
		m_pixelBuffer, 0, D3D11_MAP_WRITE_DISCARD,
		0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	dataPtr2 = (PixelBufferType*)mappedResource.pData;

	dataPtr2->pixelColor = aPixelColor;

	aD3DDeviceContext->Unmap(m_pixelBuffer, 0);

	bufferNumber = 0;

	aD3DDeviceContext->PSSetConstantBuffers(
		bufferNumber, 1, &m_pixelBuffer);

	return true;
}

void FontShaderClass::renderShader( 
	ID3D11DeviceContext *aD3DDeviceContext, int aIndexCount )
{
	aD3DDeviceContext->IASetInputLayout(m_layout);

	aD3DDeviceContext->VSSetShader(m_vertexShader, NULL, 0);
	aD3DDeviceContext->PSSetShader(m_pixelShader, NULL, 0);

	aD3DDeviceContext->PSSetSamplers(0, 1, &m_sampleState);

	aD3DDeviceContext->DrawIndexed(aIndexCount, 0, 0);

	return ;
}
