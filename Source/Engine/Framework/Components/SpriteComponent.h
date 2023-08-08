#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"

namespace bunny {
	class SpriteComponent : public RenderComponent {
	public:
		void Update(float dt) override;
		void Draw(class Renderer& r) override;

		res_t<Texture> m_texture;
	};
}