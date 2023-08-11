#include "Scene.h"
#include "Framework/Components/CollisionComponent.h"

namespace bunny {
	void Scene::Update(float dt) {
		//update & remove destroyed actors
		auto iter = m_actors.begin();

		while (iter != m_actors.end()) {
			(*iter)->Update(dt);
			((*iter)->m_destroyed) ? iter = m_actors.erase(iter) : iter++;
		}

		//check collisons
		for (auto iter1 = m_actors.begin(); iter1 != m_actors.end(); iter1++) {
			for (auto iter2 = std::next(iter1, 1); iter2 != m_actors.end(); iter2++) {
				CollisionComponent* collision1 = (*iter1)->GetComponent<CollisionComponent>();
				CollisionComponent* collision2 = (*iter2)->GetComponent<CollisionComponent>();

				if (!collision1 || !collision2) {
					continue;
				}

				if (collision1->checkCollision(collision2)) {
					(*iter1)->onCollision(iter2->get());
					(*iter2)->onCollision(iter1->get());
				}
			}
		}
	}

	void Scene::Draw(Renderer& r) {
		for (auto& a : m_actors) {
			a->Draw(r);
		}
	}

	void Scene::Add(std::unique_ptr<Actor> a) {
		a->m_scene = this;
		m_actors.push_back(std::move(a));
	}

	void Scene::RemoveAll() {
		m_actors.clear();
	}
}