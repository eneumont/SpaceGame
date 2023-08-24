#include "Enemy.h"
#include "Framework/Scene.h"
#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Player.h"
#include "Game/SpaceGame.h"
#include "Framework/Framework.h"
#include "Framework/Event/EventManager.h"

namespace bunny {
	CLASS_DEFINITION(Enemy)

	void Enemy::Update(float dt) {
		Actor::Update(dt);

		vec2 forward = vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player) {
			Vector2 direction = player->transform.position - transform.position;

			float turnAngle = vec2::SignedAngle(forward, direction.Normalized());

			//transform.rotation += turnAngle * 5 * dt;
			m_physics->ApplyTorque(turnAngle);

			if (std::fabs(turnAngle) < DegreesToRadians(30.0f)) {
				//wah!!!
			}
		}

		m_physics->ApplyForce(forward * m_speed);

		//transform.position += forward * m_speed * 1/*thrust*/ * kiko::g_time.GetDelta();
		transform.position.x = Wrap(transform.position.x, (float)g_r.GetWidth());
		transform.position.y = Wrap(transform.position.y, (float)g_r.GetHeight());

		m_fireTimer -= dt;
		if (m_fireTimer <= 0) {
			m_fireTimer = m_fireRate;
			auto weapon = INSTANTIATE(Weapon, "EnemyBullet");
			weapon->transform = { transform.position, transform.rotation, 2 };
			weapon->Initialize();
			m_scene->Add(std::move(weapon));
		}
	}

	void Enemy::onCollision(Actor* actor) {
		//dynamic_cast<Player*>(actor) could use that for if statement
		//could use != m_tag or == "Player"

		if (actor->tag == "Player") {
			EventManager::Instance().DispatchEvent("AddPoints", 100);
			destroyed = true;

			//create explosion
			EmitterData data;
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
			Transform transformer{ { transform.position }, 0, 1 };
			auto emitter = std::make_unique<Emitter>(transformer, data);
			emitter->lifespan = 0.1f;
			m_scene->Add(std::move(emitter));
		}
	}

	bool Enemy::Initialize() {
		Actor::Initialize();

		m_physics = GetComponent<PhysicsComponent>();
		auto collisionComponent = GetComponent<CollisionComponent>();

		if (collisionComponent) {
			auto renderComponent = GetComponent<RenderComponent>();
			if (renderComponent) {
				float scale = transform.scale;
				collisionComponent->m_radius = renderComponent->getRadius() * scale;
			}
		}

		return true;
	}

	void Enemy::Read(const json_t& value) {
		Actor::Read(value);
		READ_NAME_DATA(value, "speed", m_speed);
		READ_NAME_DATA(value, "turnRate", m_turnRate);
		READ_NAME_DATA(value, "fireRate", m_fireRate);
		READ_NAME_DATA(value, "fireTimer", m_fireTimer);
	}
}