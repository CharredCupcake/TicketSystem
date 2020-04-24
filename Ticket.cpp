#include "Ticket.hpp"

Ticket::Ticket() :
	m_code(),
	m_note()
{

}

Ticket::Ticket(std::string code, std::string note) :
	m_code(code),
	m_note(note)
{
}

void Ticket::setCode(std::string code)
{
	m_code = code;
}

std::string Ticket::getCode() const
{
	return m_code;
}

void Ticket::setNote(std::string note)
{
	m_note = note;
}

std::string Ticket::getNote()
{
	return m_note;
}
