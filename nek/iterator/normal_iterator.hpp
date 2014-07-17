#ifndef NEK_ITERATOR_NORMAL_ITERATOR_HPP
#define NEK_ITERATOR_NORMAL_ITERATOR_HPP

#include <nek/iterator/iterator_traits.hpp>

namespace nek
{
  template <class Iterator>
  class normal_iterator
  {
    Iterator current_;

  public:
    using iterator_type = Iterator;
    using iterator_category = typename iterator_traits<Iterator>::iterator_category;
    using value_type = typename iterator_traits<Iterator>::value_type;
    using difference_type = typename iterator_traits<Iterator>::difference_type;
    using pointer = typename iterator_traits<Iterator>::pointer;
    using reference = typename iterator_traits<Iterator>::reference;

    normal_iterator() = default;

    explicit normal_iterator(iterator_type const& it)
      : current_{it}
    {
    }
  };
}

#endif