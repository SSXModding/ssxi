//
// SSXI
// (C) 2022 modeco80
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

// This is a simple test of SSXI.

#include <ssxi/ssxog.h>
#include <iostream>

#include <thread>

int main() {
	ssxi::SSX ssx;

	// Walk the chain to eventually get the player rider.
	// This could be done in one statement, but it would be a tiny bit more
	// unmaintainable, and I generally don't think it would be worth it.
	auto app = ssx.TheApp();
	auto game = app.GameInstance();
	auto rider = game.PlayerRider();

	// Do something interesting with the player rider.
	while(true) {
		auto pos = rider.Position();

		auto v3 = pos.Get();

		// Set the position using the value binding
		pos = {
			v3.x,
			v3.y,
			v3.z + 10000,
		};

		std::cout << "Position is (" << v3.x << ',' << v3.y << ',' << v3.z << ")\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

}