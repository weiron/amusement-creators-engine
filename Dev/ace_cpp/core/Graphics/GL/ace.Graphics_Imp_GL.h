﻿#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "../Common/ace.Graphics_Imp.h"
#include "ace.GL.Base.h"

#include <mutex>

#if !_WIN32
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#endif

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace ace {
	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
#if !SWIG
	class GraphicsHelper_GL
	{
	public:
		static void LoadTexture(Graphics_Imp_GL* graphics, void* imgdata, int32_t width, int32_t height, GLuint& texture);
	};
#endif

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	class Graphics_Imp_GL
		: public Graphics_Imp
	{
	private:
		Window*			m_window;
		
		GLuint			m_frameBuffer_main;
		GLuint			m_frameBuffer_rendering;

		bool			m_endStarting;
#if !_WIN32
		bool			m_x11Mode = false;
		GLXContext		m_glx;
		Display*		m_x11Display;
		::Window		m_x11Window;
#endif

#if _WIN32
		HDC				m_renderingThreadDC;
		HGLRC			m_renderingThreadRC;
		HWND			m_renderingThreadHWND;
#else
		GLXContext		m_renderingThreadGlx;
		Display*		m_renderingThreadX11Display;
		::Window		m_renderingThreadX11Window;
#endif
		/**
			@brief		コンテキストの状態
			@note
			0-コンテキストなし
			1-メインスレッド
			2-描画スレッド
		*/
		int32_t			m_contextState;

		std::recursive_mutex		m_mutex;

		Graphics_Imp_GL(Vector2DI size, ::ace::Window* window, Log* log, bool isMultithreadingMode);

		Graphics_Imp_GL(Vector2DI size, void* display, void* window, void* context, Log* log, bool isMultithreadingMode);

		virtual ~Graphics_Imp_GL();

		static void WriteInitializedLog(Log* log);
		static void WriteDeviceInformation(Log* log);

	protected:
		void StartRenderingThread() override;
		void EndRenderingThread() override;

		VertexBuffer_Imp* CreateVertexBuffer_Imp_(int32_t size, int32_t count, bool isDynamic);
		IndexBuffer_Imp* CreateIndexBuffer_Imp_(int maxCount, bool isDynamic, bool is32bit);
		NativeShader_Imp* CreateShader_Imp_(
			const char* vertexShaderText,
			const char* vertexShaderFileName,
			const char* pixelShaderText,
			const char* pixelShaderFileName,
			std::vector <VertexLayout>& layout,
			std::vector <Macro>& macro);

		void UpdateStatus(VertexBuffer_Imp* vertexBuffer, IndexBuffer_Imp* indexBuffer, NativeShader_Imp* shaderPtr);
		void DrawPolygonInternal(int32_t count, VertexBuffer_Imp* vertexBuffer, IndexBuffer_Imp* indexBuffer, NativeShader_Imp* shaderPtr);
		void DrawPolygonInstancedInternal(int32_t count, VertexBuffer_Imp* vertexBuffer, IndexBuffer_Imp* indexBuffer, NativeShader_Imp* shaderPtr, int32_t instanceCount);

		void BeginInternal();
		void EndInternal();

		void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);

	public:
		
		static Graphics_Imp_GL* Create(::ace::Window* window, Log* log, bool isMultithreadingMode);

#if !_WIN32
		static Graphics_Imp_GL* Create_X11(void* display, void* window, int32_t width, int32_t height, Log* log, bool isMultithreadingMode);
#endif

		Texture2D_Imp* CreateTexture2D_Imp_Internal(Graphics* graphics, uint8_t* data, int32_t size);
		Texture2D_Imp* CreateEmptyTexture2D_Imp_Internal(Graphics* graphics, int32_t width, int32_t height, eTextureFormat format) override;
		RenderTexture2D_Imp* CreateRenderTexture2D_Imp(int32_t width, int32_t height, eTextureFormat format);

		CubemapTexture* CreateCubemapTextureFrom6ImageFiles_(const achar* front, const achar* left, const achar* back, const achar* right, const achar* top, const achar* bottom) override;

		DepthBuffer_Imp* CreateDepthBuffer_Imp(int32_t width, int32_t height);

		void SetRenderTarget(RenderTexture2D_Imp* texture, DepthBuffer_Imp* depthBuffer);

	public:
		void Clear(bool isColorTarget, bool isDepthTarget, const Color& color);

		void Present();

		void SaveScreenshot(const achar* path);

		bool SaveTexture(const achar* path, GLuint texture, Vector2DI size);

		eGraphicsType GetGraphicsType() const { return GRAPHICS_TYPE_GL; }

		/**
			@brief	現状のスレットに対応したコンテキストを設定する。
		*/
		void MakeContextCurrent() override;

		/**
		@brief	コンテキストを解除する。
		*/
		void MakeContextNone();

		void FlushCommand() override;

		/**
			@brief	制御用のミューテックスを取得する。
			@return	ミューテックス
		*/
		std::recursive_mutex& GetMutex(){ return m_mutex; }
	private:

		/**
		@brief	描画スレッド用にコンテキストを生成する。(描画スレッド生成前)
		@param	window	ウインドウ
		*/
		void CreateContextBeforeThreading(GLFWwindow* window);

		/**
			@brief	描画スレッド用にコンテキストを生成する。(描画スレッド上)
			@param	window	ウインドウ
		*/
		void CreateContextOnThread(GLFWwindow* window);

		/**
		@brief	描画スレッド用にコンテキストを生成する。(描画スレッド生成後)
		@param	window	ウインドウ
		*/
		void CreateContextAfterThreading(GLFWwindow* window);

		/**
			@brief	フレームバッファをバインドする。
			@note
			フレームバッファはコンテキスト間で共有できないため、スレッドに応じて切り替えている。
		*/
		void BindFramebuffer();

		/**
			@brief	フレームバッファをアンバインドする。
		*/
		void UnbindFramebuffer();
	};

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
}
