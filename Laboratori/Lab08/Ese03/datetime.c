#include "datetime.h"

Key KEYget(Datetime val)
{
    return val.YYYY * 10000 + val.MM * 100 + val.DD + val.hh * 100 + val.mm;
}

int KEYcmp(Key k1, Key k2)
{
    if (k1 > k2)
        return 1;
    else if (k1 == k2)
        return 0;
    return -1;
}