#pragma once
#include <fstream>
#include "Hall.hpp"

class TicketSystem
{
private:

	Hall* m_halls;
	size_t m_hallCount;

	bool isHallFree(const Date& date, size_t hallNumber);
	size_t getHallPos(size_t hallNumber);
	size_t findHall(const Date& date, std::string name);
	size_t countDigits(size_t number);
	bool checkCodeFormat(std::string& code);
	bool checkCodeData(std::string& code);
	void getLine(std::string& str, std::ifstream& in);


public:

	TicketSystem();
	~TicketSystem();

	void open(std::string& fileName);
	void save(std::string& fileName);
	void close(std::string& fileName);
	static void help();
	void exit(std::string& fileName, bool fileIsOpen);
	void saveAs();

	void addEvent();
	void freeSeats();
	void book();
	void unbook();
	void buy();
	void bookings();
	void check();
	void report();
};

