﻿#include <ace.h>
#include <gtest/gtest.h>
#include <memory>
#include "../EngineTest.h"

using namespace std;
using namespace ace;

class ObjectSystem_Simple : public EngineTest
{
public:
	ObjectSystem_Simple(bool isOpenGLMode)
		: EngineTest(ace::ToAString("Simple"), isOpenGLMode, 30)
	{
	}

protected:
	void OnStart()
	{
		auto scene = make_shared<Scene>();
		auto layer = make_shared<Layer2D>();
		auto object = make_shared<TextureObject2D>();
		auto object2 = make_shared<TextureObject2D>();

		ASSERT_NE(scene, nullptr);
		ASSERT_NE(layer, nullptr);
		ASSERT_NE(object, nullptr);
		ASSERT_NE(object2, nullptr);

		ace::Engine::ChangeScene(scene);
		scene->AddLayer(layer);
		layer->AddObject(object);
		layer->AddObject(object2);

		auto g = ace::Engine::GetGraphics();
		auto texture = g->CreateTexture2D(ace::ToAString("Data/Texture/Cloud1.png").c_str());
		object->SetTexture(texture);
		object2->SetTexture(texture);

		object->SetCenterPosition(Vector2DF(128, 128));
		object->SetAngle(5);
		object->SetPosition(Vector2DF(320, 240));
		object->SetScale(object->GetScale() + Vector2DF(0.5f, 0.5f));
	}
};

TEST(ObjectSystem, Simple_GL)
{
	RunTest<ObjectSystem_Simple>(true);
}

#if _WIN32
TEST(ObjectSystem, Simple_DX)
{
	RunTest<ObjectSystem_Simple>(false);
}
#endif

