#include "Platformer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

bool Platformer::Initialize() {
	std::shared_ptr<bunny::Font>m_font = GET_RESOURCE(bunny::Font, "Fonts/orangejuice.ttf", 24);
	m_text1 = std::make_unique<bunny::Text>(m_font);


	bunny::g_as.AddAudio("hit", "Audio/hit.wav");
	bunny::g_as.AddAudio("melody", "Audio/melody.wav");

	m_scene = std::make_unique<bunny::Scene>();
	m_scene->Load("Scenes/title.json");
	m_scene->Load("Scenes/tilemap.json");
	m_scene->Initialize();
	
	EVENT_SUBSCRIBE("onAddPoints", Platformer::onAddPoints);
	EVENT_SUBSCRIBE("onPlayerDead", Platformer::onPlayerDead);

	return true;
}

void Platformer::Shutdown() {

}

void Platformer::Update(float dt) {
	switch (m_state) {
	case Platformer::eState::Title:
	{
		m_text1->Create(bunny::g_r, std::to_string(m_score), bunny::Color{1, 1, 1, 1});
		//m_scene->Load("Scenes/title.json");
		/*auto actor = INSTANTIATE(Actor, "Rock");
		actor->transform.position = { bunny::random(bunny::g_r.GetWidth()), 100 };
		actor->Initialize();
		m_scene->Add(std::move(actor));*/
	}
		break;
	case Platformer::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		//bunny::g_as.PlayOneShot("melody", true);
		m_state = eState::StartLevel;
		break;
	case Platformer::eState::StartLevel:
		//m_scene->RemoveAll();
		{

		}
		m_state = eState::Game;
		break;
	case Platformer::eState::Game:
		m_gameTimer += dt;
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime) {
			m_spawnTimer = 0;
			
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
		m_text1->Draw(r, 500, 0);
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