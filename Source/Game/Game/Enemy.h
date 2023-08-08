#pragma once
#include "Framework/Actor.h"

class Enemy : public bunny::Actor {
public:
	Enemy(float speed, float turnRate, const bunny::Transform& transform) :
		Actor{ transform },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		m_fireRate = 2.0f;
		m_fireTimer = m_fireRate;
	}

	void Update(float dt) override;
	void onCollision(Actor* actor) override;
private:
	float m_speed = 0;
	float m_turnRate = 0;
	float m_fireRate = 0;
	float m_fireTimer = 0;
};