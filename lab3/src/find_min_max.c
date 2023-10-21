#include "find_min_max.h"

#include <limits.h>
#include <assert.h>

struct MinMax GetMinMax(int *array, unsigned int start_idx, unsigned int end_idx) {
  assert(("Начальный индекс больше конечного!", start_idx <= end_idx));
  struct MinMax min_max;
  int max = array[start_idx], min = max;
  for (unsigned i = ++start_idx; i < end_idx + 1; ++i) {
    int k = array[i];
    if (k > max)
      max = k;
    else if (k < min)
      min = k;    
  }
  min_max.min = min;
  min_max.max = max;
  return min_max;
}
