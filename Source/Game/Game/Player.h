#pragma once
#include "Framework/Actor.h"
#include "Weapon.h"
#include "Framework/Components/PhysicsComponent.h"

class Player : public bunny::Actor {
public:
	Player(float speed, float turnRate, const bunny::Transform& transform) :
		Actor{ transform },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{}

	bool Initialize() override;
	void Update(float dt) override;
	void onCollision(Actor* actor) override;
private:
	float m_speed = 0;
	float m_turnRate = 0;
	int m_toggle = 1;
	float m_health = 3;

	bunny::PhysicsComponent* m_physics = nullptr;
};