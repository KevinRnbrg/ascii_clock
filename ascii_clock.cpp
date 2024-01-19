// https://gist.github.com/yuanqing/ffa2244bd134f911d365
// https://github.com/servetgulnaroglu/cube.c/blob/master/cube.c

#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include <sstream>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

string getAsciiArtNum(char c, int num) {
string result;
	switch(c) {
			case '0':
		{
			string zeroRows[5] = {" 0000 ", "00  00", "00  00", "00  00", " 0000 "};
			result = zeroRows[num];
			break;
		}
			case '1':
		{
			string oneRows[5] = {"1111  ", "  11  ", "  11  ", "  11  ", "111111"};
			result = oneRows[num];
			break;
		}
		case '2':
		{	
			string rows[5] = {" 2222 ", "22  22", "   22 ", "  22  ", "222222"};
			result = rows[num];
			break;
		}
		case '3':
		{
			string rows[5] = {" 3333 ", "33  33", "   333", "33  33", " 3333 "};
			result = rows[num];
			break;
		}
		case '4':
		{
			string rows[5] = {"44  44", "44  44", "444444", "    44", "    44"};
			result = rows[num];
			break;
		}
		case '5':
		{
			string rows[5] = {"555555", "55    ", "55555 ", "    55", "55555 "};
			result = rows[num];
			break;
		}
		case '6':
		{
			string rows[5] = {" 6666 ", "66    ", "66666 ", "66  66", " 6666 "};
			result = rows[num];
			break;
		}
		case '7':
		{
			string rows[5] = {"777777", "   77 ", "  77  ", " 77   ", "77    "};
			result = rows[num];
			break;
		}
		case '8':
		{
			string rows[5] = {" 8888 ", "88  88", " 8888 ", "88  88", " 8888 "};
			result = rows[num];
			break;
		}
		case '9':
		{
			string rows[5] = {" 9999 ", "99  99", " 99999", "    99", " 9999 "};
			result = rows[num];
			break;
		}
		case ':':
		{
			string rows[5] = {"      ", "  OO  ", "      ", "  OO  ", "      "};
			result = rows[num];
			break;
		}
		default:
		{
			result = "X";
			break;
		}
	}
	return result;
}

string getAsciiString(string input) {
	string combinedString;
	for (int i = 0; i < 5; i++) {
		for (char& c : input) {
			combinedString += getAsciiArtNum(c, i) + " ";
		}
		cout << combinedString << endl;
		combinedString = "";
	}

	return combinedString;
	
}

class Strategy {
	public:
		virtual void display(string time) = 0;
};

class clockStrategy : public Strategy {
	public:
		void display(string input) {
			time_t current_time;
			int i = 0;
			while (i < 5) {
				cout << "\x1b[2J";
				current_time = time(nullptr);
				string timeString = ctime(&current_time);
				string clock = timeString.substr(11, 8);

				cout << getAsciiString(clock) << endl;
				cout << clock << endl;

				this_thread::sleep_for(chrono::seconds(1));
				i++;
			}
			return;
		}
};

class timerSecondsStrategy : public Strategy {
	public:
		void display(string time) {
			int secondsLeft = stoi(time);
			while (secondsLeft > 0) {
					cout << "\x1b[2J";
					cout << "seconds timer" << endl;

					cout << getAsciiString(to_string(secondsLeft)) << endl;
					cout << secondsLeft << endl;

					secondsLeft--;
					this_thread::sleep_for(chrono::seconds(1));
			}
			return;
		}
};

class timerMinutesStrategy : public Strategy {
	public:
		void display(string time) {
			int minutesLeft;
			int secondsLeft;
			string timeString;
			if (time.length() == 5) {
				minutesLeft = stoi(time.substr(0, 2));
				secondsLeft = stoi(time.substr(3, 2));
			} else {
				minutesLeft = stoi(time.substr(0, 1));
				secondsLeft = stoi(time.substr(2, 2));
			}
			while (1) {
					cout << "\x1b[2J";
					cout << "minutes timer" << endl;
					timeString = to_string(minutesLeft) + ":" + to_string(secondsLeft);

					cout << getAsciiString(timeString) << endl;
					cout << timeString << endl;

					secondsLeft--;
					if (secondsLeft == -1) {
						if (minutesLeft == 0) {
							break;
						}
						minutesLeft--;
						secondsLeft = 59;
					}
					this_thread::sleep_for(chrono::seconds(1));
			}
			return;
		}
};

