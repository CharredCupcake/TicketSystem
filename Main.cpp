#include <iostream>
#include "TicketSystem.hpp"

int main()
{
	std::string fileName = "Test";
	TicketSystem sys;
	sys.open(fileName);
	//sys.freeSeats();
	//sys.book();
	//sys.unbook();
	//sys.buy();
	//sys.bookings();
	//sys.check();
	sys.report();

}