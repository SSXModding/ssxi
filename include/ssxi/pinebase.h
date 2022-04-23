//
// SSXI
// (C) 2022 modeco80
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#ifndef SSXI_PINEBASE_H
#define SSXI_PINEBASE_H

#include <cstdint>

namespace ssxi {

	/**
	 * Type capable of storing a PS2 address.
	 */
	using PS2Address = std::uint32_t;
	using PS2Pointer = PS2Address;
	using PS2Offset = PS2Address;

	/**
	 * Base class for PINE interaction.
	 */
	struct PineBase {
		PineBase();
		~PineBase();

		// TODO: Safe wrappers for some other PINE APIs,
		// 	like savestate, game uuid, game id, ....

		/**
		 * Get a value of type T from the address at address.
		 *
		 * Accepted types currently are:
		 * 	- (u)intXX_t (all portable combinations, so no uint128_t)
		 *	- PS2Address, PS2Pointer, PS2Offset (which are just uint32_t sugar anyways)
		 *	- float
		 *	- double
		 *	- tVec3 (see ssxi/bxtypes.h)
		 *
		 * Any others will result in link time errors, so don't use them.
		 */
		template <typename T>
		T Get(PS2Address address);

		template <typename T>
		void Set(PS2Address address, const T& t);

	};

	/**
	 * Provides a binding over a value, which can be used
	 * to get or set the value with intuitive syntax.
	 */
	template <typename T>
	struct ValueBinding {
		ValueBinding(PineBase& pine, PS2Address address)
			: pine(pine),
			  address(address) {
		}

		// plain accessors

		T Get() {
			return pine.Get<T>(address);
		}

		void Set(const T& t) {
			pine.Set<T>(address, t);
		}

		// operator magic

		operator T() { // NOLINT
			return Get();
		}

		ValueBinding& operator=(const T& other) {
			if(this == &other)
				return *this;

			// Write the value into memory.
			Set(other);

			return *this;
		}

		ValueBinding& operator=(T&& other) {
			Set(other);
			return *this;
		}

	   private:
		PineBase& pine;
		PS2Address address;
	};

	// TODO: specialization for T* that doesn't turn it into a real host pointer? because uhhhh that would be pretty shoddy

} // namespace ssxi

#endif // SSXI_PINEBASE_H