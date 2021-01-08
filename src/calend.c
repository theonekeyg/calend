#include "calend.h"

void
print_head(month_t *month, int padding) {
  char *month_name = mon_to_str(month->mon);
  printf("%*c%s%*d\n\n", padding, ' ', month_name,
         N_DAYS * SPACE_X - (int)strlen(month_name), month->year);
  printf("%*c", padding+1, ' ');
  for (int i = Monday; i <= Sunday; ++i) {
    printf("%.3s ", day_to_str(i));
  }
  putchar('\n');
}

void
print_day(month_t *month, int day) {
  if (!day) {
    printf("%*c", 4, ' ');
  } else {
    if (UNLIKELY(day == month->today)) {
      if (day >= 10) {
        printf("\033[32m[%d]\033[m", day);
      } else {
        printf("\033[32m [%d]\033[m", day);
      }
    } else {
      printf("%*d ", 3, day);
    }
  }
}

void
print_calendar_body(month_t *month, int padding) {
  /* Storing dates of the week in the separate array doesn't make sense
   * in current implementation, however, it would be helpful if implementation would use
   * grids instead of plain numbers in output calendar. I'll keep it, until I decide
   * which implementation I like more. */
  int week[7] = { 0, 0, 0, 0, 0, 0, 0 };
  int i, j;
  int last_date;
  for (i = month->offset; i < 7; ++i) {
    week[i] = (i+1) - month->offset;
  }
  for (i = 0; i < month->nweeks; ++i) {
    printf("%*c", padding, ' ');
    for (j = 0; j < N_DAYS; ++j) {
      print_day(month, week[j]);
    }
    putchar('\n');
    for (j = 0, last_date = week[6]+1; j < 7; ++j, ++last_date) {
      week[j] = last_date * (last_date > month->ndays ? 0 : 1);
    }
  }
}

void
print_calendar(month_t *month, int padding) {
  putchar('\n');
  print_head(month, padding);
  print_calendar_body(month, padding);
  putchar('\n');
}

int
main(int argc, char **argv) {
  month_t month;
  if (month_init(&month)) {
    fprintf(stderr, "Unable to get local unix timestamp\n");
    return 1;
  }
  print_calendar(&month, 4);
  return 0;
}
