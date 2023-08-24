#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include "Audio/AudioSystem.h"
#include <memory>
#include "Platformer.h"
#include <array>
#include <map>
#include "Framework/Framework.h"
#include "Physics/PhysicsSystem.h"
#include <functional>

using namespace std;
using vec2 = bunny::Vector2;

int main(int argc, char* argv[]) {
	bunny::MemoryTracker::Initialize();
	bunny::seedRandom((unsigned int)time(nullptr));
	bunny::setFilePath("Assets");

	bunny::g_r.Initialize();
	bunny::g_r.CreateWindow("CSC196", 800, 600);
	bunny::g_is.Initialize();
	bunny::g_as.Initialize();
	bunny::PhysicsSystem::Instance().Initialize();

	unique_ptr<Platformer> game = make_unique<Platformer>();
	game->Initialize();

	//game loop
	bool quit = false;
	while (!quit) {
		kiko::g_time.Tick();
		bunny::g_as.Update();
		bunny::g_is.Update();
		bunny::g_ps.Update(kiko::g_time.GetDelta());
		bunny::PhysicsSystem::Instance().Update(kiko::g_time.GetDelta());

		game->Update(kiko::g_time.GetDelta());

		bunny::g_r.SetColor(0, 0, 0, 0);
		bunny::g_r.BeginFrame();
		game->Draw(bunny::g_r);

		// draw
		bunny::g_ps.Draw(bunny::g_r);
		bunny::g_r.EndFrame();
	}

	bunny::MemoryTracker::DisplayInfo();

	return 0;
}