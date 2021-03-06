﻿
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "ace.NativeShader_Imp_DX11.h"
#include "../../../Log/ace.Log.h"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace ace {

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
ID3DBlob* NativeShader_Imp_DX11::CompileVertexShader(Graphics_Imp_DX11* g, const char* vertexShaderText, const char* vertexShaderFileName, std::vector <Macro>& macro, Log* log)
{
	ID3DBlob* shader = nullptr;
	ID3DBlob* error = nullptr;

	if (macro.size() > 0)
	{
		Macro m;
		m.Definition = NULL;
		m.Name = NULL;
		macro.push_back(m);
	}

	/* この方法だとVS4.0以上でのコンパイルが要求 */
	auto hr = D3DCompile(
		vertexShaderText,
		strlen(vertexShaderText),
		vertexShaderFileName,
		macro.size() > 0 ? (D3D_SHADER_MACRO*) &macro[0] : NULL,
		NULL,
		"main",
		"vs_4_0",
		D3D10_SHADER_PACK_MATRIX_ROW_MAJOR,
		0,
		&shader,
		&error);

	if (macro.size() > 0)
	{
		macro.pop_back();
	}

	if (FAILED(hr))
	{
		log->WriteHeading("頂点シェーダーコンパイル失敗");
		log->WriteLine(vertexShaderFileName);

		if (hr == E_OUTOFMEMORY)
		{
			log->WriteLine("E_OUTOFMEMORY");
		}
		else
		{
			log->WriteLine("不明なエラー");
		}

		if (error != NULL)
		{
			log->WriteLine((const char*) error->GetBufferPointer());
			OutputDebugStringA((const char*) error->GetBufferPointer());
			error->Release();
		}

		return nullptr;
	}

	return shader;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
ID3DBlob* NativeShader_Imp_DX11::CompilePixelShader(Graphics_Imp_DX11* g, const char* vertexShaderText, const char* vertexShaderFileName, std::vector <Macro>& macro, Log* log)
{
	ID3DBlob* shader = nullptr;
	ID3DBlob* error = nullptr;

	if (macro.size() > 0)
	{
		Macro m;
		m.Definition = NULL;
		m.Name = NULL;
		macro.push_back(m);
	}

	/* この方法だとPS4.0以上でのコンパイルが要求 */
	auto hr = D3DCompile(
		vertexShaderText,
		strlen(vertexShaderText),
		vertexShaderFileName,
		macro.size() > 0 ? (D3D_SHADER_MACRO*) &macro[0] : NULL,
		NULL,
		"main",
		"ps_4_0",
		D3D10_SHADER_PACK_MATRIX_ROW_MAJOR,
		0,
		&shader,
		&error);

	if (macro.size() > 0)
	{
		macro.pop_back();
	}

	if (FAILED(hr))
	{
		log->WriteHeading("ピクセルシェーダーコンパイル失敗");
		log->WriteLine(vertexShaderFileName);

		if (hr == E_OUTOFMEMORY)
		{
			log->WriteLine("E_OUTOFMEMORY");
		}
		else
		{
			log->WriteLine("不明なエラー");
		}

		if (error != NULL)
		{
			log->WriteLine((const char*) error->GetBufferPointer());
			OutputDebugStringA((const char*) error->GetBufferPointer());
			error->Release();
		}

		return nullptr;
	}

	return shader;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
NativeShader_Imp_DX11::NativeShader_Imp_DX11(Graphics* graphics, ID3D11VertexShader* vertexShader, ID3D11PixelShader* pixelShader, ID3D11InputLayout* layout)
	: NativeShader_Imp(graphics)
	, m_vertexShader(vertexShader)
	, m_pixelShader(pixelShader)
	, m_vertexDeclaration(layout)
	, m_constantBufferToVS(nullptr)
	, m_constantBufferToPS(nullptr)
{

}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
NativeShader_Imp_DX11::~NativeShader_Imp_DX11()
{
	SafeRelease(m_constantBufferToVS);
	SafeRelease(m_constantBufferToPS);
	SafeRelease(m_vertexShader);
	SafeRelease(m_pixelShader);
	SafeRelease(m_vertexDeclaration);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void NativeShader_Imp_DX11::CreateVertexConstantBufferInternal(int32_t size, std::vector <ConstantBufferInformation>& info)
{
	SafeRelease(m_constantBufferToVS);

	auto g = (Graphics_Imp_DX11*)GetGraphics();

	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.ByteWidth = size;
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float) ;

	g->GetDevice()->CreateBuffer(&hBufferDesc, NULL, &m_constantBufferToVS);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void NativeShader_Imp_DX11::CreatePixelConstantBufferInternal(int32_t size, std::vector <ConstantBufferInformation>& info)
{
	SafeRelease(m_constantBufferToPS);

	auto g = (Graphics_Imp_DX11*) GetGraphics();

	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.ByteWidth = size;
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float) ;

	g->GetDevice()->CreateBuffer(&hBufferDesc, NULL, &m_constantBufferToPS);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void NativeShader_Imp_DX11::AssignConstantBuffer()
{
	auto g = (Graphics_Imp_DX11*) GetGraphics();

	if (m_vertexConstantBuffer != nullptr)
	{
		g->GetContext()->UpdateSubresource(m_constantBufferToVS, 0, NULL, m_vertexConstantBuffer, 0, 0);
		g->GetContext()->VSSetConstantBuffers(0, 1, &m_constantBufferToVS);
	}

	if (m_pixelConstantBuffer != nullptr)
	{
		g->GetContext()->UpdateSubresource(m_constantBufferToPS, 0, NULL, m_pixelConstantBuffer, 0, 0);
		g->GetContext()->PSSetConstantBuffers(0, 1, &m_constantBufferToPS);
	}
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
NativeShader_Imp_DX11* NativeShader_Imp_DX11::Create(
	Graphics* graphics,
	const char* vertexShaderText,
	const char* vertexShaderFileName,
	const char* pixelShaderText,
	const char* pixelShaderFileName,
	std::vector <VertexLayout>& layout,
	std::vector <Macro>& macro,
	Log* log)
{
	HRESULT hr;
	auto g = (Graphics_Imp_DX11*)graphics;
	ID3D11VertexShader* vs = nullptr;
	ID3D11PixelShader* ps = nullptr;
	ID3D11InputLayout* il = nullptr;
	std::vector< D3D11_INPUT_ELEMENT_DESC> decl;


	auto vertexShader = CompileVertexShader(
		(Graphics_Imp_DX11*) graphics,
		vertexShaderText,
		vertexShaderFileName,
		macro,
		log
		);
	
	auto pixelShader = CompilePixelShader(
		(Graphics_Imp_DX11*) graphics,
		pixelShaderText,
		pixelShaderFileName,
		macro,
		log
		);

	if (vertexShader == nullptr ||
		pixelShader == nullptr)
	{
		goto End;
	}

	hr = g->GetDevice()->CreateVertexShader(
		vertexShader->GetBufferPointer(),
		vertexShader->GetBufferSize(),
		NULL,
		&vs
		);

	if (FAILED(hr))
	{
		log->WriteHeading("頂点シェーダー生成失敗");
		log->WriteLine(vertexShaderFileName);
		goto End;
	}

	hr = g->GetDevice()->CreatePixelShader(
		pixelShader->GetBufferPointer(),
		pixelShader->GetBufferSize(),
		NULL,
		&ps
		);

	if (FAILED(hr))
	{
		log->WriteHeading("ピクセルシェーダー生成失敗");
		log->WriteLine(pixelShaderFileName);
		goto End;
	}

	int32_t byteOffset = 0;
	for each ( auto& l in layout)
	{
		auto d = D3D11_INPUT_ELEMENT_DESC();
		ZeroMemory(&d, sizeof(D3D11_INPUT_ELEMENT_DESC));

		if (l.LayoutFormat == LAYOUT_FORMAT_R32G32B32_FLOAT)
		{
			d.SemanticName = l.Name.c_str();
			d.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			d.AlignedByteOffset = byteOffset;
			d.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			byteOffset += sizeof(float) * 3;
		}
		else if (l.LayoutFormat == LAYOUT_FORMAT_R8G8B8A8_UNORM)
		{
			d.SemanticName = l.Name.c_str();
			d.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			d.AlignedByteOffset = byteOffset;
			d.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			byteOffset += sizeof(float) * 1;
		}
		else if (l.LayoutFormat == LAYOUT_FORMAT_R8G8B8A8_UINT)
		{
			d.SemanticName = l.Name.c_str();
			d.Format = DXGI_FORMAT_R8G8B8A8_UINT;
			d.AlignedByteOffset = byteOffset;
			d.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			byteOffset += sizeof(float) * 1;
		}
		else if (l.LayoutFormat == LAYOUT_FORMAT_R32G32_FLOAT)
		{
			d.SemanticName = l.Name.c_str();
			d.Format = DXGI_FORMAT_R32G32_FLOAT;
			d.AlignedByteOffset = byteOffset;
			d.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			byteOffset += sizeof(float) * 2;
		}
		decl.push_back(d);
	}

	hr = g->GetDevice()->CreateInputLayout(
		&(decl[0]),
		decl.size(),
		vertexShader->GetBufferPointer(),
		vertexShader->GetBufferSize(),
		&il);

	SafeRelease(vertexShader);
	SafeRelease(pixelShader);

	if (FAILED(hr))
	{
		log->WriteHeading("頂点レイアウト生成失敗");
		log->WriteLine(vertexShaderFileName);
		log->WriteLine(pixelShaderFileName);
		goto End;
	}

	return new NativeShader_Imp_DX11(
		g,
		vs,
		ps,
		il);

End:;
	SafeRelease(vertexShader);
	SafeRelease(pixelShader);
	SafeRelease(vs);
	SafeRelease(ps);
	SafeRelease(il);

	return nullptr;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}