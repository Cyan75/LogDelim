#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


int main(void)
{
	//std::cout << "Hi";
	std::string logFileName = "testServerLog.txt";
	std::ifstream logFile(logFileName);
	std::ofstream result;
	std::ofstream cmd;
	result.open("result.txt");
	cmd.open("cmds.csv");

	std::string line;
	const std::string receive = "RECE";
	const std::string send = "SEND";
	const std::string monitor = "MONITOR";
		
	if (logFile.is_open()&&cmd.is_open()) {
		while (std::getline(logFile, line)) {
			//--------------the ALGORITHM-------------------------
			 /* 
				wondering what comes after '] '
				something else than ''
				something else than a array starting with MONITOR 'M','O','N','I','T','O','R'
				they are all cmd -> break line

				0		  1			2		  3			4
			idx	0123456789012345678901234567890123456789012345
				09:34:22  [RECEIVE] MO55
				09:34:22  [SEND] 
				09:34:22  [SEND] MONITOR0120000000004112200400
				09:34:22  [RECEIVE] 
				0		  1			2
			idx	012345678901234567890123
				10:14:35  [SEND] MONITOR0120000000003112200300*/
			//--------------------------------------------------

			if (!line.empty()) {
				std::string tag = line.substr(11, 4);
				//is [RECEIVE] 
				if (!tag.compare(receive)) {
					//not [RECEIVE] - 
					if (line.at(20) != '') {
						result << "\n----------  ----------\n";
						cmd << line.substr(0, 8) << "," << line.substr(10, 9)<< "," << line.substr(20, 26) << "\n";
					}
				}
				//is [SEND]
				else if (!tag.compare(send)) {
					if (line.at(17) != '') {
						if (line.substr(17,7) != monitor) {
							result << "\n----------  ----------\n";
							cmd << line.substr(0, 8) << "," << line.substr(10, 6) << "," << line.substr(17, 29) << "\n";
						}
					}
				}
				else {
					std::cout << "neither " << send << " nor " << receive << "\n";
				}
			}

			result << line <<"\n";
		}
		logFile.close();
	}
	result.close();
	cmd.close();
	return 0;
}
	

