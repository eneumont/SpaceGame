#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"

namespace bunny {
	CLASS_DEFINITION(SpriteComponent)

	bool SpriteComponent::Initialize() {
		if (!textureName.empty()) m_texture = GET_RESOURCE(Texture, textureName, g_r);

		return true;
	}

	void SpriteComponent::Update(float dt) {
	
	}

	void SpriteComponent::Draw(Renderer& r) {
		r.DrawTexture(m_texture.get(), m_owner->transform);
	}

	void SpriteComponent::Read(const json_t& value) {
		READ_DATA(value, textureName);
	}
}
