#include "AgendaService.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>

static bool operator==(const User &t_user1, const User &t_user2) {
  if (t_user1.getName() == t_user2.getName() &&
      t_user1.getPassword() == t_user2.getPassword() &&
      t_user1.getEmail() == t_user2.getEmail() &&
      t_user1.getPhone() == t_user2.getPhone())
    return true;
  return false;
}

static bool operator==(const Meeting &t_meeting1, const Meeting &t_meeting2) {
  if (t_meeting1.getSponsor() == t_meeting2.getSponsor() &&
      t_meeting1.getParticipator() == t_meeting2.getParticipator() &&
      t_meeting1.getStartDate() == t_meeting2.getStartDate() &&
      t_meeting1.getEndDate() == t_meeting2.getEndDate() &&
      t_meeting1.getTitle() == t_meeting2.getTitle())
    return true;
  return false;
}

TEST(AgendaServiceTest, CreateAndListAndDelete) {
    AgendaService testService;
    testService.startAgenda();
    testService.userRegister("clown", "222222", "a@a.com", "333333");
    testService.userRegister("bastard", "222222", "a@a.com", "333333");
    testService.userRegister("dutchman", "222222", "a@a.com", "333333");
    testService.userRegister("lonelyguy", "222222", "a@a.com", "333333");
    std::vector<std::string> v;
    v.push_back("clown");
    v.push_back("bastard");
    v.push_back("dutchman");
    std::vector<std::string> c(v);
    testService.createMeeting("lonelyguy", "t1", "2016-08-19/08:30", "2016-08-19/09:30", v);
    testService.createMeeting("lonelyguy", "t2", "2016-08-19/10:30", "2016-08-19/11:30", v);
    testService.createMeeting("lonelyguy", "t3", "2016-08-19/12:30", "2016-08-19/13:30", v);
    testService.createMeeting("lonelyguy", "t4", "2016-08-19/14:30", "2016-08-19/15:30", v);
    testService.createMeeting("lonelyguy", "t5", "2016-08-19/16:30", "2016-08-19/17:30", v);
    v.pop_back();
    testService.createMeeting("lonelyguy", "t6", "2016-08-19/18:30", "2016-08-19/19:30", v);

    bool test_1 = testService.createMeeting("joker", "t2", "2016-08-19/10:30",
                                            "2016-08-19/11:30", v);
    EXPECT_FALSE(test_1) << "[error] Create a meeting for an user who doesn't exist\n";
    bool test_2 = testService.createMeeting("lonelyguy", "t1", "2016-08-19/14:30",
                                            "2016-08-19/15:30", v);
    EXPECT_FALSE(test_2) << "[error] Create a meeting which has title conflict\n";
    bool test_3 = testService.createMeeting("clown", "t3", "2016-08-19/16:30",
                                            "2016-08-19/17:30", v);
    EXPECT_FALSE(test_3) << "[error] Participators have sponsor\n";
    bool test_4 = testService.createMeeting("lonelyguy", "t4", "2016-08-19/09:00",
                                            "2016-08-19/11:30", v);
    EXPECT_FALSE(test_4) << "[error] Time conflict:\n";
    bool test_5 = testService.createMeeting("lonelyguy", "t5", "2016-08-19/07:00",
                                            "2016-08-19/09:00", v);
    EXPECT_FALSE(test_5) << "[error] Time conflict:\n";
    bool test_6 = testService.createMeeting("lonelyguy", "t6", "2016-08-19/09:00",
                                            "2016-08-19/09:10", v);
    EXPECT_FALSE(test_6) << "[error] Time conflict:\n";
    bool test_7 = testService.createMeeting("lonelyguy", "t7", "2016-08-19/07:00",
                                            "2016-08-19/19:30", v);
    EXPECT_FALSE(test_7) << "[error] Time conflict:\n";
    bool test_8 = testService.createMeeting("lonelyguys", "t8", "2016-08-19/19:00",
                                            "2016-08-19/09:30", v);
    EXPECT_FALSE(test_8) << "[error] start >= end:\n";
    c.push_back("sadman");
    bool test_9 = testService.createMeeting("lonelyguys", "t9", "2016-08-19/20:00",
                                            "2016-08-19/23:30", c);
    EXPECT_FALSE(test_9) << "[error] create a meeting with an user who doesn't exist\n";

    EXPECT_EQ(4, testService.listAllUsers().size()) << "[error] List all users fails\n";
    EXPECT_EQ(6, testService.listAllMeetings("lonelyguy").size()) << "[error] List all meetings fails\n";
    EXPECT_EQ(6, testService.listAllSponsorMeetings("lonelyguy").size()) << "[error] List all sponsor meetings fails\n";
    EXPECT_EQ(6, testService.listAllParticipateMeetings("clown").size()) << "[error] List all participate meetings fails\n";
    EXPECT_TRUE(testService.deleteMeeting("lonelyguy", "t1")) << "[error] Delete meeting by title fails\n";
    EXPECT_TRUE(testService.deleteUser("dutchman", "222222")) << "[error] Delete user fails\n";
    EXPECT_EQ(3, testService.listAllUsers().size()) << "[error] Delete user fails\n";
    EXPECT_EQ(1, testService.listAllMeetings("lonelyguy").size()) << "[error] Delete user fails\n";
    EXPECT_TRUE(testService.deleteAllMeetings("lonelyguy")) << "[error] Delete all meetings fails\n";
    EXPECT_EQ(0, testService.listAllMeetings("lonelyguy").size()) << "[error] Delete all meetings fails\n";
}
