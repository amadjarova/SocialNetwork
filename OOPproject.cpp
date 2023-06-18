
#include <iostream>
#include <vector>
#include "SocialNetwork.h"
int main()
{
    SocialNetwork sc;
    while (true)
    {
        char buff[1024];
        std::cin.getline(buff, 1024);
        if (strcmp(buff, ">signup") == 0)
        {
            sc.signup();
        }
        else if (strcmp(buff, ">login")==0)
        {
            Status runningStatus = sc.login();

            if (runningStatus == Status::EXIT) {
                return 0;
            }
            else if (runningStatus == Status::LOGOUT) {
                continue;
            }
        }
        else if (strcmp(buff, ">exit") == 0)
        {
            return 0;
        }
    }
}
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
