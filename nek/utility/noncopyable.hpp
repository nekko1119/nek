﻿#ifndef nek_utility_noncopyable_hpp
#define nek_utility_noncopyable_hpp

namespace nek
{
    // protection from ADL
    namespace noncopyable_
    {
        // using CRTP is a solution of EBCO with multiple inheritance.
        template <class T>
        class noncopyable
        {
        protected:
            noncopyable() = default;
            ~noncopyable() = default; // protected non virtual destructor
            noncopyable(noncopyable const&) = delete;
            noncopyable& operator=(noncopyable const&) = delete;
        };
    }

    template <class T>
    using noncopyable = noncopyable_::noncopyable<T>;
}

#endif
