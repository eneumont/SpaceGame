#include "Enemy.h"
#include "Player.h"
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

		vec2 forward = vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player) {
			vec2 direction = player->transform.position - transform.position;
			m_physics->ApplyForce(direction.Normalized() * speed);
		}
	}

	void Enemy::onCollisionEnter(Actor* actor) {
		if (actor->tag == "Player") {

		}

		if (actor->tag == "PlayerRock") {
			lifespan = 0;
			EventManager::Instance().DispatchEvent("onAddPoints", 100);
		}

		if (actor->tag == "Ground") groundCount++;
	}

	void Enemy::onCollisionExit(Actor* actor) {
		if (actor->tag == "Ground") groundCount--;
		//if (actor->tag == "Player") EventManager::Instance().DispatchEvent("Add");

	}

	void Enemy::Read(const json_t& value) {
		Actor::Read(value);
		READ_NAME_DATA(value, "speed", speed);
		READ_NAME_DATA(value, "jump", jump);
	}
}