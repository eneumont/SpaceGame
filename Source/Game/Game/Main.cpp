#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include <vector>
#include <iostream>
#include <chrono>
#include "Renderer/ModelManager.h"
#include <thread>
#include "Framework/Actor.h"
#include "Player.h"
#include "Enemy.h"
#include "Framework/Scene.h"
#include "Audio/AudioSystem.h"
#include <memory>
#include "Game/SpaceGame.h"
#include "Renderer/ParticleSystem.h"
#include "Core/Core.h"
#include <array>
#include <map>
#include "Framework/Resource/ResourceManager.h"

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
	/*int n[4] = { 1, 2, 3, 4 };
	print("array: ", n);
	cout << n << endl;
	cout << *(n + 3) << endl;

	std::array<int, 4> na = { 1, 2, 3, 4 };
	print("array class: ", na);
	cout << na.front() << endl;
	cout << na.back() << endl;
	cout << na.max_size() << endl;

	std::vector<int> nv = { 1, 2, 3, 4 };
	print("vector: ", nv);
	nv.insert(nv.begin() + 2, 0);
	nv.push_back(5);
	nv.pop_back();
	auto iter = nv.erase(nv.begin(), nv.end());
	print("vector", nv);

	std::list<int> nl = { 1, 2, 3, 4 };
	print("list:", nl);
	nl.push_front(0);
	print("list:", nl);

	std::map<std::string, int> ages;
	ages["Charles"] = 17;
	ages["Jacob"] = 18;
	ages["Cam"] = 19;
	ages["Unc"] = 21;

	cout << ages["Charles"] << endl;
	cout << ages["Jacob"] << endl;
	int* j = nullptr;
	ASSERT_LOG(j, "pointer is null");
	INFO_LOG("hi");*/

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

	bunny::res_t<bunny::Texture> texture = bunny::g_rm.Get<bunny::Texture>("ship.png", bunny::g_r);

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

		bunny::g_r.DrawTexture(texture.get(), 200.0f, 200.0f, 0.0f);

		// draw
		for (auto& star : stars) {
			star.Update(bunny::g_r.GetWidth(), bunny::g_r.GetHeight());

			bunny::g_r.SetColor(bunny::random(256), bunny::random(256), bunny::random(256), 255);
			star.Draw(bunny::g_r);
		}

		bunny::g_ps.Draw(bunny::g_r);
		game->Draw(bunny::g_r);

		bunny::g_r.EndFrame();
		//this_thread::sleep_for(chrono::milliseconds(100));
	}

	stars.clear();
	//scene.RemoveAll();
	bunny::MemoryTracker::DisplayInfo();

	return 0;
}