//
// SSXI
// (C) 2022 modeco80
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include <pine.h>
#include <ssxi/pinebase.h>

#include <ssxi/bxtypes.h>

namespace ssxi {

	namespace {

		/**
		 * Global copy of pine object.
		 *
		 * Internally reference counted (used by all PineBase instances),
		 * deleted when the number of pinebase instances hit 0
		 */
		PINE::PCSX2* gPcsx2Emu = nullptr;
		std::uint32_t gPcsx2RefCnt = 0;

		void PineCreate() {
			if(!gPcsx2Emu || gPcsx2RefCnt == 0) {
				gPcsx2Emu = new PINE::PCSX2;
				gPcsx2RefCnt = 1;
			}
		}

		void PineAddRef() {
			gPcsx2RefCnt++;
		}

		void PineDecRef() {
			if(gPcsx2RefCnt-- == 0)
				delete gPcsx2Emu;
		}

		template <typename Dest, typename Source>
		constexpr Dest UBCast(Source source) {
			union {
				Source src;
				Dest dst;
			} u {
				.src = source
			};
			return u.dst;
		}
	} // namespace

	PineBase::PineBase() {
		if(!gPcsx2Emu || gPcsx2RefCnt == 0)
			PineCreate();
		else
			PineAddRef();
	}

	PineBase::~PineBase() {
		PineDecRef();
	}

// Template magic for PineBase::Get<T> and PineBase::Set<T>: Here be dragons!
// Most of this is covered by macros though.

// Get<T>() generation:
#define BASIC_TYPE(T)                        \
	template <>                              \
	T PineBase::Get<T>(PS2Pointer address) { \
		return gPcsx2Emu->Read<T>(address);  \
	}
#include "BasicTypeListing.inl"
#undef BASIC_TYPE

// Set<T>() generation:
#define BASIC_TYPE(T)                                       \
	template <>                                             \
	void PineBase::Set<T>(PS2Pointer address, const T& t) { \
		return gPcsx2Emu->Write<T>(address, t);             \
	}
#include "BasicTypeListing.inl"
#undef BASIC_TYPE

	template <>
	float PineBase::Get<float>(PS2Pointer address) {
		return UBCast<float>(Get<std::uint32_t>(address));
	}

	template <>
	void PineBase::Set<float>(PS2Pointer address, const float& fl) {
		Set<std::uint32_t>(address, UBCast<std::uint32_t>(fl));
	}

	template <>
	double PineBase::Get<double>(PS2Pointer address) {
		return UBCast<double>(Get<std::uint64_t>(address));
	}

	template <>
	void PineBase::Set<double>(PS2Pointer address, const double& fl) {
		Set<std::uint64_t>(address, UBCast<std::uint64_t>(fl));
	}

	// TODO: Implement with batch IPC

	template <>
	tVec3 PineBase::Get<tVec3>(PS2Pointer address) {
		return {
			.x = Get<float>(address),
			.y = Get<float>(address + 4),
			.z = Get<float>(address + 8)
		};
	}

	template <>
	void PineBase::Set<tVec3>(PS2Pointer address, const tVec3& v3) {
		Set(address, v3.x);
		Set(address + 4, v3.y);
		Set(address + 8, v3.z);
	}

} // namespace ssxi
