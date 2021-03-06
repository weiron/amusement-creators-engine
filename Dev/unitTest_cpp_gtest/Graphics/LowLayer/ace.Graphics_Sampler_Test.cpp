﻿
#include "../ace.Graphics_Test_Utls.h"

static const char* dx_vs = R"(
struct VS_Input
{
	float3 Pos		: Pos0;
	float2 UV		: UV0;
};

struct VS_Output
{
	float4 Pos		: SV_POSITION;
	float2 UV		: TEXCOORD0;
};

VS_Output main( const VS_Input Input )
{
	VS_Output Output = (VS_Output)0;
	Output.Pos = float4( Input.Pos.x, Input.Pos.y, Input.Pos.z, 1.0 );
	Output.UV = Input.UV;
	return Output;
}

)";

static const char* dx_ps = R"(

Texture2D		g_texture		: register( t0 );
SamplerState	g_sampler		: register( s0 );


struct PS_Input
{
	float4 Pos		: SV_POSITION;
	float2 UV		: TEXCOORD0;
};


float4 main( const PS_Input Input ) : SV_Target
{
	float4 Output = g_texture.Sample(g_sampler, Input.UV);
	if(Output.a == 0.0f) discard;
	return Output;
}

)";

static const char* gl_vs = R"(

attribute vec3 Pos;
attribute vec2 UV;

varying vec4 vaTexCoord;

void main()
{
	gl_Position = vec4(Pos.x,Pos.y,Pos.z,1.0);
	vaTexCoord = vec4(UV.x,UV.y,0.0,0.0);
}

)";

static const char* gl_ps = R"(

varying vec4 vaTexCoord;
uniform sampler2D g_texture;

void main() 
{
	// varying(in) は変更不可(Radeon)

	vec4 uv = vaTexCoord;
	uv.y = 1.0 - uv.y; 
	gl_FragColor = texture2D(g_texture, uv.xy);
}

)";

struct Vertex
{
	ace::Vector3DF Pos;
	ace::Vector2DF UV;

	Vertex() {}
	Vertex(ace::Vector3DF pos, ace::Vector2DF uv)
	{
		Pos = pos;
		UV = uv;
	}
};

