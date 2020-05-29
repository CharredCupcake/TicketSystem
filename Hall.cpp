#include <cmath>
#include "Hall.hpp"

Hall::Hall() :
	m_events(nullptr),
	m_eventCount(0),
	m_number(0),
	m_rowCount(0),
	m_seatCount(0)
{
}

Hall::~Hall()
{
	delete[] m_events;
}

void Hall::setNumber(size_t number)
{
	m_number = number;
}

size_t Hall::getNumber() const
{
	return m_number;
}

void Hall::setRowCount(size_t rowCount)
{
	m_rowCount = rowCount;
}

size_t Hall::getRowCount() const
{
	return m_rowCount;
}

void Hall::setSeatCount(size_t seatCount)
{
	m_seatCount = seatCount;
}

size_t Hall::getSeatCount() const
{
	return m_seatCount;
}

size_t Hall::getEventCount() const
{
	return m_eventCount;
}

void Hall::initEvents(size_t eventCount)
{
	m_eventCount = eventCount;
	m_events = new Event[m_eventCount];
}

Event& Hall::getEvent(size_t eventPos)
{
	return m_events[eventPos];
}

void Hall::pushEvent(const Event& event)
{
	if (m_events == nullptr)
	{
		m_eventCount = 1;
		m_events = new Event[1];
		m_events[0] = event;
	}
	else
	{
		Event* newEvents = new Event[m_eventCount + 1];
		for (size_t i = 0; i < m_eventCount; i++)
		{
			newEvents[i] = m_events[i];
		}
		newEvents[m_eventCount] = event;
		m_eventCount++;
		delete[] m_events;
		m_events = newEvents;
	}
}

size_t Hall::findEvent(const Date& date, std::string name)
{
		for (size_t i = 0; i < m_eventCount; i++)
		{
			if (getEvent(i).getName().compare(name) == 0 && getEvent(i).getDate() == date)
			{
				return i;
			}
		}
	return 0xffffffff;
}

std::ostream& operator<<(std::ostream& out, const Hall& hall)
{
	out << hall.m_number << '\n';
	out << hall.m_rowCount << '\n';
	out << hall.m_seatCount << '\n';

	size_t eventcount = hall.m_eventCount;
	out << eventcount << '\n';

	for (size_t i = 0; i < eventcount; i++)
	{
		out << hall.m_events[i];
	}
	return out;
}
