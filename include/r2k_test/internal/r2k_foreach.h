#ifndef R2K_FOREACH_H
#define R2K_FOREACH_H

#include <stddef.h>

/**
 * foreach loop for array of items
 *
 * Implemented with two for loops; the outer loop iterates and the inner loop
 * exists to assign the current item to the `item` variable. The dummy variable
 * is used to run the inner loop only once.
 *
 * note: does not work for multi-dimensional arrays (e.g. int items[3][4])
 *
 * based on: https://stackoverflow.com/a/400970
 *
 * example:
 *
 * int array[3] = {1, 2, 3};
 * foreach (int* item, array, 3) {
 *     printf("%d\n", *item);
 * }
 *
 * @param item pointer declaration, e.g. int* item
 * @param items an array to iterate over
 * @param num_items the size of the `items` array
 */
#define foreach(item, items, num_items) \
    for (size_t dummy = 1, count = 0; \
        dummy && count != num_items; \
        dummy = !dummy, count++) \
      for (item = (items) + count; dummy; dummy = !dummy)

#endif // R2K_FOREACH_H
