#include <stdio.h>
#include <tchar.h>
#include "SerialClass.h"
#include <string>
#include <iostream>
#include <string.h>
#include <fstream>
#include <algorithm>

int main() {
    Serial *SP = new Serial("\\\\.\\COM14");

    char incomingData[5] = "";
    int dataLength = 5;
    int readResult = 0;
    std::ofstream myfile;
    myfile.open("raw.txt");
    std::string ans = "";
    int i = 0;
    while (SP->IsConnected() && i < 1024) {
        readResult = SP->ReadData(incomingData, dataLength);
        // printf("Bytes read: (0 means no data available) %i\n",readResult);
        incomingData[readResult] = 0;
        printf("%s", incomingData);
        ans += incomingData;
        Sleep(50);
        i++;
    }
    ans.erase(std::remove(ans.begin(), ans.end(), '\n'), ans.end());
    myfile << ans;
    myfile << ans;
    myfile << ans;
    myfile << ans;


    myfile.close();
    return 0;
}
