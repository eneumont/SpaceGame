#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
#include "Framework/Factory.h"

namespace bunny {
	class SpriteComponent : public RenderComponent {
	public:
		CLASS_DECLARATION(SpriteComponent)

		bool Initialize() override;
		void Update(float dt) override;
		void Draw(class Renderer& r) override;

		Rect source;
		bool flipH = false;
		vec2 origin{ 0.5f, 0.5f };

		std::string textureName;
		res_t<Texture> m_texture;
	};
}