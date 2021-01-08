#ifndef _H_CALEND
#define _H_CALEND

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LIKELY(x)   __builtin_expect((x), 1)
#define UNLIKELY(x) __builtin_expect((x), 0)

#define SPACE_X 4
#define N_DAYS 7

enum Months {
  January = 0,
  February,
  March,
  April,
  May,
  June,
  July,
  August,
  September,
  October,
  November,
  December
};

enum Days {
  Monday = 0,
  Tuesday,
  Wednesday,
  Thursday,
  Friday,
  Saturday,
  Sunday,
};

typedef struct {
  int offset;
  int ndays;
  int mon;
  int year;
  int today;
  int nweeks;
} month_t;

int month_init(month_t *month);
char *day_to_str(enum Days day);
char *mon_to_str(enum Months mon);

#endif // _H_CALEND
