#ifndef ESE01_DATETIME_H
#define ESE01_DATETIME_H

typedef int Key;
typedef struct {
    int YYYY, MM, DD;
    int hh, mm;
} Datetime;

// Prototipi
int KEYcmp(Key k1, Key k2);
Key KEYget(Datetime val);

#endif //ESE01_DATETIME_H
