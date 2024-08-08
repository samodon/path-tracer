#ifndef INTERVAL_H
#define INTERVAL_H
#include "util.h"

class interval {
public:
  double min, max;

  interval() : min(+infinity), max(-infinity) {} // Default interval is empty

  interval(double min, double max) : min(min), max(max) {}

  double size() const { return max - min; }

  bool contains(double x) const { return min <= x && x <= max; }

  bool surrounds(double x) const { return min < x && x < max; }

  static const interval empty, universe;

  double clamp(double x) const;
};

#endif
