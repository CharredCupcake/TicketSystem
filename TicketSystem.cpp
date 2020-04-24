#define _CRT_SECURE_NO_WARNINGS
#include "TicketSystem.hpp"

Date TicketSystem::cinDate()
{
	std::string dateStr;
	std::string yearStr, monthStr, dayStr;
	do
	{
		std::cout << "Enter date in format Year.Month.Day " << std::endl;
		std::cin >> dateStr;
		while (!ValidateDateFormat(dateStr))
		{
			std::cout << "Invalid format. " << std::endl;
			std::cout << "Enter date in format Year.Month.Day " << std::endl;
			std::cin >> dateStr;
		}
		size_t firstDot = dateStr.find('.');
		size_t secondDot = dateStr.rfind('.');
		yearStr = dateStr.substr(0, firstDot);
		monthStr = dateStr.substr(firstDot + 1, secondDot - firstDot - 1);
		dayStr = dateStr.substr(secondDot + 1);

	} while (!ValidateDate(yearStr, monthStr, dayStr));
	size_t year, month, day;
	year = std::stoul(yearStr);
	month = std::stoul(monthStr);
	day = std::stoul(dayStr);
	return Date(year, month, day);
}

bool TicketSystem::ValidateDateFormat(const std::string& dateStr)
{
	size_t firstDot = dateStr.find('.');
	size_t secondDot = dateStr.rfind('.');
	if (firstDot == std::string::npos)
	{
		return false;
	}
	if (secondDot == firstDot + 1)
	{
		return false;
	}
	if (firstDot == 0)
	{
		return false;
	}
	if (secondDot == dateStr.length() - 1)
	{
		return false;
	}
	if (firstDot == secondDot)
	{
		return false;
	}
	if (dateStr.find('.', firstDot + 1) != secondDot)
	{
		return false;
	}
	return true;
}

