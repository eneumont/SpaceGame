#include "Scene.h"
#include "Framework/Components/CollisionComponent.h"

namespace bunny {
	void Scene::Update(float dt) {
		//update & remove destroyed actors
		auto iter = m_actors.begin();

		while (iter != m_actors.end()) {
			if ((*iter)->active) (*iter)->Update(dt);
			((*iter)->destroyed) ? iter = m_actors.erase(iter) : iter++;
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
			if (a->active) a->Draw(r);
		}
	}

	void Scene::Add(std::unique_ptr<Actor> a) {
		a->m_scene = this;
		m_actors.push_back(std::move(a));
	}

	void Scene::RemoveAll(bool force) {
		auto iter = m_actors.begin();
		while (iter != m_actors.end()) {
			(force || !(*iter)->persistent) ? iter = m_actors.erase(iter) : iter++;
		}
	}

	bool Scene::Load(const std::string& filename) {
		rapidjson::Document document;
		if (!Json::Load(filename, document)) {
			ERROR_LOG("Could not load scene file: " << filename);
			return false;
		}

		Read(document);

		return true;
	}

	void Scene::Read(const json_t& value) {
		if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray()) {
			for (auto& actorValue : GET_DATA(value, actors).GetArray()) {
				std::string type;
				READ_DATA(actorValue, type);

				auto actor = CREATE_CLASS_BASE(Actor, type);
				actor->Read(actorValue);

				if (actor->prototype) {
					std::string name = actor->name;
					Factory::Instance().RegisterPrototype(name, std::move(actor));
				} else {
					Add(std::move(actor));
				}
			}
		}
	}

	bool Scene::Initialize() {
		for (auto& actor : m_actors) actor->Initialize();
		
		return true;
	}
}