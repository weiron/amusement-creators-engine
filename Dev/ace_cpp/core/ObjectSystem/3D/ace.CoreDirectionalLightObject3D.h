﻿
#pragma once

#include "ace.CoreObject3D.h"

#include <Graphics/ace.Color.h>

namespace ace
{
	class CoreDirectionalLightObject3D
		: public CoreObject3D
	{
	protected:
		CoreDirectionalLightObject3D(){}
		virtual ~CoreDirectionalLightObject3D(){}

	public:
		virtual Color GetColor() = 0;
		virtual void SetColor(const Color& color) = 0;
	};
}
