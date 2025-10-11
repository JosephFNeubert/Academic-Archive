// The program made for the final exam of CS225 - Joseph Neubert

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class SpaceMission {
protected:
	string missionName;
	int missionNumber;
	string goal;
	int numberOfDays;

public:
	SpaceMission(string name, int number, int days, string objective) : missionName(name), missionNumber(number), goal(objective), numberOfDays(days) {}
	SpaceMission(string name, int number, int days) : missionName(name), missionNumber(number), numberOfDays(days) {
		goal = "Leave the orbit of Earth.";
	}
	string displayMission() const {
		string display = "";
		display.append("Mission Name: ");
		display.append(missionName);
		display.append("\nMission Goal: ");
		display.append(goal);
		display.append("\nMission Number: ");
		display.append(to_string(missionNumber));
		display.append("\nNumber of Days: ");
		display.append(to_string(numberOfDays));
		display.append("\n");
		return display;
	}
	friend ostream& operator<<(ostream& os, SpaceMission& sm);
};

ostream& operator<<(ostream& os, SpaceMission& sm) {
	os << "Mission Name: " << sm.missionName << "\nMission Goal: " << sm.goal << "\nMission Number: " << sm.missionNumber << "\nNumber of Days: " << sm.numberOfDays << endl;
	return os;
}


class MarsMission : public SpaceMission {
public:
	MarsMission(string name, int number, int days) : SpaceMission(name, number, days) {
		goal = "Travel to Mars";
	}
};


int main() {
	vector<SpaceMission> missionsList;
	cout << "Welcome to the space program!" << endl;
	int flag;
	do {
		cout << "Type '1' to add a mission, type '2' to drop a mission, type '3' to exit." << endl;
		cin >> flag;
		if (flag == 1) {
			string name;
			string goal;
			int days;
			int number;
			cout << "Enter Mission Name: ";
			cin >> name;
			cout << "Enter Mission Goal: ";
			cin >> goal;
			cout << "Enter Mission Number: ";
			cin >> number;
			if (!cin) {
				number = missionsList.size() + 1;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			cout << "Enter Number of Days: ";
			cin >> days;
			if (!cin || days < 1) {
				days = 1;
			}

			SpaceMission newSM(name, number, days, goal);
			missionsList.push_back(newSM);
		}

		else if (flag == 2) {
			if (missionsList.size() <= 0) {
				cout << "There are no missions scheduled." << endl;
			}
			else {
				cout << "Dropping Mission: " << endl;
				cout << missionsList.back();
				missionsList.pop_back();
			}
		}

		else if (flag == 3) {
			ofstream file("missionsJN.txt");
			string missionsListFile = "";
			cout << "****************************MISSIONS****************************" << endl;
			for (int i = 0; i < missionsList.size(); i++) {
				cout << missionsList.at(i);
				cout << "------------------------------------------------" << endl;
				missionsListFile += missionsList.at(i).displayMission();
				missionsListFile += "------------------------------------------------\n";
			}
			file << missionsListFile;
			file.close();
		}

		else {
			cout << "Not a valid option. Please try again." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	} while (flag != 3);

	return 0;
}