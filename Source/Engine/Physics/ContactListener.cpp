#include "ContactListener.h"
#include "Framework/Components/CollisionComponent.h"
#include "Framework/Actor.h"

namespace bunny {
	void bunny::ContactListener::BeginContact(b2Contact* contact) {
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer) {
			Actor* actorA = reinterpret_cast<Actor*>(fixtureA->GetUserData().pointer);
			Actor* actorB = reinterpret_cast<Actor*>(fixtureB->GetUserData().pointer);

			if (actorA->destroyed || actorB->destroyed) return;

			actorA-> onCollisionEnter(actorB);
			actorB-> onCollisionEnter(actorA);
		}
	}

	void bunny::ContactListener::EndContact(b2Contact* contact) {
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer) {
			Actor* actorA = reinterpret_cast<Actor*>(fixtureA->GetUserData().pointer);
			Actor* actorB = reinterpret_cast<Actor*>(fixtureB->GetUserData().pointer);

			if (actorA->destroyed || actorB->destroyed) return;

			actorA->onCollisionExit(actorB);
			actorB->onCollisionExit(actorA);
		}
	}
}