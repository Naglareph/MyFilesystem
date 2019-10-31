#include <windows.h>
#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std;
using namespace std::chrono;


class Game {
	thread th;
	static void loadConfig() {
		this_thread::sleep_for(3s);
		cout << "load finished\n";
	}
public:
	Game() : th{ &Game::loadConfig } {}
	void start() {
		for (int n{}; n < 10; ++n) {
			cout << "*********\n";
			this_thread::sleep_for(250ms);
		}
		// ...
		th.join();
		cout << "just do it\n";
	}
};

int main() {
	Game game;
	game.start();
}
