%module ace_core_cs
%{

#include <ace.common.Base.h>
#include <Math/ace.RectF.h>

#include "Window/ace.Window_Imp.h"
#include "Log/ace.Log_Imp.h"

#include "Profiler/ace.Profiler.h"
#include "Profiler/ace.Profiler_Imp.h"

#include "Input/ace.IMouseButtonState.h"
#include "Input/ace.IMouseWheelableButtonState.h"
#include "Input/ace.MiddleButton.h"
#include "Input/ace.SideButton.h"
#include "Input/ace.Mouse_Imp.h"
#include "Input/ace.Keyboard_Imp.h"
#include "Input/ace.Joystick.h"
#include "Input/ace.Joystick_Imp.h"
#include "Input/ace.JoystickContainer_Imp.h"

#include "Sound/ace.SoundSource_Imp.h"
#include "Sound/ace.Sound_Imp.h"

#include "Graphics/Common/ace.Graphics_Imp.h"
#include "Graphics/Common/Resource/ace.Texture2D_Imp.h"
#include "Graphics/Common/Resource/ace.CubemapTexture_Imp.h"

#include "Graphics/Common/Resource/ace.Shader2D_Imp.h"

#include "Graphics/Common/Resource/ace.Material_Imp.h"
#include "Graphics/Common/Resource/ace.Material2D_Imp.h"

#include "Graphics/Common/Resource/ace.Effect.h"

#include "Graphics/Common/3D/ace.Mesh.h"
#include "Graphics/Common/3D/ace.Deformer.h"
#include "Graphics/Common/3D/ace.Model.h"

#include "Graphics/Common/Animation/ace.AnimationSystem_Imp.h"
#include "Graphics/Common/Animation/ace.AnimationClip_Imp.h"
#include "Graphics/Common/Animation/ace.AnimationSource_Imp.h"
#include "Graphics/Common/Animation/ace.KeyframeAnimation_Imp.h"

#include "ObjectSystem/ace.eChildMode.h"
#include "ObjectSystem/2D/ace.CoreObject2D.h"
#include "ObjectSystem/2D/ace.CoreTextureObject2D.h"
#include "ObjectSystem/2D/ace.CoreCameraObject2D.h"

#include "ObjectSystem/ace.CoreLayer.h"

#include "ObjectSystem/2D/ace.CoreLayer2D.h"

#include "ObjectSystem/3D/ace.CoreObject3D.h"
#include "ObjectSystem/3D/ace.CoreModelObject3D.h"
#include "ObjectSystem/3D/ace.CoreDirectionalLightObject3D.h"
#include "ObjectSystem/3D/ace.CoreCameraObject3D.h"
#include "ObjectSystem/3D/ace.CoreEffectObject3D.h"
#include "ObjectSystem/3D/ace.CoreLayer3D.h"

#include "ObjectSystem/ace.CoreScene.h"
#include "ObjectSystem/PostEffect/ace.CorePostEffect.h"
#include "ObjectSystem/ace.ObjectSystemFactory.h"

#include "Core/ace.Core_Imp.h"

#include "Core/ace.CreateCore.h"

#include "ace.Accessor.h"

%}

//-----------------------------------------------------------------------------------
// csharp
//-----------------------------------------------------------------------------------
%include "arrays_csharp.i"
%include "wchar.i"
%include "stdint.i"
%include "std_vector.i"
%include "std_string.i"
%include "std_wstring.i"

// 全OS共通でwchar_t扱い
namespace ace {
typedef wchar_t achar;
typedef std::wstring astring;
}

// swig上ではなし
#define ACE_DLLEXPORT 
#define ACE_STDCALL 

// セキュリティチェックを外して高速化
%pragma(csharp) imclassclassmodifiers="
[System.Security.SuppressUnmanagedCodeSecurity]
unsafe class"

// 全てのclass を unsafe partial class に変更
%typemap(csclassmodifiers) SWIGTYPE "unsafe partial class"

%pragma(csharp) moduleclassmodifiers="unsafe class"

// csharp void* の定義
%typemap(ctype) void * "void *"
%typemap(imtype) void * "IntPtr"
%typemap(cstype) void * "IntPtr"
%typemap(in) void * { $1 = $input; }
%typemap(out) void * { $result = $1; }
%typemap(csin) void * "$csinput"
%typemap(csout) void * { return $imcall; }
%typemap(csvarin) void * "set { $imcall; }"
%typemap(csvarout) void * "get { return $imcall; }" 



//-----------------------------------------------------------------------------------
// 構造体定義
//-----------------------------------------------------------------------------------
%define STRUCT_OBJECT( CTYPE, RCTYPE, CSTYPE )
%ignore CTYPE;

