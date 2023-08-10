#include "SpaceGame.h"
#include "Enemy.h"
#include "Player.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

bool SpaceGame::Initialize() {
	m_font = bunny::g_rm.Get<bunny::Font>("orangejuice.ttf", 24);
	m_gametimerText = std::make_unique<bunny::Text>(m_font);
	m_text1 = std::make_unique<bunny::Text>(m_font);
	m_text2 = std::make_unique<bunny::Text>(m_font);
	m_text3 = std::make_unique<bunny::Text>(m_font);

	bunny::g_as.AddAudio("hit", "hit.wav");
	bunny::g_as.AddAudio("melody", "melody.wav");

	m_scene = std::make_unique<bunny::Scene>();

	return true;
}

void SpaceGame::Shutdown() {

}

void SpaceGame::Update(float dt) {
	switch (m_state) {
	case SpaceGame::eState::Title:
		m_text1->Create(bunny::g_r, "Azteroids", bunny::Color{ 1, 1, 1, 1 });
		m_text2->Create(bunny::g_r, "Try to beat the highscore!(X to toggle weapon, and Hold T to slow time!)", bunny::Color{ 1, 1, 1, 1 });
		m_text3->Create(bunny::g_r, "High Score: " + std::to_string(m_highscore), bunny::Color{1, 1, 1, 1});
		if (bunny::g_is.GetKeyDown(SDL_SCANCODE_SPACE)) {
			m_state = eState::StartGame;
		}
		break;
	case SpaceGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		bunny::g_as.PlayOneShot("melody", true);
		m_state = eState::StartLevel;
		break;
	case SpaceGame::eState::StartLevel: 
		m_scene->RemoveAll();
	{
		// create player
		auto player = std::make_unique<Player>(10.0f, bunny::PI, bunny::Transform{ { 400, 300 }, 0, 3 });
		player->m_tag = "Player";
		player->m_game = this;
		//create components
		std::unique_ptr<bunny::ModelRenderComponent> component = std::make_unique<bunny::ModelRenderComponent>();
		component->m_model = bunny::g_rm.Get<bunny::Model>("good.txt");
		player->AddComponent(std::move(component));
		auto physicsComponent = std::make_unique<bunny::EnginePhysicsComponent>();
		physicsComponent->m_damping = 0.9f;
		player->AddComponent(std::move(physicsComponent));
		m_scene->Add(std::move(player));
	}
		m_state = eState::Game;
		break;
	case SpaceGame::eState::Game:
		m_text1->Create(bunny::g_r, "Score: " + std::to_string(m_score), bunny::Color{1, 1, 1, 1});
		m_text2->Create(bunny::g_r, "Lives: " + std::to_string(m_lives), bunny::Color{1, 1, 1, 1});
		m_gameTimer += dt;
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime) {
			m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(bunny::randomf(75.0f, 150.0f), bunny::PI, bunny::Transform(((float)bunny::random(800), (float)bunny::random(600)), bunny::randomf(bunny::TwoPI), 2.0f));
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			//create components
			std::unique_ptr<bunny::SpriteComponent> component = std::make_unique<bunny::SpriteComponent>();
			component->m_texture = bunny::g_rm.Get<bunny::Texture>("ship.png", bunny::g_r);
			enemy->AddComponent(std::move(component));
			m_scene->Add(std::move(enemy));
		}
		break;
	case eState::PlayerDeadStart:
		m_stateTimer = 3;
		if (m_lives == 0) {
			m_state = eState::GameOver;
		} else {
			m_state = eState::PlayerDead;
		}
		break;
	case SpaceGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			m_state = eState::StartLevel;
		}

		break;
	case SpaceGame::eState::GameOver:
		if (m_highscore < m_score) m_highscore = m_score;
		m_text1->Create(bunny::g_r, "Game Over!", bunny::Color{ 1, 1, 1, 1 });
		m_text2->Create(bunny::g_r, "Score: " + std::to_string(m_score), bunny::Color{1, 1, 1, 1});
		m_text3->Create(bunny::g_r, "High Score: " + std::to_string(m_highscore), bunny::Color{ 1, 1, 1, 1 });
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

void SpaceGame::Draw(bunny::Renderer& r) {
	switch (m_state) {
	case eState::Title:
		m_text1->Draw(r, 300, 0);
		m_text2->Draw(r, 25, 200);
		m_text3->Draw(r, 275, 400);
		break;
	case eState::Game:
		m_text1->Draw(r, 100, 0);
		m_text2->Draw(r, 600, 0);
		break;
	case eState::GameOver:
		m_text1->Draw(r, 400, 100);
		m_text2->Draw(r, 400, 200);
		m_text3->Draw(r, 400, 300);
		break;
	default:
		break;
	}

	m_scene->Draw(r);
}
