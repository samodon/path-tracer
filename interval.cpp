#include "interval.h"
const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);

double interval::clamp(double x) const {
  if (x < min)
    return min;
  if (x > max)
    return max;
  return x;
}

interval interval::expand(double delta) const {
  auto padding = delta / 2;
  return interval(min - padding, max + padding);
}
