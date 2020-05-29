#include "Event.hpp"

Event::Event() : 
	m_date(),
	m_name(),
	m_booked(nullptr),
	m_bookedCount(0),
	m_sold(nullptr),
	m_soldCount(0)
{
}

Event::Event(const Date& date, std::string name) :
	m_date(date),
	m_name(name),
	m_booked(nullptr),
	m_bookedCount(0),
	m_sold(nullptr),
	m_soldCount(0)
{
}

Event::~Event()
{
	delete[] m_sold;
	delete[] m_booked;
}

void Event::setDate(const Date& date)
{
	m_date = date;
}

Date& Event::getDate()
{
	return m_date;
}

void Event::setName(std::string name)
{
	m_name = name;
}

std::string Event::getName() const
{
	return m_name;
}

void Event::initBooked(size_t bookedCount)
{
	m_bookedCount = bookedCount;
	m_booked = new Ticket[m_bookedCount];
}

void Event::initSold(size_t soldCount)
{
	m_soldCount = soldCount;
	m_sold = new Ticket[m_soldCount];
}

Ticket& Event::getBooked(size_t bookedPos)
{
	return m_booked[bookedPos];
}

Ticket& Event::getSold(size_t soldPos)
{
	return m_sold[soldPos];
}

size_t Event::getBookedCount() const
{
	return m_bookedCount;
}

size_t Event::getSoldCount() const
{
	return m_soldCount;
}

Event& Event::operator=(const Event& other)
{
	if (this != &other)
	{
		m_date = other.m_date;
		m_name = other.m_name;
		delete[] m_booked;
		m_bookedCount = other.m_bookedCount;
		m_booked = new Ticket[m_bookedCount];
		for (size_t i = 0; i < m_bookedCount; i++)
		{
			m_booked[i] = other.m_booked[i];
		}
		delete[] m_sold;
		m_soldCount = other.m_soldCount;
		m_sold = new Ticket[m_soldCount];
		for (size_t i = 0; i < m_soldCount; i++)
		{
			m_sold[i] = other.m_sold[i];
		}
	}
	return *this;
}

void Event::pushBooked(const Ticket& ticket)
{
	if (m_booked == nullptr)
	{
		m_bookedCount = 1;
		m_booked = new Ticket[m_bookedCount];
		m_booked[0] = ticket;
		return;
	}
	
	Ticket* newBooked = new Ticket[m_bookedCount + 1];
	for (size_t i = 0; i < m_bookedCount; i++)
	{
		newBooked[i] = m_booked[i];
	}
	newBooked[m_bookedCount] = ticket;
	m_bookedCount++;
	delete[] m_booked;
	m_booked = newBooked;
}

void Event::pushSold(const Ticket& ticket)
{
	if (m_sold == nullptr)
	{
		m_soldCount = 1;
		m_sold = new Ticket[m_soldCount];
		m_sold[0] = ticket;
		return;
	}
	
	Ticket* newSold = new Ticket[m_soldCount + 1];
	for (size_t i = 0; i < m_soldCount; i++)
	{
		newSold[i] = m_sold[i];
	}
	newSold[m_soldCount] = ticket;
	m_soldCount++;
	delete[] m_sold;
	m_sold = newSold;
}

void Event::removeBooked(size_t bookedPos)
{
	if (m_bookedCount == 1)
	{
		delete[] m_booked;
		m_bookedCount = 0;
		return;
	}

	Ticket* newBooked = new Ticket[m_bookedCount - 1];

	for (size_t i = 0; i < bookedPos; i++)
	{
		newBooked[i] = m_booked[i];
	}
	for (size_t i = bookedPos + 1; i < m_bookedCount; i++)
	{
		newBooked[i - 1] = m_booked[i];
	}
	m_bookedCount--;
	delete[] m_booked;
	m_booked = newBooked;
}

std::ostream& operator<<(std::ostream& out, const Event& event)
{
	out << event.m_date;
	out << event.m_name << std::endl;
	size_t bookedCount = event.m_bookedCount;
	out << bookedCount << std::endl;
	for (size_t i = 0; i < bookedCount; i++)
	{
		out << event.m_booked[i];
	}
	size_t soldCount = event.m_soldCount;
	out << soldCount << std::endl;
	for (size_t i = 0; i < soldCount; i++)
	{
		out << event.m_sold[i];
	}
	return out;
}
