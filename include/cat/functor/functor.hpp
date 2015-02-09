#pragma once

#include <utility>

#include <cat/bits/traits.hpp>
#include <cat/bits/typelist.hpp>

namespace cat
{
    //
    // Class Functor
    //

    template <template <typename ...> class F>
    struct Functor
    {
        template <typename Fun, typename A, typename ...Args>
        struct Class
        {
            virtual auto fmap(Fun f, F<A, Args...> const & f_a)
                -> F<decltype(f(std::declval<A>())),
                     rebind_t<Args, decltype(f(std::declval<A>()))>...> = 0;
        };

        template <typename Fun, typename K, typename A, typename ...Args>
        struct Class1
        {
            virtual auto fmap(Fun f, F<K, A, Args...> const & f_a) -> F<K, decltype(f(std::declval<A>()))> = 0;
        };

    };

    template <template <typename ...> class F, typename ...> struct FunctorInstance;

    template <template <typename ...> class F, typename Fun, typename ...A>
    auto fmap(Fun f, F<A...> const &xs)
    {
        return FunctorInstance<F, Fun, A...>{}.fmap(f, xs);
    }

    //
    // constraint:
    //

    template <template <typename...> class F>
    constexpr bool is_functor()
    {
        return true;
    };


} // namespace cat

