#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
#include "Framework/Factory.h"

namespace bunny {
	class SpriteComponent : public RenderComponent {
	public:
		CLASS_DECLARATION(SpriteComponent)

		void Update(float dt) override;
		void Draw(class Renderer& r) override;
		virtual float getRadius() { return m_texture->GetSize().Length() * 0.5f; }

		res_t<Texture> m_texture;
	};
}