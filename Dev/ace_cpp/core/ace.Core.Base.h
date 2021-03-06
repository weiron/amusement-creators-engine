﻿#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <ace.common.Base.h>

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace ace {
	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	class Core;
	class Graphics;
	class Window;
	class Keyboard;
	class Mouse;
	class Log;
	class Profiler;
	class ProfilerViewer;
	class Renderer2D;

	class Joystick;
	class JoystickContainer;

	class Sound;
	class SoundSource;

	class Texture;
	class Texture2D;
	class RenderTexture2D;
	class CubemapTexture;

	class Shader2D;
	class Material2D;

	class Effect;

	class Model;

	class Mesh;
	class Deformer;

	class AnimationSystem;
	class AnimationClip;
	class AnimationSource;
	class KeyframeAnimation;


	class ObjectSystemFactory;
	class CoreScene;
	class CoreLayer;

	class CoreLayer2D;
	class CoreObject2D;
	class CoreTextureObject2D;
	class CoreCameraObject2D;

	class CoreLayer3D;
	class CoreObject3D;
	class CoreModelObject3D;
	class CoreCameraObject3D;
	class CoreEffectObject3D;
	class CoreDirectionalLightObject3D;

	class CorePostEffect;

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	enum eTextureFormat
	{
		TEXTURE_FORMAT_R8G8B8A8_UNORM = 0,
		TEXTURE_FORMAT_R32G32B32A32_FLOAT = 1,
		TEXTURE_FORMAT_R8G8B8A8_UNORM_SRGB = 2,
		TEXTURE_FORMAT_GL_R16G16_FLOAT = 3,
	};

	enum eTextureClassType
	{
		TEXTURE_CLASS_TEXTURE2D = 0,
		TEXTURE_CLASS_RENDERTEXTURE2D = 1,
		TEXTURE_CLASS_CUBEMAPTEXTURE = 2,
	};

	enum eAlphaBlend
	{
		/// <summary>
		/// 不透明
		/// </summary>
		ALPHA_BLEND_OPACITY = 0,
		/// <summary>
		/// 透明
		/// </summary>
		ALPHA_BLEND_BLEND = 1,
		/// <summary>
		/// 加算
		/// </summary>
		ALPHA_BLEND_ADD = 2,
		/// <summary>
		/// 減算
		/// </summary>
		ALPHA_BLEND_SUB = 3,
		/// <summary>
		/// 乗算
		/// </summary>
		ALPHA_BLEND_MUL = 4,

		ALPHA_BLEND_DWORD = 0x7fffffff,
	};

	enum eTextureFilterType
	{
		TEXTURE_FILTER_NEAREST = 0,
		TEXTURE_FILTER_LINEAR = 1,
		TEXTURE_FILTER_DWORD = 0x7fffffff,
	};

	enum eTextureWrapType
	{
		TEXTURE_WRAP_REPEAT = 0,
		TEXTURE_WRAP_CLAMP = 1,

		TEXTURE_WRAP_DWORD = 0x7fffffff,
	};

	enum eCullingType
	{
		CULLING_FRONT = 0,
		CULLING_BACK = 1,
		CULLING_DOUBLE = 2,

		CULLING_DWORD = 0x7fffffff,
	};

	enum eGraphicsType
	{
		GRAPHICS_TYPE_DX11,
		GRAPHICS_TYPE_GL,
	};

	enum eRenderedObject3DType
	{
		RENDERED_OBJECT3D_TYPE_UNKNOWN,
		RENDERED_OBJECT3D_TYPE_MESH,
		RENDERED_OBJECT3D_TYPE_CAMERA,
		RENDERED_OBJECT3D_TYPE_EFFECT,
		RENDERED_OBJECT3D_TYPE_DIRECTIONALLIGHT,
	};

	/**
		@brief	シェーダーに対して外部から設定可能なプロパティの変数の種類
	*/
	enum ShaderVariableType
	{
		SHADER_VARIABLE_TYPE_FLOAT,
		SHADER_VARIABLE_TYPE_VECTOR2DF,
		SHADER_VARIABLE_TYPE_VECTOR3DF,
		SHADER_VARIABLE_TYPE_TEXTURE2D,
	};

	/**
		@brief	シェーダーに対して外部から設定可能なプロパティの情報
	*/
	class ShaderVariableProperty
	{
	public:
		/**
			@brief	名称
		*/
		astring	Name;

		/**
			@brief	種類
		*/
		ShaderVariableType Type;

		/**
			@brief	定数バッファ上での先頭からのオフセット
		*/
		int32_t	Offset;
	};

	/**
		@brief	描画設定のクラス
	*/
	class RenderSettings
	{
	public:
		/**
			@brief	遅延レンダリングから軽量レンダリングに変更し高速に描画するか?
		*/
		bool IsLightweightMode;

		RenderSettings()
		{
			IsLightweightMode = false;
		}
	};

	/**
	@brief	参照カウンタのインターフェース
	*/
	class IReference
	{
	public:
		/**
			@brief	参照カウンタを加算する。
			@return	加算後の参照カウンタ
		*/
		virtual int AddRef() = 0;

		/**
		@brief	参照カウンタを取得する。
		@return	参照カウンタ
		*/
		virtual int GetRef() = 0;

		/**
		@brief	参照カウンタを減算する。0になった時、インスタンスを削除する。
		@return	減算後の参照カウンタ
		*/
		virtual int Release() = 0;
	};

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
};