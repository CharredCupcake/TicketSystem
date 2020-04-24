#pragma once
#include "Event.hpp"

class Hall
{
private:

	Event* m_events;
	size_t m_eventCount;
	size_t m_number;
	size_t m_rowCount;
	size_t m_seatCount;

public:

	Hall();
	~Hall();

	void setNumber(size_t number);
	size_t getNumber() const;
	void setRowCount(size_t rowCount);
	size_t getRowCount() const;
	void setSeatCount(size_t seatCount);
	size_t getSeatCount() const;
	size_t getEventCount() const;
	void initEvents(size_t eventCount);
	Event& getEvent(size_t eventPos);
	void pushEvent(const Event& event);
	size_t findEvent(const Date& date, std::string name);

};

