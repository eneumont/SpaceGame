#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace bunny {
	CLASS_DEFINITION(SpriteComponent)

	void SpriteComponent::Update(float dt) {
	
	}

	void SpriteComponent::Draw(Renderer& r) {
		r.DrawTexture(m_texture.get(), m_owner->m_transform);
	}
}
