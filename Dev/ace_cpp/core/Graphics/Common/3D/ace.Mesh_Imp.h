﻿
#pragma once

#include "../../../ace.Core.Base_Imp.h"

#include <Math/ace.Vector2DI.h>
#include <Math/ace.Vector2DF.h>
#include <Math/ace.Vector3DF.h>
#include <Graphics/ace.Color.h>

#include "ace.Mesh.h"

namespace ace
{
	class Mesh_Imp
		: public Mesh
		, public ReferenceObject
	{
	public:
		struct Material
		{
			Texture2D*	ColorTexture;
			Texture2D*	NormalTexture;
			Texture2D*	SpecularTexture;

			Material();
			~Material();
		};

		struct MaterialOffset
		{
			int32_t		MaterialIndex;
			int32_t		FaceOffset;
		};

		struct BoneOffset
		{
			uint8_t		BoneIndex[32];
			int32_t		FaceOffset;
		};

	private:

		struct Vertex
		{
			Vector3DF	Position;
			Vector3DF	Normal;
			Vector3DF	Binormal;
			Vector2DF	UV1;
			Vector2DF	UV2;
			Color		VColor;
			int32_t		BoneWeights;
			int32_t		BoneIndexes;
			int32_t		BoneIndexesOriginal;
		};

		struct Face
		{
			int32_t		Index1;
			int32_t		Index2;
			int32_t		Index3;
		};

		
		Graphics_Imp*	m_graphics;

		std::shared_ptr<VertexBuffer_Imp>	m_vertexBuffer;
		std::shared_ptr<IndexBuffer_Imp>	m_indexBuffer;

		std::vector<Vertex>	m_vertexBufferOnMM;
		std::vector<Face>	m_faceBufferOnMM;

		std::vector<MaterialOffset>	m_materialOffsets;
		std::vector<BoneOffset>	m_boneOffsets;

		std::vector<Material>	m_materials;

		bool					m_requireToCalcInternalParameters;

		Mesh_Imp(Graphics* graphics);
		virtual ~Mesh_Imp();

	public:

#if !SWIG
		static Mesh_Imp* Create(Graphics* graphics);
#endif

		void AddVertex(
			const Vector3DF& position,
			const Vector3DF& normal,
			const Vector3DF& binormal,
			const Vector2DF& uv1,
			const Vector2DF& uv2,
			const Color& color,
			int32_t boneWeights,
			int32_t boneIndexes);

		/**
			@brief	内部フォーマットに直接頂点情報を読み込む。
			@note
			AddVertexで追加した場合はGPUに送信する時に計算される部分を事前に追加している。
		*/
		void AddInternalVertex(
			const Vector3DF& position,
			const Vector3DF& normal,
			const Vector3DF& binormal,
			const Vector2DF& uv1,
			const Vector2DF& uv2,
			const Color& color,
			int32_t boneWeights,
			int32_t boneIndexes,
			int32_t boneIndexesOriginal);

		/**
		@brief	内部フォーマットに直接描画ごとのGPUの行列配列とボーンの行列の組み合わせを読み込む。
		@note
		AddVertexで頂点を追加した場合はGPUに送信する時に計算される部分を事前に追加している。
		*/
		void AddInternalBoneOffset(uint8_t boneIndex[32], int32_t faceOffset);

		void AddFace(int32_t index1, int32_t index2, int32_t index3);

		void AddMaterialCount(int32_t materialIndex, int32_t faceCount);
		void SendToGPUMemory();

		void SetColorTexture(int32_t materialIndex, Texture2D* texture) override;
		void SetNormalTexture(int32_t materialIndex, Texture2D* texture) override;
		void SetSpecularTexture(int32_t materialIndex, Texture2D* texture) override;

		Material* GetMaterial(int32_t materialIndex);

		std::vector<MaterialOffset>& GetMaterialOffsets() { return m_materialOffsets; }
		std::vector<BoneOffset>& GetBoneOffsets() { return m_boneOffsets; }

#if !SWIG
		std::shared_ptr<VertexBuffer_Imp>& GetVertexBuffer() { return m_vertexBuffer; }
		std::shared_ptr<IndexBuffer_Imp>& GetIndexBuffer() { return m_indexBuffer; }
#endif

		// IReferenceを継承したデバイスオブジェクト向け定義
#if !SWIG
	public:
		virtual int GetRef() { return ReferenceObject::GetRef(); }
		virtual int AddRef() { return ReferenceObject::AddRef(); }
		virtual int Release() { return ReferenceObject::Release(); }
#endif
	};
};