class timerHoursStrategy : public Strategy {
	public:
		void display(string time) {
			int minutesLeft;
			int secondsLeft;
			int hoursLeft;
			string timeString;
			if (time.length() == 8) {
				hoursLeft = stoi(time.substr(0, 2));
				minutesLeft = stoi(time.substr(3, 2));
				secondsLeft = stoi(time.substr(6, 2));
			} else {
				hoursLeft = stoi(time.substr(0, 1));
				minutesLeft = stoi(time.substr(3, 2));
				secondsLeft = stoi(time.substr(6, 2));
			}
			while (1) {
					cout << "\x1b[2J";
					cout << "hours timer" << endl;
					timeString = to_string(hoursLeft) + ":" + to_string(minutesLeft) + ":" + to_string(secondsLeft);

					cout << getAsciiString(timeString) << endl;
					cout << timeString << endl;

					secondsLeft--;
					if (secondsLeft == -1) {
						if (minutesLeft == 0) {
							if (hoursLeft == 0) {
								break;
							}
							hoursLeft--;
							minutesLeft = 60;
						}
						minutesLeft--;
						secondsLeft = 59;
					}
					this_thread::sleep_for(chrono::seconds(1));
			}
			return;
		}
};

class stopwatchStrategy : public Strategy{
	public:
		int stopwatchTime;
		string timeString;
		void display(string time) {
			stopwatchTime = 0;
			while (1) {
				cout << "\x1b[2J";
				timeString = to_string(stopwatchTime);

				cout << getAsciiString(timeString) << endl;
				cout << stopwatchTime << endl;

				stopwatchTime++;

				// add a break function somehow...
				
				this_thread::sleep_for(chrono::seconds(1));
			}
		}
};

class Context {
	private:
		Strategy* strategy;

	public:
		void setStrategy(Strategy* strategy) {
			this->strategy = strategy;
		}

		void displayStrategy(string time) {
			return strategy->display(time);
		}
};

int main() {
		Context context;
		timerSecondsStrategy secondsStrategy;
		timerMinutesStrategy minutesStrategy;
		timerHoursStrategy hoursStrategy;
		clockStrategy clockStrategy;
		stopwatchStrategy stopwatchStrategy;

        time_t current_time;
		int selection;
		int i;
		string timerTime;
		string clockTime = "";
		int stopwatchTime;
		string text;

		while (1) {
			/* cout << "\x1b[2J";
			ifstream dataFileR("data.txt");
			text = "";
			while (getline(dataFileR, text)) {
				cout << text << endl;
			}
			dataFileR.close(); */
			cout << "" << endl;
			cout << "1: clock" << endl;
			cout << "2: timer" << endl;
			cout << "3: stopwatch" << endl;
			cout << "4: exit" << endl;

			cout << "Select: " << endl;
			cin >> selection;
	
			if (selection == 1) { //clock
				
				fstream file;
				file.open("data.txt");
				string lineText;
				getline(file, lineText);
				file.close();
				int step = lineText.find("a");

				file.open("data.txt");
				file.ignore(step+1);
				file << 1; // make dynamic
				file.close();


				context.setStrategy(&clockStrategy);
				context.displayStrategy(clockTime);

			} else if (selection == 2) { // timer
				ofstream dataFileW("data.txt");
				dataFileW << "timerstrategy + 1";
				dataFileW.close();

				timerTime = "";
				cout << "Time: " << endl;
				cin >> timerTime;
				string result;

				if (timerTime.length() < 3) {
					context.setStrategy(&secondsStrategy);
				}
				if (timerTime.length() > 3 && timerTime.length() <= 5) {
					context.setStrategy(&minutesStrategy);
				}
				if (timerTime.length() > 5 && timerTime.length() <= 8) {
					context.setStrategy(&hoursStrategy);
				}
				context.displayStrategy(timerTime);

			} else if (selection == 3) { // stopwatch
				context.setStrategy(&stopwatchStrategy);
				context.displayStrategy(clockTime);
			} else {
				//dataFileR.close();	
				break;
			}
		}
		/* dataFileW.close(); */
        return 0;
}

