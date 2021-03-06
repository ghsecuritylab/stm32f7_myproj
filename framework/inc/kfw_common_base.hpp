
#pragma once
#ifndef KFW_BASE_HPP
#define KFW_BASE_HPP

#include <stddef.h>
#include <stdint.h>
#include <string.h>

using char8_t = char;

#define KFW_ASSERT(expr, ret) if(!(expr)) { kfw::kfw_assert(#expr); }
#define interface struct

namespace kfw {
	using ret_t = int;
	using component_id_t = int;

	template<class T> struct RetVal final {
		RetVal(ret_t ret_, T val_)
		: ret(ret_), val(val_) {
		}

		RetVal(ret_t ret_)
		: ret(ret_), val({0}) {

		}

		bool is_succeed() const {
			return ret >= 0;
		}

		bool is_failed() const {
			return ret < 0;
		}

		/**
		 * 値を取得します。
		 */
		T &operator ()() {
			return val;
		}

		ret_t ret;
		T val;
	};

	constexpr component_id_t kComponentCommon = 0;

	constexpr ret_t make_err_ret(component_id_t module_id, int err_code)
	{
		return (ret_t)((uint32_t)0x80000000 | ((uint32_t)module_id << 16) | (uint32_t)err_code);
	}

	static inline bool is_succeed(ret_t r) {
		return r >= 0;
	}

	static inline bool is_failed(ret_t r) {
		return r < 0;
	}

	constexpr ret_t kOk = 0;
	constexpr ret_t kEArgument = make_err_ret(kComponentCommon, 1);
	constexpr ret_t kEIndexOutOfRange = make_err_ret(kComponentCommon, 2);
	constexpr ret_t kEOutOfMemory = make_err_ret(kComponentCommon, 3);
	constexpr ret_t kEFormat = make_err_ret(kComponentCommon, 4);
	constexpr ret_t kETimeout = make_err_ret(kComponentCommon, 5);
	constexpr ret_t kEInvalidOperation = make_err_ret(kComponentCommon, 6);
	constexpr ret_t kEResource = make_err_ret(kComponentCommon, 7);
	constexpr ret_t kEDisposed = make_err_ret(kComponentCommon, 8);
	constexpr ret_t kENotSupported = make_err_ret(kComponentCommon, 9);
	constexpr ret_t kEUnknown = make_err_ret(kComponentCommon, 255);

	struct NonCopyable {
		NonCopyable() = default;
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;
	};

	void kfw_assert(const char *msg);
	[[noreturn]] void kfw_throw(ret_t r);

};

#endif
