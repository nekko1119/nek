#ifndef nek_utility_noncopyable_hpp
#define nek_utility_noncopyable_hpp

namespace nek
{
    //protection from ADL
    namespace noncopyable_
    {
        //using CRTP is a solution of EBCO with multiple inheritance.
        template <class T>
        class noncopyable
        {
        protected:
            noncopyable() {}
            ~noncopyable() {}//protected non virtual destructor
        private:
            noncopyable(const noncopyable&);//no defined
            noncopyable& operator=(const noncopyable&);//no defined
        };
    }
    using namespace noncopyable_;
}

#endif