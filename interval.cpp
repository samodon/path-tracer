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
