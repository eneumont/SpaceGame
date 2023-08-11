#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Components/CollisionComponent.h"
#include "Framework/Components/RenderComponent.h"

void Weapon::Update(float dt) {
	Actor::Update(dt);

	bunny::vec2 forward = bunny::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * kiko::g_time.GetDelta();
	m_transform.position.x = bunny::Wrap(m_transform.position.x, (float)bunny::g_r.GetWidth());
	m_transform.position.y = bunny::Wrap(m_transform.position.y, (float)bunny::g_r.GetHeight());
}

void Weapon::onCollision(Actor* actor) {
	if (actor->m_tag != m_tag) {
		m_lifespan = 0;
	}
}

bool Weapon::Initialize() {
	Actor::Initialize();

	auto collisionComponent = GetComponent<bunny::CollisionComponent>();

	if (collisionComponent) {
		auto renderComponent = GetComponent<bunny::RenderComponent>();
		if (renderComponent) {
			float scale = m_transform.scale;
			collisionComponent->m_radius = renderComponent->getRadius() * scale;
		}
	}

	return true;
}
