﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ace
{
	/// <summary>
	/// 長方形(浮動小数点)の構造体
	/// </summary>
	[System.Runtime.InteropServices.StructLayout(System.Runtime.InteropServices.LayoutKind.Sequential)]
	public struct RectF
	{
		/// <summary>
		/// 左上X座標
		/// </summary>
		public float X { get; set; }

		/// <summary>
		/// 左上Y座標
		/// </summary>
		public float Y { get; set; }

		/// <summary>
		/// 横幅
		/// </summary>
		public float Width { get; set; }

		/// <summary>
		/// 縦幅
		/// </summary>
		public float Height { get; set; }

		/// <summary>
		/// 左上座標を取得する。
		/// </summary>
		public Vector2DF Position
		{
			get { return new Vector2DF(X, Y); }
		}

		/// <summary>
		/// 大きさを取得する。
		/// </summary>
		public Vector2DF Size
		{
			get { return new Vector2DF(Width, Height); }
		}

		/// <summary>
		/// 四隅の座標を(X,Y)、(X+Width,Y)、(X+Width,Y+Height)、(X,Y+Height)の順に配列として取得する。
		/// </summary>
		public Vector2DF[] Vertexes
		{
			get
			{
				return new Vector2DF[]{
				new Vector2DF(X,Y),
				new Vector2DF(X+Width,Y),
				new Vector2DF(X+Width,Y+Height),
				new Vector2DF(X,Y+Height)};
			}
		}

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="x">左上X座標</param>
		/// <param name="y">左上Y座標</param>
		/// <param name="width">横幅</param>
		/// <param name="height">縦幅</param>
		public RectF(float x, float y, float width, float height)
			: this()
		{
			this.X = x;
			this.Y = y;
			this.Width = width;
			this.Height = height;
		}
	}
}