// 一切何も付いていないときの処理がおかしい可能性あり
%typemap(ctype)		CTYPE	"RCTYPE"
%typemap(imtype)	CTYPE	"CSTYPE"
%typemap(cstype)	CTYPE	"CSTYPE"
%typemap(in)		CTYPE	{ assert(sizeof(CTYPE)==sizeof(RCTYPE)); memcpy(&$1, &$input, sizeof(RCTYPE)); }
%typemap(out)		CTYPE	{ assert(sizeof(CTYPE)==sizeof(RCTYPE)); memcpy(&$result, &$1, sizeof(RCTYPE)); }
%typemap(csin)		CTYPE	"$csinput"
%typemap(csout)		CTYPE	{ return $imcall; }
%typemap(csvarin)	CTYPE	{ set { $imcall; } }
%typemap(csvarout)	CTYPE	{ get { return $imcall; } } 

%typemap(ctype)		CTYPE* "void*"
%typemap(imtype)	CTYPE* "ref CSTYPE"
%typemap(cstype)	CTYPE* "ref CSTYPE"
%typemap(in)		CTYPE* "$1 = (CTYPE*)$input;"
%typemap(csin)		CTYPE* "ref $csinput"


%typemap(ctype)		const CTYPE* "void*"
%typemap(imtype)	const CTYPE* "ref CSTYPE"
%typemap(cstype)	const CTYPE* "ref CSTYPE"
%typemap(in)		const CTYPE* "$1 = (CTYPE*)$input;"
%typemap(csin)		const CTYPE* "ref $csinput"

%typemap(ctype)		CTYPE& "void*"
%typemap(imtype)	CTYPE& "ref CSTYPE"
%typemap(cstype)	CTYPE& "ref CSTYPE"
%typemap(in)		CTYPE& "$1 = (CTYPE*)$input;"
%typemap(csin)		CTYPE& "ref $csinput"

%typemap(ctype)		const CTYPE& "void*"
%typemap(imtype)	const CTYPE& "ref CSTYPE"
%typemap(cstype)	const CTYPE& "ref CSTYPE"
%typemap(in)		const CTYPE& "$1 = (CTYPE*)$input;"
%typemap(csin)		const CTYPE& "ref $csinput"
%enddef

//-----------------------------------------------------------------------------------
// 構造体定義
//-----------------------------------------------------------------------------------
STRUCT_OBJECT( ace::Vector2DF, ace::Vector2DF_R, ace.Vector2DF )
STRUCT_OBJECT( ace::Vector2DI, ace::Vector2DI_R, ace.Vector2DI )
STRUCT_OBJECT( ace::Vector3DF, ace::Vector3DF_R, ace.Vector3DF )
STRUCT_OBJECT( ace::Vector4DF, ace::Vector4DF_R, ace.Vector4DF )
STRUCT_OBJECT( ace::RectI, ace::RectI_R, ace.RectI )
STRUCT_OBJECT( ace::RectF, ace::RectF_R, ace.RectF )
STRUCT_OBJECT( ace::Matrix33, ace::Matrix33_R, ace.Matrix33 )
STRUCT_OBJECT( ace::Matrix44, ace::Matrix44_R, ace.Matrix44 )
STRUCT_OBJECT( ace::FCurveKeyframe, ace::FCurveKeyframe_R, ace.FCurveKeyframe )
STRUCT_OBJECT( ace::TextureLockInfomation, ace::TextureLockInfomation_R, ace.TextureLockInfomation )

STRUCT_OBJECT( ace::Color, ace::Color_R, ace.Color )

%template(ShaderVariablePropertyVector) std::vector<ace::ShaderVariableProperty>;

//-----------------------------------------------------------------------------------
// Dispose無視
//-----------------------------------------------------------------------------------
%define DISABLE_DISPOSE( SWIGTYPE )
%typemap(csdestruct, methodname="Dispose", methodmodifiers="public") SWIGTYPE
{
	lock(this)
	{
		GC.SuppressFinalize(this);
	}
}

%typemap(csdestruct_derived, methodname="Dispose", methodmodifiers="public") SWIGTYPE
{
	lock(this)
	{
		GC.SuppressFinalize(this);
	}
}

%enddef

//-----------------------------------------------------------------------------------
// IReference,ReferenceObject向け拡張
//-----------------------------------------------------------------------------------
%typemap(csout) int ace::IReference::Release()
%{
{
	int result = $imcall;
	swigCMemOwn = false;
	swigCPtr = new HandleRef(null, IntPtr.Zero);
	return result;
}
%}

%typemap(csout) int ace::ReferenceObject::Release()
%{
{
	int result = $imcall;
	swigCMemOwn = false;
	swigCPtr = new HandleRef(null, IntPtr.Zero);
	return result;
}
%}

