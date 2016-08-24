#include "Date.hpp"

#include<iostream>
#include<sstream>

#include<cstring>
#include<cstdlib>
#include<cctype>

  /**
  * @brief default constructor
  */
  Date::Date() {
      m_year = 0;
      m_month = 0;
      m_day = 0;
      m_hour = 0;
      m_minute = 0;
  }

  /**
  * @brief constructor with arguments
  */
  Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute) : m_year(t_year),
  m_month(t_month), m_day(t_day), m_hour(t_hour), m_minute(t_minute) {}

  /**
  * @brief constructor with a string
  */
  Date::Date(std::string dateString) {
      Date date = stringToDate(dateString);
      (*this) = date;
  }
  /**
  * @brief return the year of a Date
  * @return   a integer indicate the year of a date
  */
  int Date::getYear(void) const {
      return this->m_year;
  }

  /**
  * @brief set the year of a date
  * @param a integer indicate the new year of a date
  */
  void Date::setYear(const int t_year) {
      this->m_year = t_year;
  }

  /**
  * @brief return the month of a Date
  * @return   a integer indicate the month of a date
  */
  int Date::getMonth(void) const {
      return this->m_month;
  }

  /**
  * @brief set the month of a date
  * @param a integer indicate the new month of a date
  */
  void Date::setMonth(const int t_month) {
      this->m_month = t_month;
  }

  /**
  * @brief return the day of a Date
  * @return   a integer indicate the day of a date
  */
  int Date::getDay(void) const {
      return this->m_day;
  }

  /**
  * @brief set the day of a date
  * @param a integer indicate the new day of a date
  */
  void Date::setDay(const int t_day) {
      this->m_day = t_day;
  }

  /**
  * @brief return the hour of a Date
  * @return   a integer indicate the hour of a date
  */
  int Date::getHour(void) const {
      return this->m_hour;
  }

  /**
  * @brief set the hour of a date
  * @param a integer indicate the new hour of a date
  */
  void Date::setHour(const int t_hour) {
      this->m_hour = t_hour;
  }

  /**
  * @brief return the minute of a Date
  * @return   a integer indicate the minute of a date
  */
  int Date::getMinute(void) const {
      return this->m_minute;
  }

  /**
  * @brief set the minute of a date
  * @param a integer indicate the new minute of a date
  */
  void Date::setMinute(const int t_minute) {
      this->m_minute = t_minute;
  }

  /**
  *   @brief check whether the date is valid or not
  *   @return the bool indicate valid or not
  */
  bool Date::isValid(const Date t_date) {
      if (t_date.m_year < 1000 || t_date.m_year > 9999) return false;
      if (t_date.m_month <= 0 || t_date.m_month > 12) return false;
      if (t_date.m_day <= 0 || t_date.m_day > 31) return false;
      if (t_date.m_hour < 0 || t_date.m_hour > 24) return false;
      if (t_date.m_minute < 0 || t_date.m_minute >= 60) return false;
      if (t_date.m_hour == 24 && t_date.m_minute != 0) return false;
      if ((t_date.m_month % 2 == 1 && t_date.m_month < 8) || (t_date.m_month % 2 == 0 && t_date.m_month >= 8)) {
          if (t_date.m_day > 31) return false;
      }
      else if (t_date.m_month  == 4 || t_date.m_month == 6 || t_date.m_month == 9 || t_date.m_month == 11) {
          if (t_date.m_day > 30) return false;
      }
      else if ((t_date.m_year % 4 == 0 && t_date.m_year % 100 != 0) || t_date.m_year % 400 == 0) {
          if (t_date.m_day > 29) return false;
      }
      else {
          if (t_date.m_day > 28) return false;
      }
      return true;
  }
  /**
  * @brief convert a string to date, if the format is not correct return
  * 0000-00-00/00:00
  * @return a date
  */
  Date Date::stringToDate(const std::string t_dateString) {
      if (t_dateString.length() != 16) return Date(std::string("0000-00-00/00:00"));
      if (!isdigit(t_dateString[0]) || !isdigit(t_dateString[1]) || !isdigit(t_dateString[2])
      || !isdigit(t_dateString[3]) || t_dateString[4] != '-' || !isdigit(t_dateString[5])
      || !isdigit(t_dateString[6]) || t_dateString[7] != '-'  || !isdigit(t_dateString[8])
      || !isdigit(t_dateString[9]) || t_dateString[10] != '/' || !isdigit(t_dateString[11])
      || !isdigit(t_dateString[12]) || t_dateString[13] != ':' || !isdigit(t_dateString[14])
      || !isdigit(t_dateString[15])) {
          return Date(std::string("0000-00-00/00:00"));
      } else {
          Date date;
          date.m_year = stoi(t_dateString.substr(0, 4));
          date.m_month = stoi(t_dateString.substr(5, 2));
          date.m_day = stoi(t_dateString.substr(8, 2));
          date.m_hour = stoi(t_dateString.substr(11, 2));
          date.m_minute = stoi(t_dateString.substr(14, 2));
          return date;
      }
  }

  /**
  * @brief convert a date to string, if the format is not correct return
  * 0000-00-00/00:00
  */
  std::string Date::dateToString(Date t_date) {
      if (!isValid(t_date)) return "0000-00-00/00:00";
      std::string date_str;
      std::stringstream ss;
      ss << t_date.m_year;
      date_str += ss.str() + "-";
      ss.str("");
      ss << t_date.m_month;
      if (t_date.m_month < 10) date_str += "0";
      date_str += ss.str() + "-";
      ss.str("");
      ss << t_date.m_day;
      if (t_date.m_day < 10) date_str += "0";
      date_str += ss.str() + "/";
      ss.str("");
      ss << t_date.m_hour;
      if (t_date.m_hour < 10) date_str += "0";
      date_str += ss.str() + ":";
      ss.str("");
      ss << t_date.m_minute;
      if (t_date.m_minute < 10) date_str += "0";
      date_str += ss.str();
      return date_str;
  }

  /**
  *  @brief overload the assign operator
  */
  Date& Date::operator=(const Date &t_date) {
      if (this == &t_date) return *this;
      this->m_year = t_date.m_year;
      this->m_month = t_date.m_month;
      this->m_day = t_date.m_day;
      this->m_hour = t_date.m_hour;
      this->m_minute = t_date.m_minute;
      return *this;
  }

  /**
  * @brief check whether the CurrentDate is equal to the t_date
  */
  bool Date::operator==(const Date &t_date) const {
      if (this->m_year != t_date.m_year) return false;
      if (this->m_month != t_date.m_month) return false;
      if (this->m_day != t_date.m_day) return false;
      if (this->m_hour != t_date.m_hour) return false;
      if (this->m_minute != t_date.m_minute) return false;
      return true;
  }

  /**
  * @brief check whether the CurrentDate is  greater than the t_date
  */
  bool Date::operator>(const Date &t_date) const {
      if (*this == t_date || *this < t_date) return false;
      return true;
  }

  /**
  * @brief check whether the CurrentDate is  less than the t_date
  */
  bool Date::operator<(const Date &t_date) const {
     if (m_year < t_date.m_year) return true;
     if (m_year > t_date.m_year) return false;
     if (m_month < t_date.m_month) return true;
     if (m_month > t_date.m_month) return false;
     if (m_day < t_date.m_day) return true;
     if (m_day > t_date.m_day) return false;
     if (m_hour < t_date.m_hour) return true;
     if (m_hour > t_date.m_hour) return false;
     if (m_minute < t_date.m_minute) return true;
     if (m_minute > t_date.m_minute) return false;
     return false;
  }

  /**
  * @brief check whether the CurrentDate is  greater or equal than the t_date
  */
  bool Date::operator>=(const Date &t_date) const {
      return !(*this < t_date);
  }

  /**
  * @brief check whether the CurrentDate is  less than or equal to the t_date
  */
  bool Date::operator<=(const Date &t_date) const {
      return (*this < t_date || *this == t_date);
  }
