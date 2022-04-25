#include <cstring>
#include <fstream>

using namespace std;

void clearScreen() {
	try
	{
		system("cls");
	}
	catch(const std::exception& e)
	{
		system("clear");
	}
	
}

class Vaccine {
	private:
		char name[30];
		char vaccine_name[30];
		char mobile[11];

	public:
		float rating;
		void getData();
		char* getMobile();
		char* getName();
		char* getVaccineName();
		void setMobile(char*);
		void setName(char*);
		void setVaccineName(char*);
		void setRating(float);
		friend bool isValidRating(float);
};

class database_access {
	private:
		int count;
		int total;
		Vaccine vaccines[1000];
		ifstream infile;
		ofstream outfile;
		void increment();
		inline bool isFileExists (const string&);
		bool createFile(const string&);

	public:
		database_access();
		~database_access();
		int get_total();
		bool addRecord();
		void displayRecords();
		bool searchRecord(char*, char);
};