#include "AgendaUI.hpp"

#include <iomanip>

using std::cout;
using std::endl;
using std::cin;

    AgendaUI::AgendaUI() {}

    void AgendaUI::OperationLoop(void) {
        startAgenda();
        cout << endl <<
        "--------------------Agenda ---------------------" << endl <<
        "Action :" << endl <<
        "l   -log in Agenda by user name and password" << endl <<
        "r   -register an Agenda account" << endl <<
        "q   -quit Agenda" << endl <<
        "------------------------------------------------" << endl <<
        "Agenda : ~$ ";
        std::string operation = getOperation();
        if (operation != "l" && operation != "r" && operation != "q") {
            cout << "can't find the operating command" << endl;
        } else {
            if (operation == "l") {
                userLogIn();
            } else if (operation == "r") {
                userRegister();
            } else if (operation == "q") {
                quitAgenda();
            }
        }
    }


    void AgendaUI::printCommand(void) {
        cout << "o   - log out Agenda\n";
        cout << "dc  - delete Agenda account\n";
        cout << "lu  - list all Agenda user\n";
        cout << "cm  - creat a meeting\n";
        cout << "la  - list all meetings\n";
        cout << "las - list all sponsor meetings\n";
        cout << "lap - list all participate meetings\n";
        cout << "qm  - query meetings by title\n";
        cout << "qt  - query meetings by time interval\n";
        cout << "dm  - delete meetings by title\n";
        cout << "da  - delete all meetings\n";
    }

    /**
     * constructor
     */
    void AgendaUI::startAgenda(void) {
        m_agendaService.startAgenda();
    }

    /**
     * catch user's operation
     * @return the operation
     */
    std::string AgendaUI::getOperation() {
        std::string operation;
        cin >> operation;
        return operation;
    }

    /**
     * execute the operation
     * @return if the operationloop continue
     */
    bool AgendaUI::executeOperation(std::string t_operation) {
        if (t_operation == "o") {
            userLogOut();
            return true;
        }
        else if (t_operation == "dc") {
            deleteUser();
            return true;
        } else if (t_operation == "lu") {
            listAllUsers();
            return true;
        } else if (t_operation == "cm") {
            createMeeting();
            return true;
        } else if (t_operation == "la") {
            listAllMeetings();
            return true;
        } else if (t_operation == "las") {
            listAllSponsorMeetings();
            return true;
        } else if (t_operation == "lap") {
            listAllParticipateMeetings();
            return true;
        } else if (t_operation == "qm") {
            queryMeetingByTitle();
            return true;
        } else if (t_operation == "qt") {
            queryMeetingByTimeInterval();
            return true;
        } else if (t_operation == "dm") {
            deleteMeetingByTitle();
            return true;
        } else if (t_operation == "da") {
            deleteAllMeetings();
            return true;
        } else {
            return false;
        }
    }

    /**
     * user Login
     */
    void AgendaUI::userLogIn(void) {
        cout << endl;
        cout << "[log in] [user name] [password]" << endl;
        cout << "[log in] ";
        std::string userName, userPassword;
        cin >> userName >> userPassword;
        m_userName = userName;
        m_userPassword = userPassword;
        int flag = m_agendaService.userLogIn(m_userName, m_userPassword);
        if (flag == 1) {
            OperationLoop();
        } else if (flag == 2) {
            cout << "try to find your forgotten password? \"n\" for \"NO\"" << endl;
            std::string answer;
            cin >> answer;
            if (answer == "n") OperationLoop();
            else {
                std::string email, phone;
                cout << "your email: ";
                cin >> email;
                cout << "your phone: ";
                cin >> phone;
                cout << endl;
                if (!m_agendaService.userQuery(m_userName, email, phone)) {
                    cout << "due to the wrong information,your password can't be found" << endl;
                }
                OperationLoop();
            }
        } else {
            cout << endl;
            cout << "o   - log out Agenda\n";
            cout << "dc  - delete Agenda account\n";
            cout << "lu  - list all Agenda user\n";
            cout << "cm  - creat a meeting\n";
            cout << "la  - list all meetings\n";
            cout << "las - list all sponsor meetings\n";
            cout << "lap - list all participate meetings\n";
            cout << "qm  - query meetings by title\n";
            cout << "qt  - query meetings by time interval\n";
            cout << "dm  - delete meetings by title\n";
            cout << "da  - delete all meetings\n";
            cout << "-------------------------------------------------" << endl;
            cout << "Agenda@" << m_userName << " : # ";
            std::string operation = getOperation();
            if (operation == "o" || operation == "dc" || operation == "lu" ||
            operation == "cm" || operation == "la" || operation == "las" ||
             operation == "lap" || operation == "qm" || operation == "qt" ||
              operation == "dm" || operation == "da") {
                  executeOperation(operation);
              } else {
                  cout << "can't find the operating command" << endl;
                  printCommand();
                  cout << "Agenda@" << m_userName << " : # ";
                  std::string operation = getOperation();
                  bool flag = false;
                  while (!executeOperation(operation)) {
                      cout << "can't find the operating command" << endl;
                      cout << "Agenda@" << m_userName << " : # ";
                      operation = getOperation();
                      if (operation == "o" || operation == "dc" || operation == "lu" ||
                      operation == "cm" || operation == "la" || operation == "las" ||
                       operation == "lap" || operation == "qm" || operation == "qt" ||
                        operation == "dm" || operation == "da") {
                            flag = true;
                            break;
                        }
                  }
                  if (flag) executeOperation(operation);
              }
            }
    }

    /**
     * user regist
     */
    void AgendaUI::userRegister(void) {
        cout << endl;
        cout << "[register] [user name] [password] [email] [phone]" << endl <<
        "[register] ";
        std::string username, password, email, phone;
        cin >> username >> password >> email >> phone;
        if (m_agendaService.userRegister(username, password, email, phone)) {
            cout << "[register] succeed!" << endl;
        } else {
            cout << "[error] register fail!" << endl;
        }
        cout << endl;
        OperationLoop();
    }

    /**
     * quit the Agenda
     */
    void AgendaUI::quitAgenda(void) {
        m_agendaService.quitAgenda();
    }

    /**
     * user logout
     */
    void AgendaUI::userLogOut(void) {
        cout << endl;
        OperationLoop();
    }

    /**
     * delete a user from storage
     */
    void AgendaUI::deleteUser(void) {
        if (m_agendaService.deleteUser(m_userName, m_userPassword)) {
            cout << endl << "[delete agenda account] succeed!" << endl;
        } else {
            cout << endl << "[error] delete user fail" << endl;
        }
        OperationLoop();
    }

    /**
     * list all users from storage
     */
    void AgendaUI::listAllUsers(void) {
        cout << endl << "[list all users]" << endl << endl;
        std::list<User> lu = m_agendaService.listAllUsers();
        cout.setf(std::ios::left);
        cout << std::setw(16) << "name" << std::setw(16) << "email" <<
        std::setw(16) << "phone" << endl;
        for (auto user : lu) {
            cout << std::setw(16) << user.getName() <<
            std::setw(16) << user.getEmail() <<
            std::setw(16) << user.getPhone() << endl;
        }
        cout << endl;
        printCommand();
        cout << "Agenda@" << m_userName << " : # ";
        std::string operation = getOperation();
        while (operation != "o" && operation != "dc" && operation != "lu" &&
        	operation != "cm" && operation != "la" && operation != "las" &&
        	operation != "lap" && operation != "qm" && operation != "qt" &&
        	operation != "dm" && operation != "da") {
        	cout << "can't find the operating command" << endl;
        	cout << "Agenda@" << m_userName << " : # ";
        	operation = getOperation();
        }
        executeOperation(operation);
    }

    /**
     * user create a meeting with someone else
     */
    void AgendaUI::createMeeting(void) {
        cout << endl;
        int num;
        std::vector<std::string> vec_participator;
        std::string participator, title, startDate, endDate;
        cout << "[create meeting] [the number of participators]\n";
        cout << "[create meeting] << ";
        cin >> num;
        if (num > 0) {
        for (int i = 1; i <= num; i++) {
            cout << "[create meeting] [please enter the participator " << i << " ] \n";
            cout << "[create meeting] ";
            cin >> participator;
            vec_participator.push_back(participator);
        }
        cout << "[create meeting] [title]"
            << "[start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n";
            std::cout << "[create meeting] ";
            cin >> title >> startDate >> endDate;
            if (m_agendaService.createMeeting(m_userName, title, startDate, endDate, vec_participator))
            cout << "[creating meeting] succeed!" << endl;
            else cout << "[creating meeting] error!" << endl;
        } else {
        cout << "[creating meeting] error!" << endl;
        }
        cout << endl;
        printCommand();
        cout << "Agenda@" << m_userName << " : # ";
        std::string operation = getOperation();
        while (operation != "o" && operation != "dc" && operation != "lu" &&
        	operation != "cm" && operation != "la" && operation != "las" &&
        	operation != "lap" && operation != "qm" && operation != "qt" &&
        	operation != "dm" && operation != "da") {
        	cout << "can't find the operating command" << endl;
        	cout << "Agenda@" << m_userName << " : # ";
        	operation = getOperation();
        }
        executeOperation(operation);
    }

    /**
     * list all meetings from storage
     */
    void AgendaUI::listAllMeetings(void) {
        cout << endl;
        cout << "[list all meetings]" << endl << endl;
        std::list<Meeting> meeting_list = m_agendaService.listAllMeetings(m_userName);
        printMeetings(meeting_list);
        cout << endl;
        printCommand();
        cout << "Agenda@" << m_userName << " : # ";
        std::string operation = getOperation();
        while (operation != "o" && operation != "dc" && operation != "lu" &&
        	operation != "cm" && operation != "la" && operation != "las" &&
        	operation != "lap" && operation != "qm" && operation != "qt" &&
        	operation != "dm" && operation != "da") {
        	cout << "can't find the operating command" << endl;
        	cout << "Agenda@" << m_userName << " : # ";
        	operation = getOperation();
        }
        executeOperation(operation);
    }

    /**
     * list all meetings that this user sponsored
     */
    void AgendaUI::listAllSponsorMeetings(void) {
        cout << endl;
        cout << "[list all sponsor meetings]" << endl << endl;
        std::list<Meeting> meeting_list = m_agendaService.listAllSponsorMeetings(m_userName);
        printMeetings(meeting_list);
        cout << endl;
        printCommand();
        cout << "Agenda@" << m_userName << " : # ";
        std::string operation = getOperation();
        while (operation != "o" && operation != "dc" && operation != "lu" &&
        	operation != "cm" && operation != "la" && operation != "las" &&
        	operation != "lap" && operation != "qm" && operation != "qt" &&
        	operation != "dm" && operation != "da") {
        	cout << "can't find the operating command" << endl;
        	cout << "Agenda@" << m_userName << " : # ";
        	operation = getOperation();
        }
        executeOperation(operation);
    }

    /**
     * list all meetings that this user take part in
     */
    void AgendaUI::listAllParticipateMeetings(void) {
        cout << endl;
        cout << "[list all participator meetings]" << endl << endl;
        std::list<Meeting> meeting_list = m_agendaService.listAllParticipateMeetings(m_userName);
        printMeetings(meeting_list);
        cout << endl;
        printCommand();
        cout << "Agenda@" << m_userName << " : # ";
        std::string operation = getOperation();
        while (operation != "o" && operation != "dc" && operation != "lu" &&
        	operation != "cm" && operation != "la" && operation != "las" &&
        	operation != "lap" && operation != "qm" && operation != "qt" &&
        	operation != "dm" && operation != "da") {
        	cout << "can't find the operating command" << endl;
        	cout << "Agenda@" << m_userName << " : # ";
        	operation = getOperation();
        }
        executeOperation(operation);
    }

    /**
     * search meetings by title from storage
     */
    void AgendaUI::queryMeetingByTitle(void) {
        cout << endl;
        cout << "[query meetings] [title]:" << endl << "[query meetings] ";
        std::string title;
        cin >> title;
        std::list<Meeting> meeting_list = m_agendaService.meetingQuery(m_userName, title);
        printMeetings(meeting_list);
        cout << endl;
        printCommand();
        cout << "Agenda@" << m_userName << " : # ";
        std::string operation = getOperation();
        while (operation != "o" && operation != "dc" && operation != "lu" &&
        	operation != "cm" && operation != "la" && operation != "las" &&
        	operation != "lap" && operation != "qm" && operation != "qt" &&
        	operation != "dm" && operation != "da") {
        	cout << "can't find the operating command" << endl;
        	cout << "Agenda@" << m_userName << " : # ";
        	operation = getOperation();
        }
        executeOperation(operation);
    }

    /**
     * search meetings by timeinterval from storage
     */
    void AgendaUI::queryMeetingByTimeInterval(void) {
        cout << endl;
        cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)] "
            << "[end time(yyyy-mm-dd/hh:mm)]" << endl << "[query meetings] ";
            std::string startDate, endDate;
            cin >> startDate >> endDate;
            std::list<Meeting> meeting_list = m_agendaService.meetingQuery(m_userName, startDate, endDate);
            printMeetings(meeting_list);
            cout << endl;
            printCommand();
            cout << "Agenda@" << m_userName << " : # ";
            std::string operation = getOperation();
            while (operation != "o" && operation != "dc" && operation != "lu" &&
            	operation != "cm" && operation != "la" && operation != "las" &&
            	operation != "lap" && operation != "qm" && operation != "qt" &&
            	operation != "dm" && operation != "da") {
            	cout << "can't find the operating command" << endl;
            	cout << "Agenda@" << m_userName << " : # ";
            	operation = getOperation();
            }
            executeOperation(operation);
    }

    /**
     * delete meetings by title from storage
     */
    void AgendaUI::deleteMeetingByTitle(void) {
        cout << endl;
        cout << "[delete meeting] [title]" << endl << "[delete meeting] ";
        std::string title;
        cin >> title;
        if (m_agendaService.deleteMeeting(m_userName, title)) {
            cout << endl << "[delete meeting by title] succeed!";
        } else {
            cout << endl << "[error] delete meeting fail!";
        }
        cout << endl;
        printCommand();
        cout << "Agenda@" << m_userName << " : # ";
        std::string operation = getOperation();
        while (operation != "o" && operation != "dc" && operation != "lu" &&
        	operation != "cm" && operation != "la" && operation != "las" &&
        	operation != "lap" && operation != "qm" && operation != "qt" &&
        	operation != "dm" && operation != "da") {
        	cout << "can't find the operating command" << endl;
        	cout << "Agenda@" << m_userName << " : # ";
        	operation = getOperation();
        }
        executeOperation(operation);
    }

    /**
     * delete all meetings that this user sponsored
     */
    void AgendaUI::deleteAllMeetings(void) {
        cout << endl;
        m_agendaService.deleteAllMeetings(m_userName);
        cout << "[delete all meetings] succeed!" << endl;
        cout << endl;
        printCommand();
        cout << "Agenda@" << m_userName << " : # ";
        std::string operation = getOperation();
        while (operation != "o" && operation != "dc" && operation != "lu" &&
        	operation != "cm" && operation != "la" && operation != "las" &&
        	operation != "lap" && operation != "qm" && operation != "qt" &&
        	operation != "dm" && operation != "da") {
        	cout << "can't find the operating command" << endl;
        	cout << "Agenda@" << m_userName << " : # ";
        	operation = getOperation();
        }
        executeOperation(operation);
    }

    /**
     * show the meetings in the screen
     */
    void AgendaUI::printMeetings(std::list<Meeting> t_meetings) {
        cout.setf(std::ios::left);
        cout << std::setw(10) << "title" << std::setw(10) <<
        "sponsor" << std::setw(18) << "start time" << std::setw(18)
        << "end time" << std::setw(18) << "participator" << endl;
  for (auto meeting : t_meetings) {
      cout.setf(std::ios::left);
      cout << std::setw(16) << meeting.getTitle()
              << std::setw(16) << meeting.getSponsor()
              << std::setw(16) << Date::dateToString(meeting.getStartDate())
              << std::setw(16) << Date::dateToString(meeting.getEndDate());
    std::vector<std::string> vec_participator = meeting.getParticipator();
    for (auto iterator = vec_participator.begin(); iterator != vec_participator.end(); iterator++) {
        if (iterator == (--vec_participator.end())) continue;
        cout << *iterator << ",";
    }
    cout << vec_participator.back() << endl;
}
}
    // dates
