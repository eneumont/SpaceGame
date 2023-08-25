#include "Platformer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

bool Platformer::Initialize() {
	bunny::g_as.AddAudio("hit", "Audio/hit.wav");
	bunny::g_as.AddAudio("melody", "Audio/melody.wav");

	m_scene = std::make_unique<bunny::Scene>();
	m_scene->Load("Scenes/title.json");
	m_scene->Initialize();

	return true;
}

void Platformer::Shutdown() {

}

void Platformer::Update(float dt) {
	switch (m_state) {
	case Platformer::eState::Title:
		m_scene->GetActorByName("Title")->active = true;
		bunny::g_as.PlayOneShot("melody", true);
		break;
	case Platformer::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		//bunny::g_as.PlayOneShot("melody", true);
		//m_scene->GetActorByName("Title")->active = false;
		m_state = eState::StartLevel;
		break;
	case Platformer::eState::StartLevel:
		m_scene->RemoveAll();
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