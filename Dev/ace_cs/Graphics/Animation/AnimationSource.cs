﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ace
{
	/// <summary>
	/// アニメーションの元データのクラス
	/// </summary>
	public class AnimationSource : IDestroy
	{
		internal swig.AnimationSource SwigObject { get; set; }

		internal AnimationSource(swig.AnimationSource swig)
		{
#if DEBUG
			// 唯一の対応するクラスであることを保証
			if (GC.AnimationSources.GetObject(swig.GetPtr()) != null) throw new Exception();
#endif
			SwigObject = swig;
		}

		~AnimationSource()
		{
			Destroy();
		}

		public bool IsDestroyed
		{
			get
			{
				return SwigObject == null;
			}
		}

		public void Destroy()
		{
			lock (this)
			{
				if (SwigObject == null) return;
				GC.Collector.AddObject(SwigObject);
				SwigObject = null;
			}
			System.GC.SuppressFinalize(this);
		}

		/// <summary>
		/// ボーンごとのアニメーションを追加する。
		/// </summary>
		/// <param name="keyframeAnimation">アニメーション</param>
		public void AddAnimation(KeyframeAnimation keyframeAnimation) 
		{
			SwigObject.AddAnimation(keyframeAnimation.SwigObject);
		}

		/// <summary>
		/// ボーンごとのアニメーションを削除する。
		/// </summary>
		/// <param name="keyframeAnimation">アニメーション</param>
		public void RemoveAnimation(KeyframeAnimation keyframeAnimation) 
		{
			SwigObject.RemoveAnimation(keyframeAnimation.SwigObject);
		}
	}
}
