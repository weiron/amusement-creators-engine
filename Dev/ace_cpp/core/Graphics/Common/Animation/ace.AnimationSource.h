﻿
#pragma once

#include "../../../ace.Core.Base.h"
#include "../../../ace.ReferenceObject.h"

namespace ace
{
	/**
		@brief	アニメーションの元データのクラス
	*/
	class AnimationSource
		: public IReference
	{
	public:
		AnimationSource() {}
		virtual ~AnimationSource() {}

		/**
			@brief	ボーンごとのアニメーションを追加する。
			@param	keyframeAnimation	アニメーション
		*/
		virtual void AddAnimation(KeyframeAnimation* keyframeAnimation) = 0;

		/**
		@brief	ボーンごとのアニメーションを削除する。
		@param	keyframeAnimation	アニメーション
		*/
		virtual void RemoveAnimation(KeyframeAnimation* keyframeAnimation) = 0;

#if !SWIG
		/**
		@brief	ボーンごとのアニメーションを追加する。
		@param	keyframeAnimation	アニメーション
		*/
		void AddAnimation(std::shared_ptr<KeyframeAnimation> keyframeAnimation)
		{
			AddAnimation(keyframeAnimation.get());
		}

		/**
		@brief	ボーンごとのアニメーションを削除する。
		@param	keyframeAnimation	アニメーション
		*/
		void RemoveAnimation(std::shared_ptr<KeyframeAnimation> keyframeAnimation)
		{
			RemoveAnimation(keyframeAnimation.get());
		}
#endif
	};
}

