#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Weapon.h"
#include "Framework/Framework.h"
#include "Game/SpaceGame.h"
#include "Framework/Resource/ResourceManager.h"

namespace bunny {
	CLASS_DEFINITION(Player)

	bool Player::Initialize() {
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

	void Player::Update(float dt) {
		Actor::Update(dt);

		//movement
		float rotate = 0;
		if (g_is.GetKeyDown(SDL_SCANCODE_A) || g_is.GetKeyDown(SDL_SCANCODE_LEFT)) {
			rotate = -1;
		}

		if (g_is.GetKeyDown(SDL_SCANCODE_D) || g_is.GetKeyDown(SDL_SCANCODE_RIGHT)) {
			rotate = 1;
		}
		//transform.rotation += rotate * m_turnRate * kiko::g_time.GetDelta();
		m_physics->ApplyTorque(rotate * m_turnRate);

		float thrust = 0;
		if (g_is.GetKeyDown(SDL_SCANCODE_W) || g_is.GetKeyDown(SDL_SCANCODE_UP)) {
			thrust = 1;
		}

		if (g_is.GetKeyDown(SDL_SCANCODE_S) || g_is.GetKeyDown(SDL_SCANCODE_DOWN)) {
			thrust = -1;
		}

		vec2 forward = vec2{ 0, -1 }.Rotate(transform.rotation);

		//auto physicsComponent = GetComponent<PhysicsComponent>();
		m_physics->ApplyForce(forward * m_speed * thrust);

		transform.position.x = Wrap(transform.position.x, (float)g_r.GetWidth());
		transform.position.y = Wrap(transform.position.y, (float)g_r.GetHeight());

		//shoot
		if (g_is.GetKeyDown(SDL_SCANCODE_SPACE) && !g_is.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
			switch (m_toggle) {
			case 1:
			{
				auto weapon = INSTANTIATE(Weapon, "PlayerBullet");
				weapon->transform = { transform.position + forward * 30, transform.rotation, 2 };
				weapon->Initialize();
				m_scene->Add(std::move(weapon));
			}
			break;
			case 2:
			{
				auto weapon = INSTANTIATE(Weapon, "PlayerBullet");
				weapon->transform = { transform.position + forward * 30, transform.rotation + DegreesToRadians(10), 2 };
				weapon->Initialize();
				m_scene->Add(std::move(weapon));
				weapon = INSTANTIATE(Weapon, "PlayerBullet");
				weapon->transform = { transform.position + forward * 30, transform.rotation - DegreesToRadians(10), 2 };
				weapon->Initialize();
				m_scene->Add(std::move(weapon));
			}
			break;
			case 3:
			{
				auto weapon = INSTANTIATE(Weapon, "PlayerBullet");
				weapon->transform = { transform.position + forward * 30, transform.rotation, 5 };
				weapon->Initialize();
				m_scene->Add(std::move(weapon));
			}
			break;
			}
		}

		//toggle weapon
		if (g_is.GetKeyDown(SDL_SCANCODE_X) && !g_is.GetPreviousKeyDown(SDL_SCANCODE_X)) {
			m_toggle++;
			if (m_toggle > 3) {
				m_toggle = 1;
			}
			std::cout << m_toggle;
		}

		if (g_is.GetKeyDown(SDL_SCANCODE_T)) {
			kiko::g_time.setTimeScale(0.5f);
		} else {
			kiko::g_time.setTimeScale(1.0f);
		}
	}

	void Player::onCollisionEnter(Actor* actor) {
		if (actor->tag == "Enemy") {
			m_health--;
			if (m_health == 0) {
				destroyed = true;
				EventManager::Instance().DispatchEvent("onPlayerDead", 0);
				//create explosion
				EmitterData data;
				data.burst = true;
				data.burstCount = 100;
				data.spawnRate = 200;
				data.angle = 0;
				data.angleRange = PI;
				data.lifetimeMin = 0.5f;
				data.lifetimeMin = 1.5f;
				data.speedMin = 50;
				data.speedMax = 250;
				data.damping = 0.5f;
				data.color = Color{ 1, 0, 0, 1 };
				Transform transform{ { transform.position }, 0, 1 };
				auto emitter = std::make_unique<Emitter>(transform, data);
				emitter->lifespan = 0.1f;
				m_scene->Add(std::move(emitter));
			}
		}
	}

	void Player::Read(const json_t& value) {
		Actor::Read(value);
		READ_NAME_DATA(value, "speed", m_speed);
		READ_NAME_DATA(value, "turnRate", m_turnRate);
	}
}