// This file contains basic types which we want to always allow in the PINE abstraction layer
// thingy; we do this via a X-macro style invocation mechanism, where
// BASIC_TYPE(T) must be created before inclusion of this file, to do whatever BASIC_TYPE() does.

BASIC_TYPE(std::int8_t)
BASIC_TYPE(std::uint8_t)
BASIC_TYPE(std::int16_t)
BASIC_TYPE(std::uint16_t)
BASIC_TYPE(std::int32_t)
BASIC_TYPE(std::uint32_t)
BASIC_TYPE(std::int64_t)
BASIC_TYPE(std::uint64_t)