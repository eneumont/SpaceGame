#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Weapon.h"
#include "Framework/Framework.h"
#include "Game/SpaceGame.h"
#include "Framework/Resource/ResourceManager.h"

bool Player::Initialize() {
	Actor::Initialize();

	m_physics = GetComponent<bunny::PhysicsComponent>();
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

void Player::Update(float dt) {
	Actor::Update(dt);

	//movement
	float rotate = 0;
	if (bunny::g_is.GetKeyDown(SDL_SCANCODE_A) || bunny::g_is.GetKeyDown(SDL_SCANCODE_LEFT)) {
		rotate = -1;
	}

	if (bunny::g_is.GetKeyDown(SDL_SCANCODE_D) || bunny::g_is.GetKeyDown(SDL_SCANCODE_RIGHT)) {
		rotate = 1;
	}
	transform.rotation += rotate * m_turnRate * kiko::g_time.GetDelta();

	float thrust = 0;
	if (bunny::g_is.GetKeyDown(SDL_SCANCODE_W) || bunny::g_is.GetKeyDown(SDL_SCANCODE_UP)) {
		thrust = 1;
	}

	if (bunny::g_is.GetKeyDown(SDL_SCANCODE_S) || bunny::g_is.GetKeyDown(SDL_SCANCODE_DOWN)) {
		thrust = -1;
	}

	bunny::vec2 forward = bunny::vec2{ 0, -1 }.Rotate(transform.rotation);

	//auto physicsComponent = GetComponent<bunny::PhysicsComponent>();
	m_physics->ApplyForce(forward * m_speed * thrust);

	transform.position.x = bunny::Wrap(transform.position.x, (float)bunny::g_r.GetWidth());
	transform.position.y = bunny::Wrap(transform.position.y, (float)bunny::g_r.GetHeight());

	//shoot
	if (bunny::g_is.GetKeyDown(SDL_SCANCODE_SPACE) && !bunny::g_is.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
		switch (m_toggle) {
		case 1:
		{
			auto weapon = INSTANTIATE(Weapon, "PlayerBullet");
			weapon->transform = { transform.position, transform.rotation, 2 };
			weapon->Initialize();
			m_scene->Add(std::move(weapon));
			//bunny::Transform transform1{ transform.position, transform.rotation, 2 };
			//std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform1); //m_transform
			//weapon->tag = "Player";
			//std::unique_ptr<bunny::SpriteComponent> component = std::make_unique<bunny::SpriteComponent>();
			//component->m_texture = GET_RESOURCE(bunny::Texture, "ship.png", bunny::g_r);
			//weapon->AddComponent(std::move(component));
			//auto collisionComponent = std::make_unique<bunny::CircleCollisionComponent>();
			//collisionComponent->m_radius = 30.0f;
			//weapon->AddComponent(std::move(collisionComponent));
			//weapon->Initialize();
			//m_scene->Add(std::move(weapon));
		}
			break;
		case 2:
		{
			auto weapon = INSTANTIATE(Weapon, "PlayerBullet");
			weapon->transform = { transform.position, transform.rotation + bunny::DegreesToRadians(10), 2 };
			weapon->Initialize();
			m_scene->Add(std::move(weapon));
			weapon = INSTANTIATE(Weapon, "PlayerBullet");
			weapon->transform = { transform.position, transform.rotation - bunny::DegreesToRadians(10), 2 };
			weapon->Initialize();
			m_scene->Add(std::move(weapon));
			//bunny::Transform transform1{ transform.position, transform.rotation + bunny::DegreesToRadians(10), 2 };
			//std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform1); //m_transform
			//weapon->tag = "Player";
			//std::unique_ptr<bunny::SpriteComponent> component = std::make_unique<bunny::SpriteComponent>();
			//component->m_texture = GET_RESOURCE(bunny::Texture, "ship.png", bunny::g_r);
			//weapon->AddComponent(std::move(component));
			//auto collisionComponent = std::make_unique<bunny::CircleCollisionComponent>();
			//collisionComponent->m_radius = 30.0f;
			//weapon->AddComponent(std::move(collisionComponent));
			//weapon->Initialize();
			//m_scene->Add(std::move(weapon));
			//bunny::Transform transform2{ transform.position, transform.rotation - bunny::DegreesToRadians(10), 2 };
			//weapon = std::make_unique<Weapon>(400.0f, transform2); //m_transform
			//weapon->tag = "Player";
			//component = std::make_unique<bunny::SpriteComponent>();
			//component->m_texture = GET_RESOURCE(bunny::Texture, "ship.png", bunny::g_r);
			//weapon->AddComponent(std::move(component));
			//collisionComponent = std::make_unique<bunny::CircleCollisionComponent>();
			//collisionComponent->m_radius = 30.0f;
			//weapon->AddComponent(std::move(collisionComponent));
			//weapon->Initialize();
			//m_scene->Add(std::move(weapon));
		}
			break;
		case 3:
		{
			auto weapon = INSTANTIATE(Weapon, "PlayerBullet");
			weapon->transform = { transform.position, transform.rotation, 5 };
			weapon->Initialize();
			m_scene->Add(std::move(weapon));
			//bunny::Transform transform1{ transform.position, transform.rotation, 5 };
			//std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform1); //m_transform
			//weapon->tag = "Player";
			//std::unique_ptr<bunny::SpriteComponent> component = std::make_unique<bunny::SpriteComponent>();
			//component->m_texture = GET_RESOURCE(bunny::Texture, "ship.png", bunny::g_r);
			//weapon->AddComponent(std::move(component));
			//auto collisionComponent = std::make_unique<bunny::CircleCollisionComponent>();
			//collisionComponent->m_radius = 30.0f;
			//weapon->AddComponent(std::move(collisionComponent));
			//weapon->Initialize();
			//m_scene->Add(std::move(weapon));
		}
			break;
		}
	}

	//toggle weapon
	if (bunny::g_is.GetKeyDown(SDL_SCANCODE_X) && !bunny::g_is.GetPreviousKeyDown(SDL_SCANCODE_X)) {
		m_toggle++;
		if (m_toggle > 3) {
			m_toggle = 1;
		}
		std::cout << m_toggle;
	}

	if (bunny::g_is.GetKeyDown(SDL_SCANCODE_T)) {
		kiko::g_time.setTimeScale(0.5f);
	} else {
		kiko::g_time.setTimeScale(1.0f);
	}
}

void Player::onCollision(Actor* actor) {
	if (actor->tag == "Enemy") {
		m_health--;
		if (m_health == 0) {
			destroyed = true;
			m_game->SetLives(m_game->GetLives() - 1);
			dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);
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
			bunny::Transform transform{ { transform.position }, 0, 1 };
			auto emitter = std::make_unique<bunny::Emitter>(transform, data);
			emitter->lifespan = 0.1f;
			m_scene->Add(std::move(emitter));
		}
	}
}