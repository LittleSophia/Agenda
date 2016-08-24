#include "Storage.hpp"
#include <gtest/gtest.h>
#include <list>
#include <vector>

bool operator==(const User &t_user1, const User &t_user2) {
  if (t_user1.getName() == t_user2.getName() &&
      t_user1.getPassword() == t_user2.getPassword() &&
      t_user1.getEmail() == t_user2.getEmail() &&
      t_user1.getPhone() == t_user2.getPhone())
    return true;
  return false;
}

TEST(StorageTest, UserCRUD) {
  std::shared_ptr<Storage> test_instance = Storage::getInstance();
  User test_user_1("userA", "1234", "GaauMatJe@citsin.com", "666666");
  User test_user_2("userS", "1234", "GaauMatJe@citsin.com", "666666");
  User test_user_3("userD", "1234", "GaauMatJe@citsin.com", "666666");
  User test_user_4("userF", "5678", "GaauMatJe@citsin.com", "666666");
  User test_user_5("userG", "5678", "GaauMatJe@citsin.com", "666666");
  User test_user_6("userH", "5678", "GaauMatJe@citsin.com", "666666");
  test_instance->createUser(test_user_1);
  test_instance->createUser(test_user_2);
  test_instance->createUser(test_user_3);
  test_instance->createUser(test_user_4);
  test_instance->createUser(test_user_5);
  test_instance->createUser(test_user_6);
  auto test_filter = [&](const User &t_user) {
    return t_user.getPassword() == "5678";
  };
  auto test_switcher = [&](User &t_user) { t_user.setPhone("56565656"); };

  std::list<User> test1;
  test1.push_back(test_user_4);
  test1.push_back(test_user_5);
  test1.push_back(test_user_6);
  std::list<User> result1 = test_instance->queryUser(test_filter);
  EXPECT_EQ(test1, result1)
  << "Test for queryUser fails\n";

  EXPECT_EQ(3, test_instance->updateUser(test_filter, test_switcher))
  << "Test for updateUser fails\n";
  EXPECT_EQ(3, test_instance->deleteUser([&](const User &t_user) {
    return t_user.getPhone() == "56565656";
  }))
  << "Test for deleteUser fails\n";

  std::list<User> test2;
  test2.push_back(test_user_1);
  test2.push_back(test_user_2);
  test2.push_back(test_user_3);
  std::list<User> result2 = test_instance->queryUser([&](const User &t_user) {
    return t_user.getEmail() == "GaauMatJe@citsin.com";
  });
  EXPECT_EQ(test2, result2)
  << "Cannot testify updateUser and deleteUser\n";
}

bool operator==(const Meeting &t_meeting1, const Meeting &t_meeting2) {
  if (t_meeting1.getSponsor() == t_meeting2.getSponsor() &&
      t_meeting1.getParticipator() == t_meeting2.getParticipator() &&
      t_meeting1.getStartDate() == t_meeting2.getStartDate() &&
      t_meeting1.getEndDate() == t_meeting2.getEndDate() &&
      t_meeting1.getTitle() == t_meeting2.getTitle())
    return true;
  return false;
}

TEST(StorageTest, MeetingCRUD) {
  std::shared_ptr<Storage> test_instance = Storage::getInstance();
  std::vector<std::string> test_participators = {"Adam", "Philipe", "Emre",
                                                 "Jordan", "Alberto"};

  Meeting test_meeting_1("Clown", test_participators,
                         Date::stringToDate("1000-10-10/10:10"),
                         Date::stringToDate("1000-12-12/12:12"), "t1");
  Meeting test_meeting_2("Clown", test_participators,
                         Date::stringToDate("1001-10-10/10:10"),
                         Date::stringToDate("1001-12-12/12:12"), "t2");
  Meeting test_meeting_3("Clown", test_participators,
                         Date::stringToDate("1002-10-10/10:10"),
                         Date::stringToDate("1002-12-12/12:12"), "t3");
  Meeting test_meeting_4("Clown", test_participators,
                         Date::stringToDate("2000-10-10/10:10"),
                         Date::stringToDate("2000-12-12/12:12"), "t4");
  Meeting test_meeting_5("Clown", test_participators,
                         Date::stringToDate("2001-10-10/10:10"),
                         Date::stringToDate("2001-12-12/12:12"), "t5");
  Meeting test_meeting_6("Clown", test_participators,
                         Date::stringToDate("2002-10-10/10:10"),
                         Date::stringToDate("2002-12-12/12:12"), "t6");
  test_instance->createMeeting(test_meeting_1);
  test_instance->createMeeting(test_meeting_2);
  test_instance->createMeeting(test_meeting_3);
  test_instance->createMeeting(test_meeting_4);
  test_instance->createMeeting(test_meeting_5);
  test_instance->createMeeting(test_meeting_6);

  auto test_filter = [&](const Meeting &t_meeting) {
    return t_meeting.getStartDate() <= Date::stringToDate("1002-10-10/10:10");
  };
  auto test_switcher = [&](Meeting &t_meeting) { t_meeting.setTitle("t90"); };

  std::list<Meeting> test1;
  test1.push_back(test_meeting_1);
  test1.push_back(test_meeting_2);
  test1.push_back(test_meeting_3);
  std::list<Meeting> result1 = test_instance->queryMeeting(test_filter);
  EXPECT_EQ(test1, result1)
  << "Test for queryMeeting fails\n";

  EXPECT_EQ(3, test_instance->updateMeeting(test_filter, test_switcher))
  << "Test for updateMeeting fails\n";
  EXPECT_EQ(3, test_instance->deleteMeeting([&](const Meeting &t_meeting) {
    return t_meeting.getTitle() == "t90";
  }))
  << "Test for deleteMeeting fails\n";

  std::list<Meeting> test2;
  test2.push_back(test_meeting_4);
  test2.push_back(test_meeting_5);
  test2.push_back(test_meeting_6);
  std::list<Meeting> result2 = test_instance->queryMeeting([&](
      const Meeting &t_meeting) { return t_meeting.getSponsor() == "Clown"; });
  EXPECT_EQ(test2, result2)
  << "Cannot testify updateMeeting and deleteMeeting\n";
}