void Graphics_Sampler(bool isOpenGLMode)
{
	StartGraphicsTest();
	SetGLEnable(isOpenGLMode);

	ace::Log* log = ace::Log_Imp::Create(L"graphics.html", L"描画");
	
	auto window = ace::Window_Imp::Create(640, 480, ace::ToAString(L"SingleTexture").c_str());
	ASSERT_TRUE(window != nullptr);

	auto graphics = ace::Graphics_Imp::Create(window, isOpenGLMode, log, false);
	ASSERT_TRUE(graphics != nullptr);

	auto texture = graphics->CreateTexture2D(ace::ToAString(L"Data/Texture/Sampler.png").c_str());
	ASSERT_TRUE(texture != nullptr);

	auto vertexBuffer = graphics->CreateVertexBuffer_Imp(sizeof(Vertex), 4, false);
	ASSERT_TRUE(vertexBuffer != nullptr);

	auto indexBuffer = graphics->CreateIndexBuffer_Imp(6, false, false);
	ASSERT_TRUE(indexBuffer != nullptr);
	
	std::vector<ace::VertexLayout> vl;
	vl.push_back(ace::VertexLayout("Pos", ace::LAYOUT_FORMAT_R32G32B32_FLOAT));
	vl.push_back(ace::VertexLayout("UV", ace::LAYOUT_FORMAT_R32G32_FLOAT));

	std::shared_ptr<ace::NativeShader_Imp> shader;
	std::vector<ace::Macro> macro;
	if (isOpenGLMode)
	{
		shader = graphics->CreateShader_Imp(
			gl_vs,
			"vs",
			gl_ps,
			"ps",
			vl,
			macro);
	}
	else
	{
		shader = graphics->CreateShader_Imp(
			dx_vs,
			"vs",
			dx_ps,
			"ps",
			vl,
			macro);
	}
	
	ASSERT_TRUE(shader != nullptr);
	
	{
		vertexBuffer->Lock();
		auto vb = vertexBuffer->GetBuffer<Vertex>(4);
		vb[0] = Vertex(ace::Vector3DF(-1.0f, 1.0f, 0.5f), ace::Vector2DF(0.0f, 0.0f));
		vb[1] = Vertex(ace::Vector3DF(0.5f, 1.0f, 0.5f), ace::Vector2DF(2.0f, 0.0f));
		vb[2] = Vertex(ace::Vector3DF(0.5f, -1.0f, 0.5f), ace::Vector2DF(2.0f, 2.0f));
		vb[3] = Vertex(ace::Vector3DF(-1.0f, -1.0f, 0.5f), ace::Vector2DF(0.0f, 2.0f));
		vertexBuffer->Unlock();
	}
	
	{
		indexBuffer->Lock();
		auto ib = indexBuffer->GetBuffer<uint16_t>(6);
		ib[0] = 0;
		ib[1] = 1;
		ib[2] = 2;
		ib[3] = 0;
		ib[4] = 2;
		ib[5] = 3;
		indexBuffer->Unlock();
	}

	shader->SetTexture("g_texture", texture.get(), 0);

	int32_t time = 0;
	while (window->DoEvent())
	{
		auto draw = [&](uint8_t r, uint8_t g, uint8_t b, uint8_t a, ace::eTextureFilterType filter, ace::eTextureWrapType wrap, ace::eAlphaBlend alphaBlend) -> void
		{
			graphics->Clear(true, false, ace::Color(r,g,b,a));
			graphics->SetVertexBuffer(vertexBuffer.get());
			graphics->SetIndexBuffer(indexBuffer.get());
			graphics->SetShader(shader.get());
		
			auto& state = graphics->GetRenderState()->Push();
			state.DepthTest = false;
			state.DepthWrite = false;
			state.TextureFilterTypes[0]=filter;
			state.TextureWrapTypes[0]=wrap;
			state.AlphaBlend=alphaBlend;
			graphics->GetRenderState()->Update(false);
			graphics->DrawPolygon(2);
			graphics->GetRenderState()->Pop();
		};

		graphics->Begin();

		if( time < 4  )
		{
			draw( 100, 10, 10, 255,
				ace::eTextureFilterType:: TEXTURE_FILTER_LINEAR,
				ace::eTextureWrapType::TEXTURE_WRAP_REPEAT,
				ace::eAlphaBlend::ALPHA_BLEND_BLEND );
		}
		else if (time  < 8)
		{
			draw( 10, 100, 10, 255,
				ace::eTextureFilterType::TEXTURE_FILTER_NEAREST,
				ace::eTextureWrapType::TEXTURE_WRAP_REPEAT,
				ace::eAlphaBlend::ALPHA_BLEND_ADD);
		}
		else if (time < 12)
		{
			draw(200, 100, 100, 255,
				ace::eTextureFilterType::TEXTURE_FILTER_LINEAR,
				ace::eTextureWrapType::TEXTURE_WRAP_CLAMP,
				ace::eAlphaBlend::ALPHA_BLEND_SUB);
		}
		else if (time < 16)
		{
			draw(100, 200, 100, 255,
				ace::eTextureFilterType::TEXTURE_FILTER_NEAREST,
				ace::eTextureWrapType::TEXTURE_WRAP_CLAMP,
				ace::eAlphaBlend::ALPHA_BLEND_MUL);
		}
		else if (time < 20)
		{
			draw(10, 10, 100, 255,
				ace::eTextureFilterType::TEXTURE_FILTER_LINEAR,
				ace::eTextureWrapType::TEXTURE_WRAP_CLAMP,
				ace::eAlphaBlend::ALPHA_BLEND_OPACITY);
		}

		graphics->Present();

		graphics->End();

		if (time == 2)
		{
			SAVE_SCREEN_SHOT(graphics,0);
		}

		if (time == 6)
		{
			SAVE_SCREEN_SHOT(graphics, 1);
		}

		if (time == 10)
		{
			SAVE_SCREEN_SHOT(graphics, 2);
		}

		if (time == 14)
		{
			SAVE_SCREEN_SHOT(graphics, 3);
		}

		if (time == 18)
		{
			SAVE_SCREEN_SHOT(graphics, 4);
		}

		if (time == 20)
		{
			window->Close();
		}
		time++;
	}

	graphics->Release();
	texture.reset();
	vertexBuffer.reset();
	indexBuffer.reset();
	shader.reset();

	window->Release();
	delete log;
}

TEST(Graphics, Sampler_DX)
{
	Graphics_Sampler(false);
}

TEST(Graphics, Sampler_GL)
{
	Graphics_Sampler(true);
}

