#include <iostream>
#include <vector>
#include "SocialNetwork.h"

int main() {
    SocialNetwork sn;
    
    while (true) {
        char buff[1024];
        std::cin.getline(buff, 1024);
        
        if (strcmp(buff, ">signup") == 0) {
            sn.signup();
        } else if(strcmp(buff, ">login") == 0) {
            Status runningStatus = sn.login();

            if(runningStatus == Status::EXIT) {
                return 0;
            } else if(runningStatus == Status::LOGOUT) {
                continue;
            }
        }  else if(strcmp(buff, ">exit") == 0) {
            return 0;
        }
    }
}
