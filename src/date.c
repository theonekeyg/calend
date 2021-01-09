#include "calend.h"

/*
  January - 31 days
  February - 28 days in a common year and 29 days in leap years
  March - 31 days

  April - 30 days
  May - 31 days
  June - 30 days

  July - 31 days
  August - 31 days
  September - 30 days

  October - 31 days
  November - 30 days
  December - 31 days
*/

const int DAYS_IN_MONTH[12] = {
  31, 28, 31,
  30, 31, 30,
  31, 31, 30,
  31, 30, 31
};

char *
day_to_str(enum Days day) {
  switch (day) {
    case Monday:
      return "Monday";
    case Tuesday:
      return "Tuesday";
    case Wednesday:
      return "Wednesday";
    case Thursday:
      return "Thursday";
    case Friday:
      return "Friday";
    case Saturday:
      return "Saturday";
    case Sunday:
      return "Sunday";
  }
  return "";
}

char *
mon_to_str(enum Months mon) {
  switch (mon) {
    case January:
      return "January";
    case February:
      return "February";
    case March:
      return "March";
    case April:
      return "April";
    case May:
      return "May";
    case June:
      return "June";
    case July:
      return "July";
    case August:
      return "August";
    case September:
      return "September";
    case October:
      return "October";
    case November:
      return "November";
    case December:
      return "December";
  }
  return "";
}

int
month_init(month_t *month) {
  time_t current;
  if (time(&current) == -1) {
    return 1;
  }
  /* TODO: calculate needed data without using bloated localtime
   * Very useful paper: https://howardhinnant.github.io/date_algorithms.html */
  struct tm *timeinfo = localtime(&current);
  /* By default tm_wday represents offset from sunday by 0, transform
   * it to european scale (week starts at mondays) */
  /* timeinfo->tm_wday = timeinfo->tm_wday ? timeinfo->tm_wday - 1 : Sunday; */
  month->mon = timeinfo->tm_mon;
  month->year = timeinfo->tm_year + 1900;
  month->today = timeinfo->tm_mday;
  month->ndays = DAYS_IN_MONTH[month->mon];
  month->offset = (timeinfo->tm_wday - ((month->today % 7) - 1)) & 0x7;
  month->nweeks = (month->ndays + month->offset) / 7 + 1;
  return 0;
}
