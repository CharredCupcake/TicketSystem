#pragma once
#include <string>

class Ticket
{
private:

	std::string m_code;
	std::string m_note;

public:

	Ticket();
	Ticket(std::string code, std::string note);

	void setCode(std::string code);
	std::string getCode() const;
	void setNote(std::string note);
	std::string getNote();

};

