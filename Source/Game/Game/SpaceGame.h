#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"

class SpaceGame : public bunny::Game {
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

	void SetState(eState state) { m_state = state; }
private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0;
	float m_spawnTime = 3;
	float m_stateTimer = 0;
	float m_gameTimer = 0;

	std::shared_ptr<bunny::Font> m_font;
	std::unique_ptr<bunny::Text> m_gametimerText;
	std::unique_ptr<bunny::Text> m_text1;
	std::unique_ptr<bunny::Text> m_text2;
	std::unique_ptr<bunny::Text> m_text3;
};