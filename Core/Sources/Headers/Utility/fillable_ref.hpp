#pragma once

#ifdef __has_include
	#if __has_include(<optional>)
		#include <optional>
		#define OPTIONAL std::optional
	#elif __has_include(<experimental/optional>)
		#include <experimental/optional>
		#define OPTIONAL std::experimental::optional
	#endif
#else
	#include <optional>
	#define OPTIONAL std::optional
#endif

#include <stdexcept>

namespace Hippocrates::Utility {

	class const_error : public std::logic_error {
		using std::logic_error::logic_error;
	};

	template<typename T>
	class FillableRef {
	public:
		FillableRef(const T& ref) : isConstRef{ true }, asPointer{ &ref } {}
		FillableRef(T& ref) : asPointer{ &ref } {}
		FillableRef(T&& value) : asValue{ std::forward<T>(value) } {}

		const auto& operator*() const { return Get(); }
		auto& operator*() { return Get(); }

		const auto& Get() const {
			if (isConstRef)
				throw const_error("");
			return const_cast<FillableRef*>(this)->Get();
		}
		auto& Get() { return asValue ? asValue.value() : *asPointer; }

	private:
		OPTIONAL<T> asValue;
		bool isConstRef = false;
		T* asPointer = nullptr;
	};

}

#undef OPTIONAL