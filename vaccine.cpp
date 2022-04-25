#include <iostream>
#include <cstring>
#include "vaccine.h"

using namespace std;


void Vaccine::getData() {
	clearScreen();
	int type;
	cout << endl << "\n\tCOVID-19 VACCINE PORTAL";
	fflush(stdin);
	cout << endl << "\tEnter the name : ";
	cin.getline(name, 29);

	cout << endl << "Enter the mobile : ";
	fflush(stdin);
	cin.getline(vaccine_name, 29);

	cout << endl << "\tVACCINE TYPE ";
	bool loop = true;
	while(loop) {
		cout << endl << "\n\t1.Covaxin\n\t2.Covi-Shield\n\t3.Sputnik-V\n\n\tEnter your choice > ";
		cin >> type;
		switch (type)
		{
		case 1:
			strcpy(vaccine_name, "Covaxin");
			loop = false;
			break;
		case 2:
			strcpy(vaccine_name, "Covi_Shield");
			loop = false;
			break;
		case 3:
			strcpy(vaccine_name, "Sputkik-V");
			loop = false;
			break;
		default:
			cout << "\n\n\tPlease Enter a valid choice!";
			break;
		}
	}
	cout << endl;
}


database_access::database_access() {
	if (isFileExists("vaccinated")) {
		infile.open("vaccinated", ios::in);
		infile.read((char *)&count, sizeof(count));
		infile.read((char *)&total, sizeof(total));
		infile.close();
	}
	else {
		createFile("vaccinated");
	}
	infile.open("Database", ios::in);
	for (int i = 0; i < count; i++) {
		infile.read((char *)&vaccines[i], sizeof(vaccines[i]));
	}
	infile.close();
	outfile.open("Database", ios::out | ios::app);
}

database_access::~database_access() {
	outfile.close();
}

bool database_access::createFile(const string& name) {
	outfile.close();
	outfile.open("vaccinated", ios::out | ios::trunc);
	count = 0;
	total = 10000;
	outfile.write((char *)&count, sizeof(count));
	outfile.write((char *)&total, sizeof(total));
	bool result = outfile.good();
	outfile.close();
	outfile.open("Database", ios::out | ios::app);
	return result;
}


// Set Methods
void Vaccine::setName(char *Name) { 
	strcpy(name, Name);
}

void Vaccine::setVaccineName(char *VaccineName) {
	strcpy(vaccine_name, VaccineName);
}

void Vaccine::setMobile(char *Mobile) {
	strcpy(mobile, Mobile);
}

inline bool database_access::isFileExists (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

void database_access::increment() {
	outfile.close();
	outfile.open("vaccinated", ios::trunc);
	count += 1;
	total -= 1;
	outfile.write((char *)&count, sizeof(count));
	outfile.write((char *)&total, sizeof(total));
	outfile.close();
	outfile.open("Database", ios::out | ios::app);
}


// Get Methods
int database_access::get_total()
{
	return total;
}

char *Vaccine::getName()
{
	return name;
}

char *Vaccine::getVaccineName()
{
	return vaccine_name;
}

char *Vaccine::getMobile()
{
	return mobile;
}

bool database_access::addRecord() {
	clearScreen();
	cout << endl << "\n\tCOVID-19 VACCINE PORTAL";

	char temp_name[30];
	char temp_mobile[11];
	int temp_type;
	cout << endl << "Enter the mobile : ";
	fflush(stdin);
	cin.getline(temp_mobile, 11);

	bool found = searchRecord(temp_mobile, 'n');

	char temp_vaccine[30];
	fflush(stdin);

	if (!found) {
		cout << endl << "Enter the Name : ";
		fflush(stdin);
		cin.getline(temp_name, 29);

		cout << endl << "\tVACCINE TYPE ";
		bool loop = true;
		
		while (loop)
		{
			cout << endl << "\n\t1.Covaxin\n\t2.Covi-Shield\n\t3.Sputnik-V\n\n\tEnter your choice > ";
			cin >> temp_type;
			switch (temp_type)
			{
			case 1:
				strcpy(temp_vaccine, "Covaxin");
				loop = false;
				break;
			case 2:
				strcpy(temp_vaccine, "Covi-Shield");
				loop = false;
				break;
			case 3:
				strcpy(temp_vaccine, "Sputnik-V");
				loop = false;
				break;
			default:
				cout << "\n\n\tPlease Enter a valid choice!";
				break;
			}
		}

		vaccines[count].setName(temp_name);
		vaccines[count].setVaccineName(temp_vaccine);
		vaccines[count].setMobile(temp_mobile);

		if (outfile.write((char *)&vaccines[count], sizeof(vaccines[count])))
			increment();
		else
			return false;
	}
	return found;
}

void database_access::displayRecords() {
	clearScreen();
	cout << endl << "\tCOVID-19 VACCINATION TRACKER";
	cout << "\n************************************************************";
	for (int i = 0; i < count ; i++) {
		cout << endl << endl << "Name\t\t> " << vaccines[i].getName();
		cout << endl << "Vaccine\t\t> " << vaccines[i].getVaccineName();
		cout << endl << "Mobile\t\t> " << vaccines[i].getMobile();
		cout << endl;
		cout << "************************************************************";
	}
}

bool database_access::searchRecord(char* Mobile, char type = 'o') {
	bool found = false;
	for (int i = 0; i < count; i++) {
		if(!strcmp(vaccines[i].getMobile(), Mobile)) {
			found = true;
			if (type == 'p') {
				clearScreen();
				cout << endl << "\n\tCOVID-19 VACCINE PORTAL";

				cout << "\n************************************************************-";
				cout << endl << "Name\t\t> " << vaccines[i].getName();
				cout << endl << "Vaccine\t\t> " << vaccines[i].getVaccineName();
				cout << endl << "Mobile\t\t> " << vaccines[i].getMobile();
				cout << endl;
				cout << "************************************************************-";
			}
			break;
		}
	}
	return found;
}