DISABLE_DISPOSE( ace::IReference )
DISABLE_DISPOSE( ace::ReferenceObject )

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
%define CPP_OBJECT( CTYPE )
/* 未開放バグが怖いが、ラッパークラスとswigのクラスのGCが同時に動作したときに、swigのクラスのGCを止める手段がないため */
DISABLE_DISPOSE( CTYPE )
%typemap(cscode) CTYPE
%{
    public IntPtr GetPtr()
    {
    return  swigCPtr.Handle;
    }
%}
%enddef

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
CPP_OBJECT( ace::CoreScene )
CPP_OBJECT( ace::CoreScene_Imp )
CPP_OBJECT( ace::CoreLayer )
CPP_OBJECT( ace::CoreLayer_Imp )

CPP_OBJECT( ace::CoreLayer2D )
CPP_OBJECT( ace::CoreLayer2D_Imp )
CPP_OBJECT( ace::CoreObject2D )
CPP_OBJECT( ace::CoreObject2D_Imp )
CPP_OBJECT( ace::CoreTextureObject2D )
CPP_OBJECT( ace::CoreTextureObject2D_Imp )
CPP_OBJECT( ace::CoreCameraObject2D )
CPP_OBJECT( ace::CoreCameraObject2D_Imp )

CPP_OBJECT( ace::CoreObject3D )
CPP_OBJECT( ace::CoreModelObject3D )
CPP_OBJECT( ace::CoreDirectionalLightObject3D )
CPP_OBJECT( ace::CoreCameraObject3D )
CPP_OBJECT( ace::CoreLayer3D )

CPP_OBJECT( ace::CorePostEffect )
CPP_OBJECT( ace::CorePostEffect_Imp )

CPP_OBJECT( ace::SoundSource )

CPP_OBJECT( ace::Texture )
CPP_OBJECT( ace::Texture2D )
CPP_OBJECT( ace::Texture2D_Imp )
CPP_OBJECT( ace::RenderTexture2D )
CPP_OBJECT( ace::RenderTexture2D_Imp )
CPP_OBJECT( ace::CubemapTexture )
CPP_OBJECT( ace::Material2D )
CPP_OBJECT( ace::Shader2D )
CPP_OBJECT( ace::Shader2D_Imp )

CPP_OBJECT( ace::Effect )

CPP_OBJECT( ace::Mesh )
CPP_OBJECT( ace::Deformer )
CPP_OBJECT( ace::Model )
CPP_OBJECT( ace::KeyframeAnimation )
CPP_OBJECT( ace::AnimationSource )
CPP_OBJECT( ace::AnimationClip )

CPP_OBJECT( ace::Profiler )
CPP_OBJECT( ace::Profiler_Imp )
CPP_OBJECT( ace::Log )
CPP_OBJECT( ace::Log_Imp )

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
%newobject ace::Core::CreateCore;

%newobject ace::Graphics_Imp::CreateTexture2D_Imp;
%newobject ace::Graphics_Imp::CreateRenderTexture2D_Imp;
%newobject ace::Graphics_Imp::CreateCubemapTexture2D_;

%newobject ace::Graphics_Imp::CreateShader2D_Imp;
%newobject ace::Graphics_Imp::CreateMaterial2D_;
%newobject ace::Graphics_Imp::CreateMesh_;
%newobject ace::Graphics_Imp::CreateDeformer_;
%newobject ace::Graphics_Imp::CreateModel_;

%newobject ace::ObjectSystemFactory::CreateObject2D;
%newobject ace::ObjectSystemFactory::CreateTextureObject2D;
%newobject ace::ObjectSystemFactory::CreateLayer2D;

%newobject ace::ObjectSystemFactory::CreateModelObject3D;
%newobject ace::ObjectSystemFactory::CreateCameraObject3D;
%newobject ace::ObjectSystemFactory::CreateDirectionalLightObject3D;
%newobject ace::ObjectSystemFactory::CreateLayer3D;

%newobject ace::ObjectSystemFactory::CreateScene;
%newobject ace::ObjectSystemFactory::CreatePostEffect;

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace ace
{
	struct Vector2DF;
	struct Vector2DI;
	struct Vector3DF;
	struct Vector4DF;
	struct Color;
	struct Matrix33;
	struct Matrix44;
	struct RectI;
	struct RectF;

	struct FCurveKeyframe;
}

%include "ace_cpp/common/Graphics/ace.Graphics.Common.h"

%include "ace_cpp/core/ace.Core.Base.h"
%include "ace_cpp/core/ace.ReferenceObject.h"

