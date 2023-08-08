#include "Actor.h"
#include "Framework/Components/RenderComponent.h"

namespace bunny {
	void Actor::Draw(bunny::Renderer& r) {
		//m_model->Draw(r, m_transform);

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

	void Actor::Update(float dt) {
		if (m_lifespan != -1.0f) {
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
		}

		for (auto& component : m_components) {
			component->Update(dt);
		}
	}
}
