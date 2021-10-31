#include "DisjointSet.h"

#include <stdio.h>

int main()
{
    DisjointSet set;

    Initialize(&set, 10);

    UnionElement(&set, 3, 0);
    UnionElement(&set, 3, 1);
    UnionElement(&set, 3, 2);
    UnionElement(&set, 7, 4);
    UnionElement(&set, 7, 5);
    UnionElement(&set, 7, 6);
    UnionElement(&set, 9, 8);

    /**
     *    3       7       9
     *    0 1 2   4 5 6   8
     */

     /**
      * => [0] value is [3]
      * => [1] value is [3]
      * => [2] value is [3]
      * => [3] value is [-1]
      * => [4] value is [7]
      * => [5] value is [7]
      * => [6] value is [7]
      * => [7] value is [-1]
      * => [8] value is [9]
      * => [9] value is [-1]
      */
    for (int i = 0; i < 10; i++)
    {
        printf("[%d] value is [%d]\n", i, ValueOfIndex(&set, i));
    }

    /**
     * => [0] root is [3]
     * => [1] root is [3]
     * => [2] root is [3]
     * => [3] root is [3]
     * => [4] root is [7]
     * => [5] root is [7]
     * => [6] root is [7]
     * => [7] root is [7]
     * => [8] root is [9]
     * => [9] root is [9]
     */
    for (int i = 0; i < 10; i++)
    {
        printf("[%d] root is [%d]\n", i, FindRoot(&set, i));
    }

    return 0;
}
