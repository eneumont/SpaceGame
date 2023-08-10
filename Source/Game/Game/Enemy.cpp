#include "Enemy.h"
#include "Framework/Scene.h"
#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Player.h"
#include "Game/SpaceGame.h"
#include "Framework/Emitter.h"
#include "Framework/Components/SpriteComponent.h"
#include "Framework/Resource/ResourceManager.h"

void Enemy::Update(float dt) {
	Actor::Update(dt);

	bunny::vec2 forward = bunny::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	Player* player = m_scene->GetActor<Player>();
	if (player) {
		bunny::Vector2 direction = player->m_transform.position - m_transform.position;

		float turnAngle = bunny::vec2::SignedAngle(forward, direction.Normalized());

		m_transform.rotation += turnAngle * 5 * dt;

		if (std::fabs(turnAngle) < bunny::DegreesToRadians(30.0f)) {
			//wah!!!
		}
	}

	m_transform.position += forward * m_speed * 1/*thrust*/ * kiko::g_time.GetDelta();
	m_transform.position.x = bunny::Wrap(m_transform.position.x, (float)bunny::g_r.GetWidth());
	m_transform.position.y = bunny::Wrap(m_transform.position.y, (float)bunny::g_r.GetHeight());

	m_fireTimer -= dt;
	if (m_fireTimer <= 0) {
		m_fireTimer = m_fireRate;
		bunny::Transform transform{ m_transform.position, m_transform.rotation, 2 };
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(300.0f, transform); //m_transform
		weapon->m_tag = "Enemy";
		std::unique_ptr<bunny::SpriteComponent> component = std::make_unique<bunny::SpriteComponent>();
		component->m_texture = bunny::g_rm.Get<bunny::Texture>("ship.png", bunny::g_r);
		weapon->AddComponent(std::move(component));
		m_scene->Add(std::move(weapon));
	}
}

void Enemy::onCollision(Actor* actor) {
	//dynamic_cast<Player*>(actor) could use that for if statement
	//could use != m_tag or == "Player"

	if (actor->m_tag == "Player") {
		m_game->AddPoints(100);
		m_destroyed = true;

		//create explosion
		bunny::EmitterData data;
		data.burst = true;
		data.burstCount = 100;
		data.spawnRate = 200;
		data.angle = 0;
		data.angleRange = bunny::PI;
		data.lifetimeMin = 0.5f;
		data.lifetimeMin = 1.5f;
		data.speedMin = 50;
		data.speedMax = 250;
		data.damping = 0.5f;
		data.color = bunny::Color{ 1, 0, 0, 1 };
		bunny::Transform transform{ { m_transform.position }, 0, 1 };
		auto emitter = std::make_unique<bunny::Emitter>(transform, data);
		emitter->m_lifespan = 0.1f;
		m_scene->Add(std::move(emitter));
	}
}