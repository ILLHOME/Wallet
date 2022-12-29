#include "wallet.h"

Wallet::Wallet()
{
	std::ifstream read(filename);
	std::ostringstream file;
	std::regex reg(R"(\\+|-?\d+)");
	std::smatch match;
	
	file << read.rdbuf();

	this->m_file_data = file.str();
	std::string wallet_values = m_file_data.substr(0, m_file_data.find('\n'));
	int32_t initial_size = wallet_values.size();

	while (std::regex_search(wallet_values, match, reg))
	{
		if (initial_size == wallet_values.size())
			m_cash_value = std::stoi(match.str());
		else
			m_card_value = std::stoi(match.str());

		wallet_values = match.suffix();
	}
}

void Wallet::write()
{
	std::ofstream write(filename);
	write << m_file_data;
	write.close();
}

void Wallet::insert(const int32_t& value, const std::string& wallet_type, const std::string& comment)
{
	const time_t now = time(NULL);
	char now_str[26];
	ctime_s(now_str, 26, &now);
	now_str[26] = ' ';

	if (wallet_type == "cash")
		m_cash_value += value;
	else
		m_card_value += value;

	m_file_data.replace(0, m_file_data.find('\n'), "[" + std::to_string(m_cash_value) + " " + std::to_string(m_card_value) + "]\n");

	m_file_data += now_str + std::to_string(value) + " " + wallet_type + " " + comment + "\n\n";
}

std::string Wallet::get_log()
{
	return this->m_file_data.substr(m_file_data.find('\n'), m_file_data.find_last_of('\n'));
}

std::string Wallet::get_overall()
{
	return "CASH: | " + std::to_string(m_cash_value) + "\n--------------------\nCARD: | " + std::to_string(m_card_value) + "\n";
}

void Wallet::clear()
{
	std::ofstream write(filename);
	write.close();
}
