#include <iostream>
#include "vaccine.cpp"

using namespace std;

int main(void){
	bool iterate = true;
	int choice, val;
	bool isTrue;
	
	database_access covid_database;
	while (iterate) {
		clearScreen();
		cout << "\t\t*************************** COVID-19 [VACCINE TRACKER] ***************************\n";
		cout << "\n\n\t\t\t\t\t\t1.Add Record\n\t\t\t\t\t\t2.Display Records\n\t\t\t\t\t\t3.Search Record\n\t\t\t\t\t\t4.Vaccine Availability\n\t\t\t\t\t\t5.Exit\n\n\t\t\t\t\tEnter your choice > ";
		cin >> choice;
		
		switch (choice)
		{
			case 1:
				if (!covid_database.addRecord())
					cout << endl << endl << "Record added!";
				else
					cout << endl << endl << "The record already exists!";
				fflush(stdin);
				getchar();
				break;
			case 2:
				covid_database.displayRecords();
				fflush(stdin);
				getchar();
				break;
			case 3:
				{
					char mobile[11];
					cout << endl << endl << "Enter the Mobile number : ";
					fflush(stdin);
					cin.getline(mobile,11);
					clearScreen();
					if (!covid_database.searchRecord(mobile, 'p')) {
						cout << endl << endl << "\tRecord not found!";
					}
					fflush(stdin);
					getchar();
					break;
				}
			case 4:
				cout << endl << endl << endl << "\n\n\t\t\tAvailability : " << covid_database.get_total();
				fflush(stdin);
				getchar();
				break;
			case 5:
				clearScreen();
				iterate = false;
				cout << endl << endl << endl << endl << "\t\t\t     Wear a mask!\n\t\t\tStay Home, Stay Safe!\n\n\n\n";
				fflush(stdin);
				getchar();
				break;
			default:
				clearScreen();
				cout << endl << "Enter a valid choice...!";
				fflush(stdin);
				getchar();
				break;
		}
		clearScreen();
		cout << endl << endl << "Enter to continue > ";
		fflush(stdin);
		getchar();
	}
}