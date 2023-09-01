#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"
#include "Framework/Event/EventManager.h"

class Platformer : public bunny::Game, bunny::IEventListener {
public:
	enum class eState {
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDeadStart,
		PlayerDead,
		GameOverStart,
		GameOver
	};

	virtual bool Initialize() override;
	virtual void Shutdown() override;
	virtual void Update(float dt) override;
	virtual void Draw(bunny::Renderer& r) override;

	void SetState(eState state) { m_state = state; };
	void onAddPoints(const bunny::Event& event);
	void onPlayerDead(const bunny::Event& event);
private:
	eState m_state = eState::Title;
	std::unique_ptr<bunny::Text> m_text1;
	float m_spawnTimer = 0;
	float m_spawnTime = 3;
	float m_stateTimer = 0;
	float m_gameTimer = 0;
};