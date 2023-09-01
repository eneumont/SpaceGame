#include "Rock.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

namespace bunny {
	CLASS_DEFINITION(Rock)

	bool Rock::Initialize() {
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

	void Rock::Update(float dt) {
		Actor::Update(dt);

		vec2 forward = vec2{ 1, 0 }.Rotate(transform.rotation);
		m_physics->SetVelocity(forward * speed);
		transform.position.x = Wrap(transform.position.x, (float)g_r.GetWidth());
		transform.position.y = Wrap(transform.position.y, (float)g_r.GetHeight());
	}

	void Rock::onCollisionEnter(Actor* actor) {
		if (actor->tag == "Enemy") {
			lifespan = 0;
		}
	}

	void Rock::Read(const json_t& value) {
		Actor::Read(value);
		READ_DATA(value, speed);
	}
}