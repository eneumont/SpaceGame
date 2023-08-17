#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

namespace bunny {
	void Weapon::Update(float dt) {
		bunny::vec2 forward = bunny::vec2{ 0, -1 }.Rotate(transform.rotation);
		transform.position += forward * speed * kiko::g_time.GetDelta();
		transform.position.x = bunny::Wrap(transform.position.x, (float)bunny::g_r.GetWidth());
		transform.position.y = bunny::Wrap(transform.position.y, (float)bunny::g_r.GetHeight());
	}

	void Weapon::onCollision(Actor* actor) {
		if (actor->tag != tag) {
			lifespan = 0;
		}
	}

	bool Weapon::Initialize() {
		auto collisionComponent = GetComponent<bunny::CollisionComponent>();

		if (collisionComponent) {
			auto renderComponent = GetComponent<bunny::RenderComponent>();
			if (renderComponent) {
				float scale = transform.scale;
				collisionComponent->m_radius = renderComponent->getRadius() * scale;
			}
		}

		return true;
	}

	void Weapon::Read(const json_t& value) {
		READ_DATA(value, speed);
	}
}
