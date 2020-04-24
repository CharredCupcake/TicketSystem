#pragma once
#include "Date.hpp"
#include "Ticket.hpp"

class Event
{
private:

	Date m_date;
	std::string m_name;
	Ticket* m_booked;
	size_t m_bookedCount;
	Ticket* m_sold;
	size_t m_soldCount;

public:

	Event();
	Event(const Date& date, std::string name);
	~Event();

	void setDate(const Date& date);
	Date& getDate();
	void setName(std::string name);
	std::string getName() const;
	void initBooked(size_t bookedCount);
	void initSold(size_t soldCount);
	Ticket& getBooked(size_t bookedPos);
	Ticket& getSold(size_t soldPos);
	size_t getBookedCount() const;
	size_t getSoldCount() const;
	Event& operator=(const Event& other);
	void pushBooked(const Ticket& ticket);
	void pushSold(const Ticket& ticket);
	void removeBooked(size_t bookedPos);

};

