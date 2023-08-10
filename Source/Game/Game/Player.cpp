#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Weapon.h"
#include "Framework/Scene.h"
#include "Game/SpaceGame.h"
#include "Framework/Emitter.h"
#include "Framework/Components/SpriteComponent.h"
#include "Framework/Resource/ResourceManager.h"
#include "Framework/Components/EnginePhysicsComponent.h"

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
	m_transform.rotation += rotate * m_turnRate * kiko::g_time.GetDelta();

	float thrust = 0;
	if (bunny::g_is.GetKeyDown(SDL_SCANCODE_W) || bunny::g_is.GetKeyDown(SDL_SCANCODE_UP)) {
		thrust = 1;
	}

	if (bunny::g_is.GetKeyDown(SDL_SCANCODE_S) || bunny::g_is.GetKeyDown(SDL_SCANCODE_DOWN)) {
		thrust = -1;
	}

	bunny::vec2 forward = bunny::vec2{ 0, -1 }.Rotate(m_transform.rotation);

	auto physicsComponent = GetComponent<bunny::PhysicsComponent>();
	physicsComponent->ApplyForce(forward * m_speed * thrust);

	m_transform.position.x = bunny::Wrap(m_transform.position.x, (float)bunny::g_r.GetWidth());
	m_transform.position.y = bunny::Wrap(m_transform.position.y, (float)bunny::g_r.GetHeight());

	//shoot
	if (bunny::g_is.GetKeyDown(SDL_SCANCODE_SPACE) && !bunny::g_is.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
		switch (m_toggle) {
		case 1:
		{
			bunny::Transform transform1{ m_transform.position, m_transform.rotation, 2 };
			std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform1); //m_transform
			weapon->m_tag = "Player";
			std::unique_ptr<bunny::SpriteComponent> component = std::make_unique<bunny::SpriteComponent>();
			component->m_texture = bunny::g_rm.Get<bunny::Texture>("ship.png", bunny::g_r);
			weapon->AddComponent(std::move(component));
			m_scene->Add(std::move(weapon));
		}
			break;
		case 2:
		{
			bunny::Transform transform1{ m_transform.position, m_transform.rotation + bunny::DegreesToRadians(10), 2 };
			std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform1); //m_transform
			weapon->m_tag = "Player";
			std::unique_ptr<bunny::SpriteComponent> component = std::make_unique<bunny::SpriteComponent>();
			component->m_texture = bunny::g_rm.Get<bunny::Texture>("ship.png", bunny::g_r);
			weapon->AddComponent(std::move(component));
			m_scene->Add(std::move(weapon));
			bunny::Transform transform2{ m_transform.position, m_transform.rotation - bunny::DegreesToRadians(10), 2 };
			weapon = std::make_unique<Weapon>(400.0f, transform2); //m_transform
			weapon->m_tag = "Player";
			component = std::make_unique<bunny::SpriteComponent>();
			component->m_texture = bunny::g_rm.Get<bunny::Texture>("ship.png", bunny::g_r);
			weapon->AddComponent(std::move(component));
			m_scene->Add(std::move(weapon));
		}
			break;
		case 3:
		{
			bunny::Transform transform1{ m_transform.position, m_transform.rotation, 5 };
			std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform1); //m_transform
			weapon->m_tag = "Player";
			std::unique_ptr<bunny::SpriteComponent> component = std::make_unique<bunny::SpriteComponent>();
			component->m_texture = bunny::g_rm.Get<bunny::Texture>("ship.png", bunny::g_r);
			weapon->AddComponent(std::move(component));
			m_scene->Add(std::move(weapon));
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
	if (actor->m_tag == "Enemy") {
		m_health--;
		if (m_health == 0) {
			m_destroyed = true;
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
			bunny::Transform transform{ { m_transform.position }, 0, 1 };
			auto emitter = std::make_unique<bunny::Emitter>(transform, data);
			emitter->m_lifespan = 0.1f;
			m_scene->Add(std::move(emitter));
		}
	}
}