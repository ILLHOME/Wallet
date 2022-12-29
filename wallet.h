#ifndef WALLET
#define WALLET
#include <fstream>
#include <sstream>
#include <regex>
#include <string_view>
#include <ctime>

#define filename "D:\\wallet.lock"

class Wallet
{
public:
	Wallet();
	void write();
	void insert(const int32_t& value, const std::string& wallet_type, const std::string& comment);
	std::string get_log();
	std::string get_overall();
	void clear();
private:
	std::string m_file_data;
	int32_t m_cash_value = 0, m_card_value = 0;
};
#endif