%include "ace_cpp/core/Window/ace.Window.h"
%include "ace_cpp/core/Window/ace.Window_Imp.h"
%include "ace_cpp/core/Log/ace.Log.h"
%include "ace_cpp/core/Log/ace.Log_Imp.h"
%include "ace_cpp/core/Profiler/ace.Profiler.h"
%include "ace_cpp/core/Profiler/ace.Profiler_Imp.h"
%include "ace_cpp/core/Input/ace.IMouseButtonState.h"
%include "ace_cpp/core/Input/ace.IMouseWheelableButtonState.h"
%include "ace_cpp/core/Input/ace.MiddleButton.h"
%include "ace_cpp/core/Input/ace.SideButton.h"
%include "ace_cpp/core/Input/ace.Mouse.h"
%include "ace_cpp/core/Input/ace.Mouse_Imp.h"
%include "ace_cpp/core/Input/ace.Keyboard.h"
%include "ace_cpp/core/Input/ace.Keyboard_Imp.h"
%include "ace_cpp/core/Input/ace.Joystick.h"
%include "ace_cpp/core/Input/ace.Joystick_Imp.h"
%include "ace_cpp/core/Input/ace.JoystickContainer.h"
%include "ace_cpp/core/Input/ace.JoystickContainer_Imp.h"
%include "ace_cpp/core/Input/ace.JoystickContainer_Imp.h"

%include "ace_cpp/core/Sound/ace.SoundSource.h"
%include "ace_cpp/core/Sound/ace.Sound.h"

%include "ace_cpp/core/Graphics/Common/Resource/ace.Shader2D.h"
%include "ace_cpp/core/Graphics/Common/Resource/ace.Shader2D_Imp.h"

%include "ace_cpp/core/Graphics/Common/Resource/ace.Material2D.h"

%include "ace_cpp/core/Graphics/Common/Resource/ace.Texture.h"
%include "ace_cpp/core/Graphics/Common/Resource/ace.Texture2D.h"
%include "ace_cpp/core/Graphics/Common/Resource/ace.Texture2D_Imp.h"
%include "ace_cpp/core/Graphics/Common/Resource/ace.RenderTexture2D.h"
%include "ace_cpp/core/Graphics/Common/Resource/ace.RenderTexture2D_Imp.h"
%include "ace_cpp/core/Graphics/Common/Resource/ace.CubemapTexture.h"

%include "ace_cpp/core/Graphics/Common/Resource/ace.Effect.h"

%include "ace_cpp/core/Graphics/Common/3D/ace.Deformer.h"
%include "ace_cpp/core/Graphics/Common/3D/ace.Mesh.h"
%include "ace_cpp/core/Graphics/Common/3D/ace.Model.h"

%include "ace_cpp/core/Graphics/Common/Animation/ace.KeyframeAnimation.h"
%include "ace_cpp/core/Graphics/Common/Animation/ace.AnimationSource.h"
%include "ace_cpp/core/Graphics/Common/Animation/ace.AnimationClip.h"
%include "ace_cpp/core/Graphics/Common/Animation/ace.AnimationSystem.h"

%include "ace_cpp/core/Graphics/Common/ace.Graphics.h"
%include "ace_cpp/core/Graphics/Common/ace.Graphics_Imp.h"

%include "ace_cpp/core/ObjectSystem/ace.eChildMode.h"
%include "ace_cpp/core/ObjectSystem/2D/ace.CoreObject2D.h"
%include "ace_cpp/core/ObjectSystem/2D/ace.CoreTextureObject2D.h"
%include "ace_cpp/core/ObjectSystem/2D/ace.CoreCameraObject2D.h"

%include "ace_cpp/core/ObjectSystem/ace.CoreLayer.h"

%include "ace_cpp/core/ObjectSystem/2D/ace.CoreLayer2D.h"

%include "ace_cpp/core/ObjectSystem/3D/ace.CoreObject3D.h"
%include "ace_cpp/core/ObjectSystem/3D/ace.CoreModelObject3D.h"
%include "ace_cpp/core/ObjectSystem/3D/ace.CoreDirectionalLightObject3D.h"
%include "ace_cpp/core/ObjectSystem/3D/ace.CoreCameraObject3D.h"
%include "ace_cpp/core/ObjectSystem/3D/ace.CoreEffectObject3D.h"
%include "ace_cpp/core/ObjectSystem/3D/ace.CoreLayer3D.h"

%include "ace_cpp/core/ObjectSystem/ace.CoreScene.h"
%include "ace_cpp/core/ObjectSystem/PostEffect/ace.CorePostEffect.h"
%include "ace_cpp/core/ObjectSystem/ace.ObjectSystemFactory.h"

%include "ace_cpp/core/Core/ace.Core.h"
%include "ace_cpp/core/Core/ace.Core_Imp.h"

%include "ace_cpp/core/Core/ace.CreateCore.h"

%include "ace_cpp/core/ace.Accessor.h"

