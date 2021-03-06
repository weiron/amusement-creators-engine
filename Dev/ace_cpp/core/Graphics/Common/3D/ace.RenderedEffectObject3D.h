﻿
#pragma once

#include <Math/ace.Vector2DI.h>
#include <Math/ace.Vector3DF.h>

#include "ace.RenderedObject3D.h"

namespace ace
{
	class RenderedEffectObject3D
		: public RenderedObject3D
	{
	private:
		static const int32_t GCThreshold = 32;

		struct
		{


		} m_values;

		struct
		{


		} m_values_FR;

		std::vector<Effekseer::Handle>	m_handles;
		Effect*							m_effect;
		Renderer3D*						m_renderer = nullptr;
		bool							m_doesMoveEffects = nullptr;

	public:
		RenderedEffectObject3D(Graphics* graphics);
		virtual ~RenderedEffectObject3D();

		void Flip() override;
		void Rendering(RenderingProperty& prop) override;

		void SetEffect(Effect* effect);

		/**
			@brief	設定されている全てのエフェクトを再生する。
		*/
		void Play();

		/**
			@brief	このオブジェクトから再生されたエフェクトを全て停止する。
		*/
		void Stop();

		/**
		@brief	このオブジェクトから再生されたエフェクトのルートを全て停止する。
		*/
		void StopRoot();

		/**
		@brief	このオブジェクトから再生されたエフェクトをオブジェクトに合わせて移動させるか取得する。
		@return	フラグ
		*/
		bool GetDoesMoveEffects() { return m_doesMoveEffects; }

		/**
		@brief	このオブジェクトから再生されたエフェクトをオブジェクトに合わせて移動させるか設定する。
		@param	value	フラグ
		*/
		void SetDoesMoveEffects(bool value) { m_doesMoveEffects = value; }

		void OnAdded(Renderer3D* renderer) override;

		void OnRemoving(Renderer3D* renderer) override;

		eRenderedObject3DType GetObjectType() const override { return RENDERED_OBJECT3D_TYPE_EFFECT; }
	};
}