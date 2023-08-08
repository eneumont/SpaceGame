#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include "Player.h"
#include "Enemy.h"
#include "Audio/AudioSystem.h"
#include <memory>
#include "Game/SpaceGame.h"
#include <array>
#include <map>
#include "Framework/Framework.h"

using namespace std;
using vec2 = bunny::Vector2;

class Star {
public:
	Star(const vec2& pos, const bunny::Vector2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update(int width, int height) {
		m_pos += m_vel * kiko::g_time.GetDelta();

		if (m_pos.x >= width) {
			m_pos.x = 0;
		}

		if (m_pos.y >= height) {
			m_pos.y = 0;
		}
	}

	void Draw(bunny::Renderer& r) {
		r.DrawPoint(m_pos.x, m_pos.y);
	}
public:
	bunny::vec2 m_pos;
	bunny::vec2 m_vel;
};

int main(int argc, char* argv[]) {
	bunny::MemoryTracker::Initialize();
	bunny::seedRandom((unsigned int)time(nullptr));
	bunny::setFilePath("Assets");

	bunny::g_r.Initialize();
	bunny::g_r.CreateWindow("CSC196", 800, 600);
	bunny::g_is.Initialize();
	bunny::g_as.Initialize();

	unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
	game->Initialize();

	bunny::vec2 v{ 5,5 };
	v.Normalize();

	vector<Star> stars;
	for (int i = 0; i < 1000; i++) {
		bunny::Vector2 pos(bunny::Vector2(bunny::random(bunny::g_r.GetWidth()), bunny::random(bunny::g_r.GetHeight())));
		bunny::Vector2 vel(bunny::randomf(100, 200), 0.0f);
		stars.push_back(Star(pos, vel));
	}

	//game loop
	bool quit = false;
	while (!quit) {
		kiko::g_time.Tick();
		bunny::g_as.Update();
		bunny::g_is.Update();
		bunny::g_ps.Update(kiko::g_time.GetDelta());

		if (bunny::g_is.GetKeyDown(SDL_SCANCODE_SPACE) && !bunny::g_is.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
			bunny::g_as.PlayOneShot("hit");
		}

		game->Update(kiko::g_time.GetDelta());

		bunny::g_r.SetColor(0, 0, 0, 0);
		bunny::g_r.BeginFrame();

		// draw
		for (auto& star : stars) {
			star.Update(bunny::g_r.GetWidth(), bunny::g_r.GetHeight());

			bunny::g_r.SetColor(bunny::random(256), bunny::random(256), bunny::random(256), 255);
			star.Draw(bunny::g_r);
		}

		bunny::g_ps.Draw(bunny::g_r);
		game->Draw(bunny::g_r);

		bunny::g_r.EndFrame();
	}

	stars.clear();
	bunny::MemoryTracker::DisplayInfo();

	return 0;
}