#include "Enemy.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"
#include "PlatformerGame/Platformer.h"
#include "Framework/Resource/ResourceManager.h"

namespace bunny {
	CLASS_DEFINITION(Enemy)

	bool Enemy::Initialize() {
		Actor::Initialize();

		m_physics = GetComponent<PhysicsComponent>();

		return true;
	}

	void Enemy::Update(float dt) {
		Actor::Update(dt);

		//movement
		float dir = 0;
		if (g_is.GetKeyDown(SDL_SCANCODE_A) || g_is.GetKeyDown(SDL_SCANCODE_LEFT)) {
			dir = -1;
		}

		if (g_is.GetKeyDown(SDL_SCANCODE_D) || g_is.GetKeyDown(SDL_SCANCODE_RIGHT)) {
			dir = 1;
		}

		bool onGround = (groundCount > 0);
		if (onGround && (g_is.GetKeyDown(SDL_SCANCODE_W) && !g_is.GetPreviousKeyDown(SDL_SCANCODE_W) || g_is.GetKeyDown(SDL_SCANCODE_UP) && !g_is.GetPreviousKeyDown(SDL_SCANCODE_UP))) {
			bunny::vec2 up = bunny::vec2{ 0, -1 };
			m_physics->SetVelocity(up * jump);
		}

		if (g_is.GetKeyDown(SDL_SCANCODE_S) || g_is.GetKeyDown(SDL_SCANCODE_DOWN)) {

		}

		vec2 forward = vec2{ 1, 0 };

		m_physics->ApplyForce(forward * speed * dir);

		if (g_is.GetKeyDown(SDL_SCANCODE_SPACE) && !g_is.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {

		}
	}

	void Enemy::onCollisionEnter(Actor* actor) {
		if (actor->tag == "Player") {

		}

		if (actor->tag == "Ground") groundCount++;
	}

	void Enemy::onCollisionExit(Actor* actor) {
		if (actor->tag == "Ground") groundCount--;
	}

	void Enemy::Read(const json_t& value) {
		Actor::Read(value);
		READ_NAME_DATA(value, "speed", speed);
		READ_NAME_DATA(value, "jump", jump);
	}
}