#include "Storage.hpp"

#include "Path.hpp"

#include <string>
#include <map>
#include <vector>
#include<fstream>

#include <cstddef>
#include<cstring>

using std::map;
using std::string;

std::shared_ptr<Storage> Storage::m_instance = nullptr;
  /**
 *   default constructor
  */
  Storage::Storage() {
      m_dirty = false;
      readFromFile();
  }


  /**
  *   read file content into memory
  *   @return if success, true will be returned
  */
  bool Storage::readFromFile(void) {
      std::ifstream user_file;
      user_file.open(Path::userPath);
      if (!user_file) return false;
      map<int, string> stringMap;
      for (int i = 0; !user_file.eof(); i++) {
          std::getline(user_file, stringMap[i], '\n');
      }
      for (auto iterator = stringMap.begin(); iterator != stringMap.end(); iterator++) {
          if (iterator == stringMap.begin() || iterator == (--stringMap.end()))
               continue;
          std::size_t first_comma = (iterator->second).find_first_of(",");
        string username = (iterator->second).substr(1, first_comma - 2);
        std::size_t second_comma = (iterator->second).find_first_of(",", first_comma + 1);
        string password = (iterator->second).substr(first_comma + 2, second_comma - first_comma - 3);
        std::size_t third_comma = (iterator->second).find_first_of(",", second_comma + 1);
        string email = (iterator->second).substr(second_comma + 2, third_comma - second_comma - 3);
        string phone = (iterator->second).substr(third_comma + 2, (iterator->second).length() - third_comma - 3);
        m_userList.push_back(User(username, password, email, phone));
    }
    user_file.close();
    stringMap.clear();

    std::ifstream meeting_file;
    meeting_file.open(Path::meetingPath);
    if (!meeting_file) return false;
    for (int i = 0; !meeting_file.eof(); i++) {
        std::getline(meeting_file, stringMap[i], '\n');
    }
    for (auto iterator = stringMap.begin(); iterator != stringMap.end(); iterator++) {
        if (iterator == stringMap.begin() || iterator == (--stringMap.end()))
               continue;
        std::size_t first_comma = (iterator->second).find_first_of(",");
      string sponsor = (iterator->second).substr(1, first_comma - 2);
      std::size_t second_comma = (iterator->second).find_first_of(",", first_comma + 1);
      string participators = (iterator->second).substr(first_comma + 2, second_comma - first_comma - 3);
      std::size_t third_comma = (iterator->second).find_first_of(",", second_comma + 1);
      string startDate = (iterator->second).substr(second_comma + 2, third_comma - second_comma - 3);
      std::size_t fourth_comma = (iterator->second).find_first_of(",", third_comma + 1);
      string endDate = (iterator->second).substr(third_comma + 2, fourth_comma - third_comma - 3);
      string title = (iterator->second).substr(fourth_comma + 2, (iterator->second).length() - fourth_comma - 3);
      std::vector<string> vec_participators;
      std::size_t found = participators.find("&");
      if (found == std::string::npos) {
          vec_participators.push_back(participators);
      } else {
          char * cstring = new char[participators.length() + 1];
          strcpy(cstring, participators.c_str());
          char* p = strtok(cstring, "&");
          vec_participators.push_back(p);
          while (p != NULL) {
              p = strtok(NULL, "&");
              if (p != NULL) vec_participators.push_back(p);
          }
          delete [] cstring;
      }
      m_meetingList.push_back(Meeting(sponsor, vec_participators, startDate, endDate, title));
  }
  user_file.close();
  return true;
  }



  /**
   *
  *   write file content from memory
  *   @return if success, true will be returned
  */
  bool Storage::writeToFile(void) {
      std::ofstream user_file;
      user_file.open(Path::userPath);
      if (!user_file) return false;
      user_file << "\"name\",\"password\",\"email\",\"phone\"\n";
      for (auto user : m_userList) {
          user_file << "\"" << user.getName() << "\","
          << "\"" << user.getPassword() << "\","
          << "\"" << user.getEmail() << "\","
          << "\"" << user.getPhone() << "\"\n";
      }
      user_file.close();
      std::ofstream meeting_file;
      meeting_file.open(Path::meetingPath);
      if (!meeting_file) return false;
      meeting_file << "\"sponsor\",\"participator\",\"start date\",\"end date\",\"title\"\n";
      for (auto meeting : m_meetingList) {
          meeting_file << "\"" << meeting.getSponsor() << "\",\"";
          std::vector<std::string> vec_participators = meeting.getParticipator();
          for (auto iterator = vec_participators.begin(); iterator != (--vec_participators.end()); iterator++) {
              meeting_file << *iterator << "&";
          }
          meeting_file << *(--vec_participators.end()) << "\",";
          meeting_file << "\"" << Date::dateToString(meeting.getStartDate()) << "\","
          << "\"" << Date::dateToString(meeting.getEndDate()) << "\","
          << "\"" << meeting.getTitle() << "\"\n";
      }
      m_dirty = false;
      return true;
  }

  /**
  * get Instance of storage
  * @return the pointer of the instance
  */
  std::shared_ptr<Storage> Storage::getInstance(void) {
      if (m_instance == nullptr)
      m_instance = std::shared_ptr<Storage>(new Storage);
       return m_instance;
  }

  /**
  *   destructor
  */
  Storage::~Storage() {
      sync();
  }

  // CRUD for User & Meeting
  // using C++11 Function Template and Lambda Expressions

  /**
  * create a user
  * @param a user object
  */
  void Storage::createUser(const User & t_user) {
      m_userList.push_back(t_user);
      m_dirty = true;
  }

  /**
  * query users
  * @param a lambda function as the filter
  * @return a list of fitted users
  */
  std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) const {
      std::list<User> queriedUsers;
      for (auto user : m_userList) {
          if (filter(user)) {
              queriedUsers.push_back(user);
          }
      }
      return queriedUsers;
  }
  /**
  * update users
  * @param a lambda function as the filter
  * @param a lambda function as the method to update the user
  * @return the number of updated users
  */
  int Storage::updateUser(std::function<bool(const User &)> filter,
                 std::function<void(User &)> switcher) {
                     int count = 0;
                     for (auto &user : m_userList) {
                         if (filter(user)) {
                             switcher(user);
                             count++;
                         }
                     }
                     return count;
                 }

  /**
  * delete users
  * @param a lambda function as the filter
  * @return the number of deleted users
  */
  int Storage::deleteUser(std::function<bool(const User &)> filter) {
      int count = 0;
      auto iterator = m_userList.begin();
      while(iterator != m_userList.end()) {
          if (filter(*iterator)) {
              iterator = m_userList.erase(iterator);
              count++;
          } else {
              iterator++;
          }
      }
      m_dirty = true;
      return count;
  }

  /**
  * create a meeting
  * @param a meeting object
  */
  void Storage::createMeeting(const Meeting & t_meeting) {
      m_meetingList.push_back(t_meeting);
      m_dirty = true;
  }

  /**
  * query meetings
  * @param a lambda function as the filter
  * @return a list of fitted meetings
  */
  std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting & meeting)> filter) const {
      std::list<Meeting> queriedMeetings;
      for (auto &meeting : m_meetingList) {
          if (filter(meeting)) {
              queriedMeetings.push_back(meeting);
          }
      }
      return queriedMeetings;
  }

  /**
  * update meetings
  * @param a lambda function as the filter
  * @param a lambda function as the method to update the meeting
  * @return the number of updated meetings
  */
  int Storage::updateMeeting(std::function<bool(const Meeting &meeting)> filter,
                    std::function<void(Meeting &)> switcher) {
                        int count = 0;
                        for (auto &meeting : m_meetingList) {
                            if (filter(meeting)) {
                                switcher(meeting);
                                count++;
                            }
                        }
                        return count;
                    }

  /**
  * update meetings
  * @param a lambda function as the filter
  * @return the number of deleted meetings
  */
  int Storage::deleteMeeting(std::function<bool(const Meeting &meeting)> filter) {
      int count = 0;
      auto iterator = m_meetingList.begin();
      while(iterator != m_meetingList.end()) {
          if (filter(*iterator)) {
              iterator = m_meetingList.erase(iterator);
              count++;
          } else {
              iterator++;
          }
      }
      m_dirty = true;
      return count;
  }

  /**
  * sync with the file
  */
  bool Storage::sync(void) {
      if (m_dirty)
      return writeToFile();
      return true;
  }
