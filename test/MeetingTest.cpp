#include "Meeting.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>

TEST(MeetingTest, SetAndGet) {
  Meeting meeting;
  meeting.setSponsor("Clown");
  EXPECT_STREQ("Clown", meeting.getSponsor().c_str())
  << "Test for getSponsor() fails\n";
  std::vector<std::string> vec;
  for (int i = 0; i < 100; i++) {
    char ch = i + '0';
    std::string temp = "participator";
    temp += ch;
    vec.push_back(temp);
  }
  meeting.setParticipator(vec);
  EXPECT_EQ(vec, meeting.getParticipator())
  << "Test for getParticipator() fails\n";
  Date t_start = Date::stringToDate("2016-8-19/00:00");
  meeting.setStartDate(t_start);
  EXPECT_EQ(t_start, meeting.getStartDate())
  << "Test for getStartDate() fails\n";
  Date t_end = Date::stringToDate("2016-8-23/23:59");
  meeting.setEndDate(t_end);
  EXPECT_EQ(t_end, meeting.getEndDate())
  << "Test for getEndDate() fails\n";
  meeting.setTitle("Boring");
  EXPECT_STREQ("Boring", meeting.getTitle().c_str())
  << "Test for getTitle() fails\n";
}
