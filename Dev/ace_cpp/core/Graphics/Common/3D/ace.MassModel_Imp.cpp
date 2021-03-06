﻿
#include "ace.MassModel_Imp.h"

#include "../ace.Graphics_Imp.h"

#include "../Resource/ace.VertexBuffer_Imp.h"
#include "../Resource/ace.IndexBuffer_Imp.h"

namespace ace
{
	bool MassObject_Imp::Load(Graphics_Imp* g, MassModel_IO& io)
	{
		m_vertexBuffer.reset();
		m_indexBuffer.reset();
		m_animationTexture.reset();

		// 頂点バッファ
		m_vertexBuffer = g->CreateVertexBuffer_Imp(sizeof(MassModel_IO::Vertex), io.Vertices.size(), false);
		m_vertexBuffer->Lock();

		auto vbuf = m_vertexBuffer->GetBuffer<MassModel_IO::Vertex>(io.Vertices.size());
		for (size_t i = 0; i < io.Vertices.size(); i++)
		{
			vbuf[i] = io.Vertices[i];
		}

		m_vertexBuffer->Unlock();

		// インデックスバッファ
		m_indexBuffer = g->CreateIndexBuffer_Imp(io.Faces.size() * 3, false, true);
		m_indexBuffer->Lock();

		auto ibuf = m_indexBuffer->GetBuffer<int32_t>(io.Faces.size() * 3);
		for (size_t i = 0; i < io.Faces.size(); i++)
		{
			ibuf[i * 3 + 0] = io.Faces[i].Index1;
			ibuf[i * 3 + 1] = io.Faces[i].Index2;
			ibuf[i * 3 + 2] = io.Faces[i].Index3;
		}

		m_indexBuffer->Unlock();

		// アニメーションテクスチャ
		auto texture = g->CreateRenderTexture(io.AnimationTexture.TextureWidth, io.AnimationTexture.TextureHeight, eTextureFormat::TEXTURE_FORMAT_R32G32B32A32_FLOAT);
		TextureLockInfomation info;

		if (texture->Lock(info))
		{
			memcpy(info.Pixels, &(io.AnimationTexture.Buffer[0]), io.AnimationTexture.Buffer.size() * 4);
			texture->Unlock();
		}
		return true;
	}

	MassObject_Imp::MassObject_Imp()
	{

	}

	MassObject_Imp::~MassObject_Imp()
	{

	}
}