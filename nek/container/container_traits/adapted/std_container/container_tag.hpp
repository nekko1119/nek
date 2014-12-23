#ifndef NEK_CONTAINER_CONTAINER_TRAITS_ADAPTED_STD_CONTAINER_CONTAINER_TAG_HPP
#define NEK_CONTAINER_CONTAINER_TRAITS_ADAPTED_STD_CONTAINER_CONTAINER_TAG_HPP

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace nek
{
    namespace container_traits
    {
        struct std_container_tag;

        template <class>
        struct container_tag;

        template <class T, std::size_t N>
        struct container_tag<std::array<T, N>>
        {
            using type = std_container_tag;
        };

        template <class T, class A>
        struct container_tag<std::deque<T, A>>
        {
            using type = std_container_tag;
        };

        template <class T, class A>
        struct container_tag<std::forward_list<T, A>>
        {
            using type = std_container_tag;
        };

        template <class T, class A>
        struct container_tag<std::list<T, A>>
        {
            using type = std_container_tag;
        };

        template <class K, class V, class Comp, class A>
        struct container_tag<std::map<K, V, Comp, A>>
        {
            using type = std_container_tag;
        };

        template <class K, class V, class Comp, class A>
        struct container_tag<std::multimap<K, V, Comp, A>>
        {
            using type = std_container_tag;
        };

        template <class T, class Comp, class A>
        struct container_tag<std::set<T, Comp, A>>
        {
            using type = std_container_tag;
        };

        template <class T, class Comp, class A>
        struct container_tag<std::multiset<T, Comp, A>>
        {
            using type = std_container_tag;
        };

        template <class T, class Hash, class Comp, class A>
        struct container_tag<std::unordered_set<T, Hash, Comp, A>>
        {
            using type = std_container_tag;
        };

        template <class T, class Hash, class Comp, class A>
        struct container_tag<std::unordered_multiset<T, Hash, Comp, A>>
        {
            using type = std_container_tag;
        };

        template <class K, class V, class Hash, class Comp, class A>
        struct container_tag<std::unordered_map<K, V, Hash, Comp, A>>
        {
            using type = std_container_tag;
        };

        template <class K, class V, class Hash, class Comp, class A>
        struct container_tag<std::unordered_multimap<K, V, Hash, Comp, A>>
        {
            using type = std_container_tag;
        };

        template <class T, class A>
        struct container_tag<std::vector<T, A>>
        {
            using type = std_container_tag;
        };
    }
}

#endif