bool TicketSystem::ValidateDate(const std::string& yearStr, const std::string& monthStr, const std::string& dayStr)
{
	if (yearStr.find_first_not_of("0123456789") != std::string::npos)
	{
		std::cout << "Invalid Year. " << std::endl;
		return false;
	}
	if (monthStr.find_first_not_of("0123456789") != std::string::npos)
	{
		std::cout << "Invalid Month. " << std::endl;
		return false;
	}
	if (dayStr.find_first_not_of("0123456789") != std::string::npos)
	{
		std::cout << "Invalid day. " << std::endl;
		return false;
	}
	size_t year = std::stoul(yearStr), month = std::stoul(monthStr), day = std::stoul(dayStr);
	if (month < 1 || month > 12)
	{
		std::cout << "Invalid Month. " << std::endl;
		return false;
	}
	if (Date(year, month, day).isLeapYear())
	{
		if (month == 2)
		{
			if (DAYS_IN_MONTH[1] + 1 < day)
			{
				std::cout << "Invalid Day. " << std::endl;
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			if (DAYS_IN_MONTH[month - 1] < day)
			{
				std::cout << "Invalid Day. " << std::endl;
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	else
	{
		if (DAYS_IN_MONTH[month - 1] < day)
		{
			std::cout << "Invalid Day. " << std::endl;
			return false;
		}
		else
		{
			return true;
		}
	}
	return true;
}

bool TicketSystem::isHallFree(const Date& date, size_t hallNumber)
{
	for (size_t i = 0; i < m_hallCount; i++)
	{
		if (m_halls[i].getNumber() == hallNumber)
		{
			size_t eventCount = m_halls[i].getEventCount();
			for (size_t j = 0; j < eventCount; j++)
			{
				if (m_halls[i].getEvent(j).getDate() == date)
				{
					std::cout << "Date unavailable." << std::endl;
					return false;
				}
			}
			return true;
		}
	}
	std::cout << "Hall not found." << std::endl;
	return false;
}

size_t TicketSystem::getHallPos(size_t hallNumber)
{
	for (size_t i = 0; i < hallNumber; i++)
	{
		if (m_halls[i].getNumber() == hallNumber)
		{
			return i;
		}
	}
	return 0xffffffff;
}

size_t TicketSystem::findHall(const Date& date, std::string name)
{
	for (size_t i = 0; i < m_hallCount; i++)
	{
		size_t eventCount = m_halls[i].getEventCount();
		for (size_t j = 0; j < eventCount; j++)
		{
			if (m_halls[i].getEvent(j).getName().compare(name) == 0 && m_halls[i].getEvent(j).getDate() == date)
			{
				return i;
			}
		}
	}
	return 0xffffffff;
}

size_t TicketSystem::countDigits(size_t number)
{
	size_t result = 0, tempNumber = number;
	do {
		result++;
		tempNumber /= 10;
	} while (tempNumber != 0);
	return result;
}

bool TicketSystem::checkCodeFormat(std::string& code)
{
	size_t RPos = code.find('R'), SPos = code.find('S'), HPos = code.find('H');
	if (RPos == std::string::npos || SPos == std::string::npos || HPos == std::string::npos)
	{
		return false;
	}
	if (RPos != 0)
	{
		return false;
	}
	if (RPos + 1 >= SPos || RPos + 1 >= HPos)
	{
		return false;
	}
	if (SPos + 1 >= HPos)
	{
		return false;
	}
	if (HPos == code.length() - 1)
	{
		return false;
	}
	std::string row = code.substr(1, SPos - 1);
	if (row.find_first_not_of("0123456789") != std::string::npos)
	{
		return false;
	}
	std::string seat = code.substr(SPos + 1, HPos - SPos - 1);
	if (seat.find_first_not_of("0123456789") != std::string::npos)
	{
		return false;
	}
	std::string hall = code.substr(HPos + 1);
	if (hall.find_first_not_of("0123456789") != std::string::npos)
	{
		return false;
	}
	return true;
}

bool TicketSystem::checkCodeData(std::string& code)
{
	size_t RPos = code.find('R'), SPos = code.find('S'), HPos = code.find('H');
	std::string row = code.substr(1, SPos - 1), seat = code.substr(SPos + 1, HPos - SPos - 1), hall = code.substr(HPos + 1);
	bool seenHall = false;
	for (size_t i = 0; i < m_hallCount; i++)
	{
		if (m_halls[i].getNumber() == std::stoul(hall))
		{
			seenHall = true;
			if (m_halls[i].getRowCount() < std::stoul(row))
			{
				return false;
			}
			if (m_halls[i].getSeatCount() < std::stoul(seat))
			{
				return false;
			}
			break;
		}
	}
	return seenHall;
}

TicketSystem::TicketSystem() :
	m_halls(nullptr),
	m_hallCount(0)
{
}

TicketSystem::~TicketSystem()
{
	delete[] m_halls;
}

void TicketSystem::open(std::string& fileName)
{
	std::cout << "Enter file name." << std::endl;
	std::cin >> fileName;
	std::cin.ignore();
	size_t dotPos = fileName.find('.');
	if (dotPos == std::string::npos)
	{
		fileName += ".txt";
	}
	else
	{
		if (fileName.find('txt', dotPos + 1) != dotPos + 1)
		{
			fileName += ".txt";
		}
	}
	std::string hallCountStr;
	std::ifstream inStream;
	inStream.open(fileName);
	char tempChar = '\0';
	while ((tempChar = inStream.get()) != '\n')
	{
		hallCountStr.push_back(tempChar);
	}
	m_hallCount = std::stoul(hallCountStr);
	m_halls = new Hall[m_hallCount];
	for (size_t i = 0; i < m_hallCount; i++)
	{
		std::string numberStr;
		while ((tempChar = inStream.get()) != '\n')
		{
			numberStr.push_back(tempChar);
		}
		m_halls[i].setNumber(std::stoul(numberStr));
		std::string rowCountStr;
		while ((tempChar = inStream.get()) != '\n')
		{
			rowCountStr.push_back(tempChar);
		}
		m_halls[i].setRowCount(std::stoul(rowCountStr));
		std::string seatCountStr;
		while ((tempChar = inStream.get()) != '\n')
		{
			seatCountStr.push_back(tempChar);
		}
		m_halls[i].setSeatCount(std::stoul(seatCountStr));
		std::string eventCountStr;
		while ((tempChar = inStream.get()) != '\n')
		{
			eventCountStr.push_back(tempChar);
		}
		size_t eventCount = std::stoul(eventCountStr);
		m_halls[i].initEvents(eventCount);
		for (size_t j = 0; j < eventCount; j++)
		{
			std::string dateStr;
			while ((tempChar = inStream.get()) != '\n')
			{
				dateStr.push_back(tempChar);
			}
			size_t firstDot = dateStr.find('.'), secondDot = dateStr.rfind('.');
			Date date(std::stoul(dateStr.substr(0, firstDot)), std::stoul(dateStr.substr(firstDot + 1, secondDot - firstDot - 1)), std::stoul(dateStr.substr(secondDot + 1)));
			m_halls[i].getEvent(j).setDate(date);
			std::string nameStr;
			while ((tempChar = inStream.get()) != '\n')
			{
				nameStr.push_back(tempChar);
			}
			m_halls[i].getEvent(j).setName(nameStr);
			std::string bookedCountStr;
			while ((tempChar = inStream.get()) != '\n')
			{
				bookedCountStr.push_back(tempChar);
			}
			size_t bookedCount = std::stoul(bookedCountStr);
			m_halls[i].getEvent(j).initBooked(bookedCount);
			for (size_t k = 0; k < bookedCount; k++)
			{
				std::string codeStr, noteStr;
				while ((tempChar = inStream.get()) != '\n')
				{
					codeStr.push_back(tempChar);
				}
				m_halls[i].getEvent(j).getBooked(k).setCode(codeStr);
				while ((tempChar = inStream.get()) != '\n')
				{
					noteStr.push_back(tempChar);
				}
				m_halls[i].getEvent(j).getBooked(k).setNote(noteStr);
			}
			std::string soldCountStr;
			while ((tempChar = inStream.get()) != '\n')
			{
				soldCountStr.push_back(tempChar);
			}
			size_t soldCount = std::stoul(soldCountStr);
			m_halls[i].getEvent(j).initSold(soldCount);
			for (size_t k = 0; k < soldCount; k++)
			{
				std::string codeStr;
				while ((tempChar = inStream.get()) != '\n')
				{
					codeStr.push_back(tempChar);
				}
				m_halls[i].getEvent(j).getSold(k).setCode(codeStr);
			}
		}
	}
}

void TicketSystem::addEvent()
{
	Date date(cinDate());

	std::cout << "Enter hall number." << std::endl;
	size_t hallNumber;
	std::cin >> hallNumber;
	std::cin.ignore();

	std::string name;
	std::cout << "Enter name." << std::endl;
	std::getline(std::cin, name);

	if (isHallFree(date, hallNumber))
	{
		size_t hallPos = getHallPos(hallNumber);
		m_halls[hallPos].pushEvent(Event(date, name));
	}
}

void TicketSystem::freeSeats()
{
	Date date(cinDate());
	std::cin.ignore();
	std::string name;
	std::cout << "Enter name." << std::endl;
	std::getline(std::cin, name);

	size_t hallPos = findHall(date, name);
	if (hallPos == 0xffffffff)
	{
		std::cout << "Event not found." << std::endl;
		return;
	}
	size_t eventPos = m_halls[hallPos].findEvent(date, name);
	size_t rowCount = m_halls[hallPos].getRowCount(), seatCount = m_halls[hallPos].getSeatCount();
	size_t bookedCount = m_halls[hallPos].getEvent(eventPos).getBookedCount(), soldCount = m_halls[hallPos].getEvent(eventPos).getSoldCount();
	if (bookedCount + soldCount > rowCount* seatCount)
	{
		std::cout << "No Free seats!";
		return;
	}
	if (bookedCount == 0 && soldCount == 0)
	{
		for (size_t i = 0; i < rowCount; i++)
		{
			std::cout << "\nRow " << i + 1 << std::endl;
			for (size_t j = 0; j < seatCount; j++)
			{
				std::cout << "Seat " << j + 1 << '\t';
			}

		}
	}
	else
	{
		size_t HPos;
		std::string hallnumberStr;
		if (bookedCount > 0)
		{
			HPos = m_halls[hallPos].getEvent(eventPos).getBooked(0).getCode().find('H');
			hallnumberStr = m_halls[hallPos].getEvent(eventPos).getBooked(0).getCode().substr(HPos + 1);
		}
		else
		{
			HPos = m_halls[hallPos].getEvent(eventPos).getSold(0).getCode().find('H');
			hallnumberStr = m_halls[hallPos].getEvent(eventPos).getSold(0).getCode().substr(HPos + 1);

		}

		std::string code;
		char* row = new char[countDigits(rowCount) + 1];
		char* seat = new char[countDigits(seatCount) + 1];
		bool isFree;
		for (size_t i = 0; i < rowCount; i++)
		{
			row = _ultoa(i + 1, row, 10);
			std::cout << "\nRow " << i + 1 << std::endl;
			for (size_t j = 0; j < seatCount; j++)
			{
				isFree = true;
				seat = _ultoa(j + 1, seat, 10);
				code = 'R' + std::string(row) + 'S' + std::string(seat) + 'H' + hallnumberStr;
				for (size_t k = 0; k < bookedCount; k++)
				{
					if (code.compare(m_halls[hallPos].getEvent(eventPos).getBooked(k).getCode()) == 0)
					{
						isFree = false;
						break;
					}
				}
				if (isFree == false) continue;
				for (size_t k = 0; k < soldCount; k++)
				{
					if (code.compare(m_halls[hallPos].getEvent(eventPos).getSold(k).getCode()) == 0)
					{
						isFree = false;
						break;
					}
				}
				if (isFree == true)
				{
					std::cout <<"Seat " << j + 1 <<'\t';
				}
			}
			std::cout << std::endl;
		}
		delete[] row;
		delete[] seat;
	}
}

void TicketSystem::book()
{
	Date date(cinDate());
	std::cin.ignore();
	std::string name;
	std::cout << "Enter name." << std::endl;
	std::getline(std::cin, name);

	size_t hallPos = findHall(date, name);
	if (hallPos == 0xffffffff)
	{
		std::cout << "Event not found."<< std::endl;
		return;
	}
	size_t eventPos = m_halls[hallPos].findEvent(date, name);
	size_t rowCount = m_halls[hallPos].getRowCount(), seatCount = m_halls[hallPos].getSeatCount();
	size_t bookedCount = m_halls[hallPos].getEvent(eventPos).getBookedCount(), soldCount = m_halls[hallPos].getEvent(eventPos).getSoldCount();

	if (bookedCount + soldCount > rowCount* seatCount)
	{
		std::cout << "No Free seats!" << std::endl;
		return;
	}

	std::string rowStr, seatStr;
	std::cout << "Enter row." << std::endl;
	std::getline(std::cin, rowStr);
	std::cout << "Enter seat." << std::endl;
	std::getline(std::cin, seatStr);

	if (std::stoul(rowStr) > rowCount)
	{
		std::cout << "Invalid row." << std::endl;
		return;
	}
	if (std::stoul(seatStr) > seatCount)
	{
		std::cout << "Invalid seat." << std::endl;
		return;
	}
	size_t hallNumber = m_halls[hallPos].getNumber();
	char* numberCStr = new char[countDigits(hallNumber) + 1];
	numberCStr = _ultoa(hallNumber, numberCStr, 10);
	std::string code = 'R' + rowStr + "S" + seatStr + 'H' + std::string(numberCStr);

	for (size_t i = 0; i < bookedCount; i++)
	{
		if (code.compare(m_halls[hallPos].getEvent(eventPos).getBooked(i).getCode()) == 0)
		{
			std::cout << "Seat already booked." << std::endl;
			return;
		}
	}
	for (size_t i = 0; i < soldCount; i++)
	{
		if (code.compare(m_halls[hallPos].getEvent(eventPos).getSold(i).getCode()) == 0)
		{
			std::cout << "Seat already sold." << std::endl;
			return;
		}
	}

	std::string note;
	std::cout << "Enter note." << std::endl;
	std::getline(std::cin, note);
	Ticket ticket(code, note);
	m_halls[hallPos].getEvent(eventPos).pushBooked(ticket);
}

void TicketSystem::unbook()
{
	Date date(cinDate());
	std::cin.ignore();
	std::string name;
	std::cout << "Enter name." << std::endl;
	std::getline(std::cin, name);

	size_t hallPos = findHall(date, name);
	if (hallPos == 0xffffffff)
	{
		std::cout << "Event not found." << std::endl;
		return;
	}
	size_t eventPos = m_halls[hallPos].findEvent(date, name);
	size_t rowCount = m_halls[hallPos].getRowCount(), seatCount = m_halls[hallPos].getSeatCount();
	size_t bookedCount = m_halls[hallPos].getEvent(eventPos).getBookedCount();

	if (bookedCount == 0)
	{
		std::cout << "No bookings for this event." << std::endl;
		return;
	}

	std::string rowStr, seatStr;
	std::cout << "Enter row." << std::endl;
	std::getline(std::cin, rowStr);
	std::cout << "Enter seat." << std::endl;
	std::getline(std::cin, seatStr);

	if (std::stoul(rowStr) > rowCount)
	{
		std::cout << "Invalid row." << std::endl;
		return;
	}
	if (std::stoul(seatStr) > seatCount)
	{
		std::cout << "Invalid seat." << std::endl;
		return;
	}
	size_t hallNumber = m_halls[hallPos].getNumber();
	char* numberCStr = new char[countDigits(hallNumber) + 1];
	numberCStr = _ultoa(hallNumber, numberCStr, 10);
	std::string code = 'R' + rowStr + "S" + seatStr + 'H' + std::string(numberCStr);
	delete[] numberCStr;
	for (size_t i = 0; i < bookedCount; i++)
	{
		if (code.compare(m_halls[hallPos].getEvent(eventPos).getBooked(i).getCode()) == 0)
		{
			m_halls[hallPos].getEvent(eventPos).removeBooked(i);
			return;
		}
	}
	std::cout << "Booking not found.";
}

void TicketSystem::buy()
{

	Date date(cinDate());
	std::cin.ignore();
	std::string name;
	std::cout << "Enter name." << std::endl;
	std::getline(std::cin, name);

	size_t hallPos = findHall(date, name);
	if (hallPos == 0xffffffff)
	{
		std::cout << "Event not found." << std::endl;
		return;
	}
	size_t eventPos = m_halls[hallPos].findEvent(date, name);
	size_t rowCount = m_halls[hallPos].getRowCount(), seatCount = m_halls[hallPos].getSeatCount();
	size_t soldCount = m_halls[hallPos].getEvent(eventPos).getSoldCount();

	std::string rowStr, seatStr;
	std::cout << "Enter row." << std::endl;
	std::getline(std::cin, rowStr);
	std::cout << "Enter seat." << std::endl;
	std::getline(std::cin, seatStr);

	if (std::stoul(rowStr) > rowCount)
	{
		std::cout << "Invalid row." << std::endl;
		return;
	}
	if (std::stoul(seatStr) > seatCount)
	{
		std::cout << "Invalid seat." << std::endl;
		return;
	}
	size_t hallNumber = m_halls[hallPos].getNumber();
	char* numberCStr = new char[countDigits(hallNumber) + 1];
	numberCStr = _ultoa(hallNumber, numberCStr, 10);
	std::string code = 'R' + rowStr + "S" + seatStr + 'H' + std::string(numberCStr);
	delete[] numberCStr;

	for (size_t i = 0; i < soldCount; i++)
	{
		if (code.compare(m_halls[hallPos].getEvent(eventPos).getSold(i).getCode()) == 0)
		{
			std::cout << "Seat already taken." << std::endl;
			return;
		}
	}
	Ticket ticket(code, "");
	m_halls[hallPos].getEvent(eventPos).pushSold(ticket);
	std::cout << "Ticket code: " << code << std::endl;
}

void TicketSystem::bookings()
{
	size_t option = 0;
	do
	{
		std::cout << "(1) Search with date." << std::endl;
		std::cout << "(2) Search with name." << std::endl;
		std::cout << "(3) Search with date and name." << std::endl;
		std::cin >> option;
	} while (option < 1 || option > 3);
	Date date;
	std::string name;

	if (option < 3)
	{
		if (option == 1)
		{
			date = cinDate();
			for (size_t i = 0; i < m_hallCount; i++)
			{
				size_t eventCount = m_halls[i].getEventCount();
				for (size_t j = 0; j < eventCount; j++)
				{
					if (m_halls[i].getEvent(j).getDate() == date)
					{
						size_t bookedCount = m_halls[i].getEvent(j).getBookedCount();
						if (bookedCount == 0)
						{
							std::cout << "No booked tickets for " << m_halls[i].getEvent(j).getName() << " on " << date;
							continue;
						}
						else
						{
							std::cout << "Booked tickets for " << m_halls[i].getEvent(j).getName() << " on " << date;
						}
						for (size_t k = 0; k < bookedCount; k++)
						{
							std::cout << m_halls[i].getEvent(j).getBooked(k).getCode() << std::endl << m_halls[i].getEvent(j).getBooked(k).getNote() << std::endl;
						}
					}
				}
			}
		}
		else
		{
			std::cin.ignore();
			std::cout << "Enter name." << std::endl;
			std::getline(std::cin, name);

			for (size_t i = 0; i < m_hallCount; i++)
			{
				size_t eventCount = m_halls[i].getEventCount();
				for (size_t j = 0; j < eventCount; j++)
				{
					if (name.compare(m_halls[i].getEvent(j).getName()) == 0)
					{
						size_t bookedCount = m_halls[i].getEvent(j).getBookedCount();
						if (bookedCount == 0)
						{
							std::cout << "No booked tickets for " << name << " on " << m_halls[i].getEvent(j).getDate();
							continue;
						}
						else
						{
							std::cout << "Booked tickets for " << name << " on " << m_halls[i].getEvent(j).getDate();
						}
						for (size_t k = 0; k < bookedCount; k++)
						{
							std::cout << m_halls[i].getEvent(j).getBooked(k).getCode() << std::endl << m_halls[i].getEvent(j).getBooked(k).getNote()  << std::endl;
						}
					}
				}
			}
		}
	}
	else
	{
		date = cinDate();
		std::cin.ignore();
		std::cout << "Enter name." << std::endl;
		std::getline(std::cin, name);
		size_t hallPos = findHall(date, name);
		if (hallPos == 0xffffffff)
		{
			std::cout << "Event not found." << std::endl;
		}
		size_t eventPos = m_halls[hallPos].findEvent(date, name);
		size_t bookedCount = m_halls[hallPos].getEvent(eventPos).getBookedCount();
		if (bookedCount == 0)
		{
			std::cout << "No booked tickets for " << name << " on " << date;
		}
		else
		{
			std::cout << "Booked tickets for " << name << " on " << date;
		}
		for (size_t i = 0; i < bookedCount; i++)
		{
			std::cout << m_halls[hallPos].getEvent(eventPos).getBooked(i).getCode() << std::endl << m_halls[hallPos].getEvent(eventPos).getBooked(i).getNote() << std::endl;
		}
	}
}

void TicketSystem::check()
{
	std::string code;
	std::cout << "Enter code to check." << std::endl;
	std::getline(std::cin, code);
	if (checkCodeFormat(code) == false)
	{
		std::cout << "Invalid code." << std::endl;
		return;
	}
	if (checkCodeData(code) == false)
	{
		std::cout << "Invalid code." << std::endl;
		return;
	}
	std::cout << "Valid code." << std::endl;
}

void TicketSystem::report()
{
	std::cout << "From when to start the search?" << std::endl;
	Date fromDate(cinDate());
	std::cout << "When to stop the search?" << std::endl;
	Date toDate(cinDate());

	size_t option = 0;
	do
	{
		std::cout << "Specify hall?" << std::endl;
		std::cout << "(1) Yes." << std::endl;
		std::cout << "(2) No." << std::endl;
		std::cin >> option;
	} while (option < 1 || option > 2);

	if (option == 1)
	{
		size_t hallNumber;
		std::cout << "Enter hall number." << std::endl;
		std::cin >> hallNumber;
		std::cin.ignore();
		bool seenHall = false;
		for (size_t i = 0; i < m_hallCount; i++)
		{
			if (m_halls[i].getNumber() == hallNumber)
			{
				seenHall = true;
				size_t eventCount = m_halls[i].getEventCount();
				if (eventCount == 0)
				{
					std::cout << "There are no events in hall: " << hallNumber << std::endl;
					return;
				}
				for (size_t j = 0; j < eventCount; j++)
				{
					if (m_halls[i].getEvent(j).getDate() >= fromDate && m_halls[i].getEvent(j).getDate() <= toDate)
					{
						std::cout << "There are " << m_halls[i].getEvent(j).getSoldCount() << " tickets sold for " << m_halls[i].getEvent(j).getName() << " on " << m_halls[i].getEvent(j).getDate();
					}
				}
				break;
			}
		}
		if (seenHall == false)
		{
			std::cout << "Hall " << hallNumber << " doean't exist." << std::endl;
		}
	}
	else
	{
		for (size_t i = 0; i < m_hallCount; i++)
		{
			size_t eventCount = m_halls[i].getEventCount();
			if (eventCount == 0)
			{
				std::cout << "There are no events in hall: " << m_halls[i].getNumber() << std::endl;
			}
			for (size_t j = 0; j < eventCount; j++)
			{
				if (m_halls[i].getEvent(j).getDate() >= fromDate && m_halls[i].getEvent(j).getDate() <= toDate)
				{
					std::cout << "There are " << m_halls[i].getEvent(j).getSoldCount() << " tickets sold for " << m_halls[i].getEvent(j).getName() << " on " << m_halls[i].getEvent(j).getDate();
				}
			}
		}
	}

}
