//
// SSXI
// (C) 2022 modeco80
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


#ifndef SSXI_SSXOG_H
#define SSXI_SSXOG_H

#include <ssxi/pinebase.h>
#include <ssxi/bxtypes.h>

namespace ssxi {

	/**
	 * SSX OG game class.
	 */
	struct SSX : public PineBase {

		// TODO: Generic `ObjectBinding` class which SSX and SSXDVD use?
		struct Binding {
			Binding(SSX& ssx);

		   protected:
			SSX& game;
		};

		struct Game;

		/**
		 * Binding to cApplication
		 */
		struct Application : public Binding {

			ValueBinding<float> GameRate();

			Game GameInstance();
		};

		struct Rider;

		/**
		 * Binding to cGame
		 */
		struct Game : public Binding {
			Rider PlayerRider();

		   protected:
			friend Application;

			Game(SSX& ssx, PS2Address where);

			PS2Address where;
		};

		/**
		 * Binding to riders
		 */
		struct Rider : public Binding {
			/**
			 * Get a value binding referencing the position.
			 */
			ValueBinding<tVec3> Position();

			/**
			 * Get a value binding referencing the rider's speed multiplier.
			 */
			ValueBinding<float> SpeedMultiplier();

		   protected:
			friend Game;

			Rider(SSX& ssx, PS2Address where);
			PS2Address where;
		};

		struct World{}; // to do

		Application TheApp();
	};

}

#endif // SSXI_SSXOG_H
