#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

namespace bunny {
	CLASS_DEFINITION(Weapon);

	void Weapon::Update(float dt) {
		Actor::Update(dt);

		bunny::vec2 forward = bunny::vec2{ 0, -1 }.Rotate(transform.rotation);
		m_physics->SetVelocity(forward * speed);
		transform.position.x = bunny::Wrap(transform.position.x, (float)bunny::g_r.GetWidth());
		transform.position.y = bunny::Wrap(transform.position.y, (float)bunny::g_r.GetHeight());
	}

	void Weapon::onCollisionEnter(Actor* actor) {
		if (actor->tag != tag) {
			lifespan = 0;
		}
	}

	bool Weapon::Initialize() {
		Actor::Initialize();

		m_physics = GetComponent<PhysicsComponent>();

		auto collisionComponent = GetComponent<bunny::CollisionComponent>();
		if (collisionComponent) {
			/*auto renderComponent = GetComponent<bunny::RenderComponent>();
			if (renderComponent) {
				float scale = transform.scale;
				collisionComponent->m_radius = renderComponent->getRadius() * scale;
			}*/
		}

		return true;
	}

	void Weapon::Read(const json_t& value) {
		Actor::Read(value);
		READ_DATA(value, speed);
	}
}
