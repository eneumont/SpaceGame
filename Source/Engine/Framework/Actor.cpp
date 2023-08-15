#include "Actor.h"
#include "Framework/Components/RenderComponent.h"

namespace bunny {
	CLASS_DEFINITION(Actor)

	void Actor::Draw(bunny::Renderer& r) {
		for (auto& component : m_components) {
			if (dynamic_cast<RenderComponent*>(component.get())) {
				dynamic_cast<RenderComponent*>(component.get())->Draw(r);
			}
		}
	}

	void Actor::AddComponent(std::unique_ptr<Component> c) {
		c->m_owner = this;
		m_components.push_back(std::move(c));
	}

	bool Actor::Initialize() {
		for (auto& component : m_components) {
			component->Initialize();
		}

		return true;
	}

	void Actor::Destroy() {
		for (auto& component : m_components) {
			component->Destroy();
		}
	}

	void Actor::Update(float dt) {
		if (m_lifespan != -1.0f) {
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
		}

		for (auto& component : m_components) {
			component->Update(dt);
		}
	}

	bool Actor::Read(const rapidjson::Value& value) {
		return true;
	}
}
