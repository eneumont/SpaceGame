#include "Enemy.h"
#include "Framework/Scene.h"
#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Player.h"
#include "Game/SpaceGame.h"
#include "Framework/Framework.h"

void Enemy::Update(float dt) {
	Actor::Update(dt);

	bunny::vec2 forward = bunny::vec2{ 0, -1 }.Rotate(transform.rotation);
	Player* player = m_scene->GetActor<Player>();
	if (player) {
		bunny::Vector2 direction = player->transform.position - transform.position;

		float turnAngle = bunny::vec2::SignedAngle(forward, direction.Normalized());

		transform.rotation += turnAngle * 5 * dt;

		if (std::fabs(turnAngle) < bunny::DegreesToRadians(30.0f)) {
			//wah!!!
		}
	}

	transform.position += forward * m_speed * 1/*thrust*/ * kiko::g_time.GetDelta();
	transform.position.x = bunny::Wrap(transform.position.x, (float)bunny::g_r.GetWidth());
	transform.position.y = bunny::Wrap(transform.position.y, (float)bunny::g_r.GetHeight());

	m_fireTimer -= dt;
	//if (m_fireTimer <= 0) {
	//	m_fireTimer = m_fireRate;
	//	bunny::Transform transformer{ transform.position, transform.rotation, 2 };
	//	std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(300.0f, transformer); //m_transform
	//	weapon->tag = "Enemy";
	//	std::unique_ptr<bunny::SpriteComponent> component = std::make_unique<bunny::SpriteComponent>();
	//	component->m_texture = GET_RESOURCE(bunny::Texture, "ship.png", bunny::g_r);
	//	weapon->AddComponent(std::move(component));
	//	auto collisionComponent = std::make_unique<bunny::CircleCollisionComponent>();
	//	collisionComponent->m_radius = 30.0f;
	//	weapon->AddComponent(std::move(collisionComponent));
	//	weapon->Initialize();
	//	m_scene->Add(std::move(weapon));
	//}
}

void Enemy::onCollision(Actor* actor) {
	//dynamic_cast<Player*>(actor) could use that for if statement
	//could use != m_tag or == "Player"

	if (actor->tag == "Player") {
		m_game->AddPoints(100);
		destroyed = true;

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
		bunny::Transform transformer{ { transform.position }, 0, 1 };
		auto emitter = std::make_unique<bunny::Emitter>(transformer, data);
		emitter->lifespan = 0.1f;
		m_scene->Add(std::move(emitter));
	}
}

bool Enemy::Initialize() {
	Actor::Initialize();

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