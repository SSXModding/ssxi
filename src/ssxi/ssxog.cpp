//
// SSXI
// (C) 2022 modeco80
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include <ssxi/ssxog.h>

namespace ssxi {

	namespace {
		// These constants/offsets are for US.

		constexpr PS2Address THEAPP_POINTER = 0x002852f8;

	} // namespace

	SSX::Binding::Binding(SSX& ssx)
		: game(ssx) {
	}

	ValueBinding<float> SSX::Application::GameRate() {
		return { game, THEAPP_POINTER + 0x6e0 };
	}

	SSX::Game SSX::Application::GameInstance() {
		return { game, game.Get<PS2Address>(THEAPP_POINTER + 0x6ec) };
	}

	SSX::Game::Game(SSX& ssx, PS2Address where)
		: SSX::Binding(ssx), where(where) {
	}

	SSX::Rider SSX::Game::PlayerRider() {
		return { game, game.Get<PS2Address>(where + 0xa4) };
	}

	SSX::Rider::Rider(SSX& ssx, PS2Address where)
		: SSX::Binding(ssx), where(where) {
	}

	ValueBinding<tVec3> SSX::Rider::Position() {
		return { game, where + 0xc0 };
	}

	ValueBinding<float> SSX::Rider::SpeedMultiplier() {
		return { game, where + 0xa0 };
	}

	SSX::Application SSX::TheApp() {
		return { *this };
	}

} // namespace ssxi