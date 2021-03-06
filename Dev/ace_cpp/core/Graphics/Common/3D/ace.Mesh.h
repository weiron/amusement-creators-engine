﻿
#pragma once

#include <ace.common.Base.h>

#include "../../../ace.Core.Base.h"

#include "../../../ace.ReferenceObject.h"

namespace ace
{
	/**
		@brief	3Dメッシュのクラス
	*/
	class Mesh
		: public IReference
	{
	protected:
		Mesh(){}
		virtual ~Mesh(){}
	public:

		/**
			@brief	頂点を追加する。
			@param	position	座標
			@param	normal		法線
			@param	binormal	従法線
			@param	uv1			UV1
			@param	uv2			UV2
			@param	color		頂点色
			@param	boneWeights	ボーンのウエイト
			@param	boneIndexes	ボーンのインデックス
		*/
		virtual void AddVertex(
			const Vector3DF& position,
			const Vector3DF& normal,
			const Vector3DF& binormal,
			const Vector2DF& uv1,
			const Vector2DF& uv2,
			const Color& color,
			int32_t boneWeights,
			int32_t boneIndexes) = 0;

		/**
			@brief	面を追加する。
			@param	index1	頂点インデックス1
			@param	index2	頂点インデックス2
			@param	index3	頂点インデックス3
		*/
		virtual void AddFace(int32_t index1, int32_t index2, int32_t index3) = 0;

		/**
			@brief	素材を設定する。
			@param	materialIndex	素材のインデックス
			@param	faceCount	面数
			@note
			素材は追加された順に先頭から面数の数だけ割り当てられる。
		*/
		virtual void AddMaterialCount(int32_t materialIndex, int32_t faceCount) = 0;

		/**
			@brief	設定した値をGPUに送信する。
		*/
		virtual void SendToGPUMemory() = 0;

		/**
		@brief	内部シェーダーを使用する場合のカラーテクスチャを設定する。
		@param	materialIndex	材質のインデックス
		@param	テクスチャ
		@note
		AddMaterialCountを実行した後でないと無効になる。
		*/
		virtual void SetColorTexture(int32_t materialIndex, Texture2D* texture) = 0;

		/**
		@brief	内部シェーダーを使用する場合の法線テクスチャを設定する。
		@param	materialIndex	材質のインデックス
		@param	テクスチャ
		@note
		AddMaterialCountを実行した後でないと無効になる。
		*/
		virtual void SetNormalTexture(int32_t materialIndex, Texture2D* texture) = 0;

		/**
		@brief	内部シェーダーを使用する場合のスペキュラテクスチャを設定する。
		@param	materialIndex	材質のインデックス
		@param	テクスチャ
		@note
		AddMaterialCountを実行した後でないと無効になる。
		*/
		virtual void SetSpecularTexture(int32_t materialIndex, Texture2D* texture) = 0;
	};
};