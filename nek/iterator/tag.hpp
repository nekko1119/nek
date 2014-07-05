#ifndef NEK_ITERATOR_TAG_HPP
#define NEK_ITERATOR_TAG_HPP

namespace nek
{
  struct input_iterator_tag
  {
  };

  struct output_iterator_tag
  {
  };

  struct forward_iterator_tag
    : public input_iterator_tag
  {
  };

  struct bidirectional_iterator_tag
    : public forward_iterator_tag
  {
  };

  struct random_access_iterator_tag
    :public bidirectional_iterator_tag
  {
  };
}

#endif