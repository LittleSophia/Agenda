#include "Date.hpp"
#include <gtest/gtest.h>
#include <string>

TEST(DateTest, isValid) {
    Date date1(2015, 8, 19, 20, 10);
    Date date2(2016, 2, 30, 1, 12);
    EXPECT_TRUE(Date::isValid(date1)) << "Test for true fails\n";
    EXPECT_FALSE(Date::isValid(date2)) << "Test for false fails\n";
}

TEST(DateTest, overloadedOperator) {
    Date blankDate;
    Date date1(2015, 8, 19, 20, 10);
    Date date2(2015, 8, 19, 20, 10);
    Date date3(2016, 7, 19, 9, 1);
    Date date4(date3);
    Date date5(1984, 3, 20, 1, 59);
    EXPECT_EQ(blankDate, Date::stringToDate("16-08-19/00:00"))
    << "Test_One for operator== fails\n"
    << "Possible problems: 1-default constructor 2-stringToDate 3-operator==\n";
    EXPECT_EQ(date3, date4)
    << "Test_Two for operator== fails\n"
    << "Possible problems: 1-copy constructor 2-operator==\n";
    EXPECT_LT(date1, date3)
    << "Test for operator< fails\n"
    << "Possible problems: operator<\n";
    EXPECT_LE(date1, date3)
    << "Test_One for operator<= (the part of <) fails\n"
    << "Possible problems: operator<=\n";
    EXPECT_LE(date1, date2)
    << "Test_Two for operator<= (the part of =) fails\n"
    << "Possible problems: operator<=\n";
    EXPECT_GT(date3, date5)
    << "Test for operator> fails\n"
    << "Possible problems: operator>\n";
    EXPECT_GE(date3, date5)
    << "Test_One for operator>= (the part of >) fails\n"
    << "Possible problems: operator>=\n";
    EXPECT_GE(date1, date2)
    << "Test_One for operator>= (the part of =) fails\n"
    << "Possible problems: operator>=\n";
}

TEST(DateTest, dateToString) {
    Date date(2016, 7, 19, 9, 1);
    EXPECT_STREQ("2016-07-19/09:01", Date::dateToString(date).c_str())
    << "Test for dateToString fails\n";
}

TEST(DateTest, stringToDate) {
    Date date(1984, 3, 20, 1, 59);
    EXPECT_EQ(date, Date::stringToDate("1984-03-20/01:59"))
    << "Test for stringToDate fails\n";
}
