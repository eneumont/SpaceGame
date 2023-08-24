#include "Platformer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

bool Platformer::Initialize() {
	bunny::g_as.AddAudio("hit", "hit.wav");
	bunny::g_as.AddAudio("melody", "melody.wav");

	m_scene = std::make_unique<bunny::Scene>();
	m_scene->Load("Scenes/title.json");
	m_scene->Initialize();

	EVENT_SUBSCRIBE("onAddPoints", SpaceGame::onAddPoints);
	EVENT_SUBSCRIBE("onPlayerDead", SpaceGame::onPlayerDead);

	return true;
}

void Platformer::Shutdown() {

}

void Platformer::Update(float dt) {
	switch (m_state) {
	case Platformer::eState::Title:
		m_scene->GetActorByName("Title")->active = true;
		break;
	case Platformer::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		bunny::g_as.PlayOneShot("melody", true);
		m_scene->GetActorByName("Title")->active = false;
		m_state = eState::StartLevel;
		break;
	case Platformer::eState::StartLevel:
		m_scene->RemoveAll();
		{
			auto player = INSTANTIATE(Player, "Player");
			player->transform = bunny::Transform{ { 400, 300 }, 0, 3 };
			player->Initialize();
			m_scene->Add(std::move(player));

			// create player
			//auto player = std::make_unique<bunny::Player>(10.0f, bunny::PI, bunny::Transform{ { 400, 300 }, 0, 3 });
			//player->tag = "Player";
			//player->m_game = this;
			//create components
			//auto component = CREATE_CLASS(SpriteComponent);
			//component->m_texture = GET_RESOURCE(bunny::Texture, "playership.png", bunny::g_r);
			//player->AddComponent(std::move(component));
			//auto physicsComponent = CREATE_CLASS(EnginePhysicsComponent);
			//physicsComponent->m_damping = 0.9f;
			//player->AddComponent(std::move(physicsComponent));
			//auto collisionComponent = CREATE_CLASS(CircleCollisionComponent);
			//collisionComponent->m_radius = 30.0f;
			//player->AddComponent(std::move(collisionComponent));
			//player->Initialize();
			//m_scene->Add(std::move(player));
		}
		m_state = eState::Game;
		break;
	case Platformer::eState::Game:
		m_text1->Create(bunny::g_r, "Score: " + std::to_string(m_score), bunny::Color{ 1, 1, 1, 1 });
		m_text2->Create(bunny::g_r, "Lives: " + std::to_string(m_lives), bunny::Color{ 1, 1, 1, 1 });
		m_gameTimer += dt;
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime) {
			m_spawnTimer = 0;
			auto enemy = INSTANTIATE(Enemy, "Enemy");
			enemy->transform = bunny::Transform{ { bunny::random(800), bunny::random(600) }, bunny::randomf(bunny::TwoPI), 2 };
			enemy->Initialize();
			m_scene->Add(std::move(enemy));
		}
		break;
	case eState::PlayerDeadStart:
		m_stateTimer = 3;
		if (m_lives == 0) {
			m_state = eState::GameOver;
		}
		else {
			m_state = eState::PlayerDead;
		}
		break;
	case Platformer::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			m_state = eState::StartLevel;
		}

		break;
	case Platformer::eState::GameOver:
		if (m_highscore < m_score) m_highscore = m_score;
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			m_scene->RemoveAll();
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}

	m_scene->Update(dt);
}

void Platformer::Draw(bunny::Renderer& r) {
	m_scene->Draw(r);

	switch (m_state) {
	case eState::Title:
		break;
	case eState::Game:
		break;
	case eState::GameOver:
		break;
	default:
		break;
	}
}

void Platformer::onAddPoints(const bunny::Event& event) {
	m_score += std::get<int>(event.data);
}

void Platformer::onPlayerDead(const bunny::Event& event) {
	m_lives--;
	m_state = eState::PlayerDeadStart;
}