#pragma warning(disable : 4996)
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
using namespace std;


void addToLog(string winner, string loser)
{
	time_t now = time(0);
	char* dt = ctime(&now);

	fstream outfile;
	outfile.open("log.txt", std::fstream::out | std::fstream::app);
	outfile << winner << " Vs " << loser << "\n";
	outfile << "Winner: " << winner << "\n";
	outfile << dt << "\n\n";
	outfile.close();

}
