#pragma once
#include "Component.h"

namespace bunny {
	class RenderComponent : public Component {
	public:
		virtual void Draw(class Renderer& r) = 0;
		virtual float getRadius() { return 0; }
	};
}
