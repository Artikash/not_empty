#pragma once
#ifndef NOT_EMPTY_HXX_A
#define NOT_EMPTY_HXX_A

#include <utility> // forward, move
#include <exception> // terminate
#include <iterator> // empty
#include <cassert> // assert

template <typename T>
class not_empty
{
public:

	template <typename... args_t>
	constexpr not_empty(args_t&&... args) :
		container{ std::forward<args_t>(args)... }
	{
		static_assert(sizeof...(args), "Must initialize not_empty container");
		assert_not_empty();
	}

	not_empty(const not_empty&) = default;
	not_empty(not_empty&&) = default;
	not_empty& operator=(const not_empty&) = default;
	not_empty& operator=(not_empty&&) = default;

	not_empty& operator=(T other)
	{
		assert_not_empty(other);
		container = std::move(other);
		return *this;
	}

	constexpr const T& get() const
	{
		return container;
	}

	constexpr operator const T&() const
	{
		return container;
	}

	constexpr const T* operator->() const
	{
		return &container;
	}

	struct proxy_t
	{
		proxy_t(T& container) :
			container{ container }
		{}

		proxy_t(const proxy_t&) = default;

		T* operator->() const
		{
			return &container;
		}

		~proxy_t()
		{
			assert_not_empty(container);
		}

		T& container;
	};

	proxy_t writeable()
	{
		return proxy_t{ container };
	}

	#define NOT_EMPTY_FORWARD_CONST(fn)\
		template <typename... args_t>\
		constexpr auto fn(args_t&&... args) const ->\
			decltype(container.fn(std::forward<args_t>(args)...))\
		{\
			return container.fn(std::forward<args_t>(args)...);\
		}

	#define NOT_EMPTY_FORWARD_MUTABLE(fn)\
	template <typename... args_t>\
		constexpr auto fn(args_t&&... args) ->\
			decltype(container.fn(std::forward<args_t>(args)...))\
		{\
			return container.fn(std::forward<args_t>(args)...);\
		}

	#define NOT_EMPTY_FORWARD_GENERIC(fn)\
		NOT_EMPTY_FORWARD_CONST(fn)\
		NOT_EMPTY_FORWARD_MUTABLE(fn)

	#define NOT_EMPTY_FORWARD_AND_ASSERT(fn)\
		template <typename... args_t>\
		constexpr auto fn(args_t&&... args) ->\
			decltype(container.fn(std::forward<args_t>(args)...))\
		{\
			auto&& ret = container.fn(std::forward<args_t>(args)...);\
			assert_not_empty();\
			return ret;\
		}

	NOT_EMPTY_FORWARD_CONST(cbegin)
	NOT_EMPTY_FORWARD_CONST(cend)
	NOT_EMPTY_FORWARD_CONST(crbegin)
	NOT_EMPTY_FORWARD_CONST(crend)
	NOT_EMPTY_FORWARD_CONST(size)
	NOT_EMPTY_FORWARD_CONST(max_size)
	NOT_EMPTY_FORWARD_CONST(empty)
	NOT_EMPTY_FORWARD_CONST(capacity)
	NOT_EMPTY_FORWARD_CONST(at)
	NOT_EMPTY_FORWARD_CONST(count)
	NOT_EMPTY_FORWARD_CONST(contains)
	NOT_EMPTY_FORWARD_CONST(key_comp)
	NOT_EMPTY_FORWARD_CONST(value_comp)
	NOT_EMPTY_FORWARD_CONST(hash_function)
	NOT_EMPTY_FORWARD_CONST(key_eq)
	NOT_EMPTY_FORWARD_CONST(get_allocator)

	NOT_EMPTY_FORWARD_MUTABLE(shrink_to_fit)
	NOT_EMPTY_FORWARD_MUTABLE(reserve)
	NOT_EMPTY_FORWARD_MUTABLE(emplace)
	NOT_EMPTY_FORWARD_MUTABLE(insert)
	NOT_EMPTY_FORWARD_MUTABLE(emplace_back)
	NOT_EMPTY_FORWARD_MUTABLE(push_back)
	NOT_EMPTY_FORWARD_MUTABLE(emplace_front)
	NOT_EMPTY_FORWARD_MUTABLE(push_front)
	NOT_EMPTY_FORWARD_MUTABLE(splice)
	NOT_EMPTY_FORWARD_MUTABLE(unique)
	NOT_EMPTY_FORWARD_MUTABLE(merge)
	NOT_EMPTY_FORWARD_MUTABLE(sort)
	NOT_EMPTY_FORWARD_MUTABLE(reverse)
	NOT_EMPTY_FORWARD_MUTABLE(insert_or_assign)
	NOT_EMPTY_FORWARD_MUTABLE(emplace_hint)
	NOT_EMPTY_FORWARD_MUTABLE(try_emplace)

	NOT_EMPTY_FORWARD_GENERIC(begin)
	NOT_EMPTY_FORWARD_GENERIC(end)
	NOT_EMPTY_FORWARD_GENERIC(rbegin)
	NOT_EMPTY_FORWARD_GENERIC(rend)
	NOT_EMPTY_FORWARD_GENERIC(front)
	NOT_EMPTY_FORWARD_GENERIC(back)
	NOT_EMPTY_FORWARD_GENERIC(operator[])
	NOT_EMPTY_FORWARD_GENERIC(data)
	NOT_EMPTY_FORWARD_GENERIC(find)
	NOT_EMPTY_FORWARD_GENERIC(lower_bound)
	NOT_EMPTY_FORWARD_GENERIC(upper_bound)
	NOT_EMPTY_FORWARD_GENERIC(equal_range)
	
	NOT_EMPTY_FORWARD_AND_ASSERT(resize)
	NOT_EMPTY_FORWARD_AND_ASSERT(assign)
	NOT_EMPTY_FORWARD_AND_ASSERT(erase)
	NOT_EMPTY_FORWARD_AND_ASSERT(pop_back)
	NOT_EMPTY_FORWARD_AND_ASSERT(pop_front)
	NOT_EMPTY_FORWARD_AND_ASSERT(swap)
	NOT_EMPTY_FORWARD_AND_ASSERT(remove)
	NOT_EMPTY_FORWARD_AND_ASSERT(remove_if)
	NOT_EMPTY_FORWARD_AND_ASSERT(extract)

private:

	static constexpr void assert_not_empty(const T& container)
	{
		if (std::empty(container))
		{
			assert(false);
			std::terminate();
		}
	}

	constexpr void assert_not_empty() const
	{
		assert_not_empty(container);
	}

	T container;
};

#endif
