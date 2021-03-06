﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ace
{
	/// <summary>
	/// エフェクトの機能を提供するクラス
	/// </summary>
	public class EffectObject3D : Object3D
	{
		swig.CoreEffectObject3D coreObject = null;

		public EffectObject3D()
		{
			coreObject = Engine.ObjectSystemFactory.CreateEffectObject3D();
			GC.Object3Ds.AddObject(coreObject.GetPtr(), this);
			commonObject = coreObject;
		}

		public override void Destroy()
		{
			coreObject = null;
			base.Destroy();
		}

		protected override void OnStart() { }
		protected override void OnUpdate() { }
		internal protected override void OnDrawAdditionally() { }

		protected override void OnUpdateInternal()
		{
		}

		/// <summary>
		/// 描画に使用するエフェクトを設定する。
		/// </summary>
		/// <param name="effect">エフェクト</param>
		public void SetEffect(Effect effect)
		{
			coreObject.SetEffect(effect.SwigObject);
		}

		/// <summary>
		/// 設定されている全てのエフェクトを再生する。
		/// </summary>
		public void Play()
		{
			coreObject.Play();
		}

		/// <summary>
		/// このオブジェクトから再生されたエフェクトを全て停止する。
		/// </summary>
		public void Stop()
		{
			coreObject.Stop();
		}

		/// <summary>
		/// このオブジェクトから再生されたエフェクトのルートを全て停止する。
		/// </summary>
		public void StopRoot()
		{
			coreObject.StopRoot();
		}

		

		/// <summary>
		/// このオブジェクトから再生されたエフェクトをオブジェクトに合わせて移動させるか取得、または設定する。
		/// </summary>
		public bool DoesMoveEffects
		{
			get
			{
				return coreObject.GetDoesMoveEffects();
			}
			set
			{
				coreObject.SetDoesMoveEffects(value);
			}
		}
	}
	
}
