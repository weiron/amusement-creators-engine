﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ace
{
	/// <summary>
	/// 長方形(整数)の構造体
	/// </summary>
	[System.Runtime.InteropServices.StructLayout(System.Runtime.InteropServices.LayoutKind.Sequential)]
	public struct RectI
	{
		/// <summary>
		/// 左上X座標
		/// </summary>
		public int X { get; set; }

		/// <summary>
		/// 左上Y座標
		/// </summary>
		public int Y { get; set; }

		/// <summary>
		/// 横幅
		/// </summary>
		public int Width { get; set; }

		/// <summary>
		/// 縦幅
		/// </summary>
		public int Height { get; set; }

		/// <summary>
		/// 左上座標を取得する。
		/// </summary>
		public Vector2DI Position
		{
			get { return new Vector2DI( X, Y ); }
		}

		/// <summary>
		/// 大きさを取得する。
		/// </summary>
		public Vector2DI Size
		{
			get { return new Vector2DI( Width, Height ); }
		}

		/// <summary>
		/// 四隅の座標を(X,Y)、(X+Width,Y)、(X+Width,Y+Height)、(X,Y+Height)の順に配列として取得する。
		/// </summary>
		public Vector2DI[] Vertexes
		{
			get
			{
				return new Vector2DI[]{
				new Vector2DI(X,Y),
				new Vector2DI(X+Width,Y),
				new Vector2DI(X+Width,Y+Height),
				new Vector2DI(X,Y+Height)};
			}
		}

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="x">左上X座標</param>
		/// <param name="y">左上Y座標</param>
		/// <param name="width">横幅</param>
		/// <param name="height">縦幅</param>
		public RectI(int x, int y, int width, int height)
			: this()
		{
			this.X = x;
			this.Y = y;
			this.Width = width;
			this.Height = height;
		}
	}
}
