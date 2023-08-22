#include "Actor.h"
#include "Framework/Components/RenderComponent.h"

namespace bunny {
	CLASS_DEFINITION(Actor)

	Actor::Actor(const Actor& other) {
		name = other.name;
		tag = other.tag;
		lifespan = other.lifespan;
		transform = other.transform;
		m_scene = other.m_scene;
		m_game = other.m_game;

		for (auto& component : other.components) {
			auto cloneComponent = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			AddComponent(std::move(cloneComponent));
		}
	}

	void Actor::Draw(bunny::Renderer& r) {
		for (auto& component : components) {
			if (dynamic_cast<RenderComponent*>(component.get())) {
				dynamic_cast<RenderComponent*>(component.get())->Draw(r);
			}
		}
	}

	void Actor::AddComponent(std::unique_ptr<Component> c) {
		c->m_owner = this;
		components.push_back(std::move(c));
	}

	bool Actor::Initialize() {
		for (auto& component : components) {
			component->Initialize();
		}

		return true;
	}

	void Actor::Destroy() {
		for (auto& component : components) {
			component->Destroy();
		}
	}

	void Actor::Update(float dt) {
		if (lifespan != -1.0f) {
			lifespan -= dt;
			destroyed = (lifespan <= 0);
		}

		for (auto& component : components) {
			component->Update(dt);
		}
	}

	void Actor::Read(const json_t& value) {
		Object::Read(value);

		READ_DATA(value, tag);
		READ_DATA(value, lifespan);
		READ_DATA(value, persistent);
		READ_DATA(value, prototype);
		if (HAS_DATA(value, transform)) transform.Read(GET_DATA(value, transform));

		if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray()) {
			for (auto& componentValue : GET_DATA(value, components).GetArray()) {
				std::string type;
				READ_DATA(componentValue, type);

				auto component = CREATE_CLASS_BASE(Component, type);
				component->Read(componentValue);
				AddComponent(std::move(component));
			}
		}
	}
}
