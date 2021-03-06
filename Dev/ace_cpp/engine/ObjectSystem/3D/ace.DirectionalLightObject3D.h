﻿
#pragma once

#include "ace.Object3D.h"

namespace ace
{
	/**
	@brief	無限遠光源の機能を提供するクラス
	*/
	class DirectionalLightObject3D
		: public Object3D
	{
	private:
		std::shared_ptr<CoreDirectionalLightObject3D> m_coreObject;

	protected:
		/**
		@brief	オーバーライドして、このオブジェクトの初期化処理を記述できる。
		*/
		virtual void OnStart() {};

		/**
		@brief	オーバーライドして、毎フレーム実行される更新処理を記述できる。
		*/
		virtual void OnUpdate() {};

		/**
		@brief	オーバーライドして、追加の描画処理を記述できる。
		*/
		virtual void OnDrawAdditionally() {};

	public:
		DirectionalLightObject3D();
		virtual ~DirectionalLightObject3D();

		/**
			@brief	光源の色を取得する。
			@return	光源の色
		*/
		Color GetColor();
		/**
		@brief	光源の色を設定する。
		@param	color	光源の色
		*/
		void SetColor(const Color& color);
	};
}