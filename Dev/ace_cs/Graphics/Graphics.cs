﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ace
{
	public class Graphics
	{
		swig.Graphics_Imp graphics;

		internal Graphics(swig.Graphics_Imp swig)
		{
			graphics = swig;
		}

		/// <summary>
		/// テクスチャを生成する。
		/// </summary>
		/// <param name="path">パス</param>
		/// <returns>テクスチャ</returns>
		public Texture2D CreateTexture2D(string path)
		{
			var texture = graphics.CreateTexture2D_Imp(path);
			return GC.GenerateTexture2D(texture, GC.GenerationType.Create);
		}

		/// <summary>
		/// 空のテクスチャを生成する。
		/// </summary>
		/// <param name="width">横幅</param>
		/// <param name="height">縦幅</param>
		/// <param name="format">フォーマット</param>
		/// <returns>テクスチャ</returns>
		public Texture2D CreateEmptyTexture2D(int width, int height, TextureFormat format)
		{
			var texture = graphics.CreateEmptyTexture2D_Imp(width, height, (swig.eTextureFormat)format);
			return GC.GenerateTexture2D(texture, GC.GenerationType.Create);
		}

		/// <summary>
		/// 描画先として指定可能なテクスチャを生成する。
		/// </summary>
		/// <param name="width">横幅</param>
		/// <param name="height">縦幅</param>
		/// <param name="format">フォーマット</param>
		/// <returns>テクスチャ</returns>
		public RenderTexture2D CreateRenderTexture2D(int width, int height, TextureFormat format)
		{
			var rt = graphics.CreateRenderTexture2D_Imp(width,height, (swig.eTextureFormat)format);
			var p = rt.GetPtr();

			var existing = GC.Texture2Ds.GetObject(p);
			if (existing != null)
			{
				return (RenderTexture2D)existing;
			}

			var ret = new RenderTexture2D(rt);
			GC.Texture2Ds.AddObject(p, ret);
			return ret;
		}

		/// <summary>
		/// 6枚の画像ファイルからキューブマップテクスチャを生成する。
		/// </summary>
		/// <param name="front">前方向の画像ファイルへの相対パス</param>
		/// <param name="left">左方向の画像ファイルへの相対パス</param>
		/// <param name="back">後ろ方向の画像ファイルへの相対パス</param>
		/// <param name="right">右方向の画像ファイルへの相対パス</param>
		/// <param name="top">上方向の画像ファイルへの相対パス</param>
		/// <param name="bottom">下方向の画像ファイルへの相対パス</param>
		/// <returns>キューブマップ</returns>
		CubemapTexture CreateCubemapTextureFrom6ImageFiles(string front, string left, string back, string right, string top, string bottom)
		{
			return GC.GenerateCubemapTexture(graphics.CreateCubemapTextureFrom6ImageFiles_(front, left, back, right, top, bottom), GC.GenerationType.Create);
		}

		/// <summary>
		/// シェーダー(2D)を生成する。
		/// </summary>
		/// <param name="shaderText">シェーダーのコード</param>
		/// <param name="variableProperties">シェーダーで使用可能な外部入力可能な変数</param>
		/// <returns></returns>
		public Shader2D CreateShader2D(string shaderText, ShaderVariableProperty[] variableProperties)
		{
			swig.ShaderVariablePropertyVector vprops = new swig.ShaderVariablePropertyVector();
			foreach (var v_ in variableProperties)
			{
				var sprop = new swig.ShaderVariableProperty();
				sprop.Name = v_.Name;
				sprop.Type = (swig.ShaderVariableType)v_.Type;
				sprop.Offset = v_.Offset;
				vprops.Add(sprop);
			}

			var shader = graphics.CreateShader2D_Imp(shaderText, vprops);
			if (shader == null) return null;

			var p = shader.GetPtr();

			var existing = GC.Shader2Ds.GetObject(p);
			if (existing != null)
			{
				return existing;
			}

			var ret = new Shader2D(shader);
			GC.Shader2Ds.AddObject(p, ret);
			return ret;
		}

		/// <summary>
		/// マテリアル(2D)を生成する。
		/// </summary>
		/// <param name="shader">シェーダー</param>
		/// <returns>マテリアル(2D)</returns>
		public Material2D CreateMaterial2D(Shader2D shader)
		{
			var material = graphics.CreateMaterial2D_(shader.SwigObject);
			var p = material.GetPtr();

			var existing = GC.Material2Ds.GetObject(p);
			if (existing != null)
			{
				return existing;
			}

			var ret = new Material2D(material);
			GC.Material2Ds.AddObject(p, ret);
			return ret;
		}

		/// <summary>
		/// メッシュを生成する。
		/// </summary>
		/// <returns>メッシュ</returns>
		public Mesh CreateMesh()
		{
			return GC.GenerateMesh(graphics.CreateMesh_(), GC.GenerationType.Create);
		}

		/// <summary>
		/// デフォーマーを生成する。
		/// </summary>
		/// <returns>デフォーマー</returns>
		public Deformer CreateDeformer()
		{
			return GC.GenerateDeformer(graphics.CreateDeformer_(), GC.GenerationType.Create);
		}

		/// <summary>
		/// モデルを生成する。
		/// </summary>
		/// <param name="path">パス</param>
		/// <returns>モデル</returns>
		public Model CreateModel(string path)
		{
			var model = graphics.CreateModel_(path);
			if (model == null) return null;
			return GC.GenerateModel(model, GC.GenerationType.Create);
		}

		/// <summary>
		/// エフェクトを生成する。
		/// </summary>
		/// <param name="path">パス</param>
		/// <returns>エフェクト</returns>
		public Effect CreateEffect(string path)
		{
			var effect = graphics.CreateEffect_(path);
			if (effect == null) return null;
			return GC.GenerateEffect(effect, GC.GenerationType.Create);
		}

		/// <summary>
		/// 描画ランタイムの種類を取得する。
		/// </summary>
		public GraphicsType GraphicsType
		{
			get { return (GraphicsType)graphics.GetGraphicsType(); }
		}
	}
}
