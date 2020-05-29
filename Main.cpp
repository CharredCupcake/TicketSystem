#include <iostream>
#include "TicketSystem.hpp"

int main()
{
	std::string fileName;
	TicketSystem sys;
	size_t option, dotPos;
	do
	{
		do
		{
			std::cout << "Choose an option." << std::endl;
			std::cout << "(1) Open." << std::endl;
			std::cout << "(2) Help." << std::endl;
			std::cout << "(3) Exit." << std::endl;
			std::cin >> option;

		} while (option < 1 || option > 3);
		switch (option)
		{
		case 1:
			sys.open(fileName);
			break;
		case 2:
			TicketSystem::help();
			continue;
		case 3:
			sys.exit(fileName, false);
			break;
		}
		do
		{
			std::cout << "Choose an option." << std::endl;
			std::cout << "(1) Close." << std::endl;
			std::cout << "(2) Exit." << std::endl;
			std::cout << "(3) Help." << std::endl;
			std::cout << "(4) Save." << std::endl;
			std::cout << "(5) Save as." << std::endl;
			std::cout << "(6) Add event." << std::endl;
			std::cout << "(7) Free seats." << std::endl;
			std::cout << "(8) Book." << std::endl;
			std::cout << "(9) Unbook." << std::endl;
			std::cout << "(10) Buy." << std::endl;
			std::cout << "(11) Bookings." << std::endl;
			std::cout << "(12) Check." << std::endl;
			std::cout << "(13) Report." << std::endl;
			std::cin >> option;
			if (option < 1 || option > 13)
			{
				continue;
			}
			switch (option)
			{
			case 1:
				sys.close(fileName);
				break;
			case 2:
				sys.exit(fileName, true);
				break;
			case 3:
				TicketSystem::help();
				continue;
			case 4:
				sys.save(fileName);
				break;
			case 5:
				sys.saveAs();
				break;
			case 6:
				sys.addEvent();
				break;
			case 7:
				sys.freeSeats();
				break;
			case 8:
				sys.book();
				break;
			case 9:
				sys.unbook();
				break;
			case 10:
				sys.buy();
				break;
			case 11:
				sys.bookings();
				break;
			case 12:
				sys.check();
				break;
			case 13:
				sys.report();
				break;
			}
		} while (option != 1);

	} while (true);
}