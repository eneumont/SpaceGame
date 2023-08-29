#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"
#include "PlatformerGame/Platformer.h"
#include "Framework/Resource/ResourceManager.h"

namespace bunny {
	CLASS_DEFINITION(Player)

	bool Player::Initialize() {
		Actor::Initialize();

		m_physics = GetComponent<PhysicsComponent>();
		m_anim = GetComponent<AnimComponent>();

		return true;
	}

	void Player::Update(float dt) {
		Actor::Update(dt);

		bool onGround = (groundCount > 0);

		//movement
		float dir = 0;
		if (g_is.GetKeyDown(SDL_SCANCODE_A) || g_is.GetKeyDown(SDL_SCANCODE_LEFT)) {
			dir = -1;
		}

		if (g_is.GetKeyDown(SDL_SCANCODE_D) || g_is.GetKeyDown(SDL_SCANCODE_RIGHT)) {
			dir = 1;
		}

		vec2 forward = vec2{ 1, 0 };
		m_physics->ApplyForce(forward * speed * dir * ((onGround) ? 1 : 0.25f));
		
		if (onGround && (g_is.GetKeyDown(SDL_SCANCODE_W) && !g_is.GetPreviousKeyDown(SDL_SCANCODE_W) || g_is.GetKeyDown(SDL_SCANCODE_UP) && !g_is.GetPreviousKeyDown(SDL_SCANCODE_UP))) {
			bunny::vec2 up = bunny::vec2{ 0, -1 };
			m_physics->SetVelocity(up * jump);
		}

		if (g_is.GetKeyDown(SDL_SCANCODE_S) || g_is.GetKeyDown(SDL_SCANCODE_DOWN)) {

		}

		
		vec2 velocity = m_physics->m_velocity;
		if (std::fabs(velocity.x) > 0.2f) {
			// if dir != 0 dir < 0
			m_anim->flipH = (velocity.x < -0.1f);
			m_anim->setSequence("run");
		} else {
			m_anim->setSequence("idle");
		}
	}

	void Player::onCollisionEnter(Actor* actor) {
		if (actor->tag == "Enemy") {
			
		}

		if (actor->tag == "Ground") groundCount++;
	}

	void Player::onCollisionExit(Actor* actor) {
		if (actor->tag == "Ground") groundCount--;
	}

	void Player::Read(const json_t& value) {
		Actor::Read(value);
		READ_NAME_DATA(value, "speed", speed);
		READ_NAME_DATA(value, "jump", jump);
	}
}