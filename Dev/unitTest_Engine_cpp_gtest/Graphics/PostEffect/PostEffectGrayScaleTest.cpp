﻿#include <ace.h>
#include <gtest/gtest.h>
#include <memory>
#include "../../EngineTest.h"


class Graphics_PostEffectGrayScale : public EngineTest
{
public:
	float intensity;
	Graphics_PostEffectGrayScale(bool isOpenGLMode) :
		EngineTest(ace::ToAString("PostEffectGrayScale"), isOpenGLMode, 10)
	{}
protected:
	void OnStart() override
	{

		auto scene = std::make_shared<ace::Scene>();
		auto layer = std::make_shared<ace::Layer2D>();
		auto object = std::make_shared<ace::TextureObject2D>();
		scene->AddLayer(layer);
		layer->AddObject(object);
		ace::Engine::ChangeScene(scene);

		auto g = ace::Engine::GetGraphics();
		auto texture = g->CreateTexture2D(ace::ToAString("Data/Texture/Sample1.png").c_str());
		object->SetTexture(texture);
		object->SetScale(ace::Vector2DF(2, 2));

		auto pe = std::make_shared<ace::PostEffectGrayScale>(g);
		layer->AddPostEffect(pe);
	}
};


TEST(Graphics, PostEffectGrayScale_GL)
{
	Graphics_PostEffectGrayScale(true).Run();
	AssertMemoryDoesntLeak();
}

#if _WIN32
TEST(Graphics, PostEffectGrayScale_DX)
{
	Graphics_PostEffectGrayScale(false).Run();
	AssertMemoryDoesntLeak();
}
#endif

