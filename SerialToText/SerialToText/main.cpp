
//This code snippet will help you to read data from arduino

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SerialPort.h"
#include <fstream>  

using std::cout;
using std::endl;

/*Portname must contain these backslashes, and remember to
replace the following com port*/
char* port_name = (char*) "\\\\.\\COM6";

//String for incoming data
char incomingData[MAX_DATA_LENGTH];

int main()
{
	std::ofstream outfile("data.txt");
	SerialPort arduino(port_name);
	if (arduino.isConnected()) cout << "Connection Established" << endl;
	else cout << "ERROR, check port name";
	int i = 0;
	while (arduino.isConnected() && i < 4096) {
		//Check if data has been read or not
		int read_result = arduino.readSerialPort(incomingData, MAX_DATA_LENGTH);
		//prints out datax
		cout << incomingData;
		outfile << read_result << std::endl;
		i++;
		//wait a bit
		Sleep(100);
	}
	outfile.close();
	puts("done");
}
