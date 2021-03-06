﻿#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "../../ace.Core.Base.h"
#include "../../ace.Core.Base_Imp.h"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace ace{
	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	class Graphics_Imp_GL;
	class Texture2D_Imp_GL;
	class NativeShader_Imp_GL;

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#ifdef _DEBUG
#define GLCheckError()		{ int __code = glGetError(); if(__code != GL_NO_ERROR) { printf("GLError filename = %s , line = %d, error = %s\n", __FILE__, __LINE__, (const char*)gluErrorString(__code) ); }  }
#else
#define GLCheckError()
#endif