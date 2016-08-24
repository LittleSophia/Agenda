#include "User.hpp"
#include <gtest/gtest.h>
#include <string>

TEST(UserTest, SetAndGet) {
  User user;
  user.setName("Clown");
  EXPECT_STREQ("Clown", user.getName().c_str())
  << "Test for getName() fails\n";
  user.setPassword("55555555");
  EXPECT_STREQ("55555555", user.getPassword().c_str())
  << "Test for getPassword() fails\n";
  user.setEmail("jyungoaa@sohei.com");
  EXPECT_STREQ("jyungoaa@sohei.com", user.getEmail().c_str())
  << "Test for getEmail() fails\n";
  user.setPhone("999");
  EXPECT_STREQ("999", user.getPhone().c_str())
  << "Test for getPhone() fails\n";
}
