#include "main.h"

void Output(const char*, ...);
int find_nth(const std::string &, const std::string &, int);

int main(void)
{
	std::ifstream SQL_login;
	try
	{
		SQL_login.open("Data/pass.txt");

		if (!SQL_login.is_open())
		{
			throw std::invalid_argument("pass.txt was not opened.");
		}
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what() << "\n";
		std::cin.get();
	}

	std::string line;
	getline(SQL_login, line);

	int pos1 = line.find(";");

	const std::string localHost = "localhost";
	const std::string username = line.substr(0, pos1);
	const std::string password = line.substr(pos1 + 1);
	std::string tableName = "books_info";
	std::string dbName = "books_db";

	mysqlx::Session session(mysqlx::SessionOption::USER, username,
							mysqlx::SessionOption::PWD, password,
							mysqlx::SessionOption::HOST, localHost,
							mysqlx::SessionOption::PORT, 33060);
	
	SQL_login.close();

	// Create Database
	session.sql("create database if not exists " + dbName + ";").execute();
	session.sql("use " + dbName + ";").execute();

	// Create Table
	session.sql("create table if not exists " + tableName + "(name varchar(100), author varchar(100), date_published varchar(4));").execute();
	session.sql("truncate table " + tableName + ";").execute();

	std::ifstream file;
	file.open("Data/book_data.txt");

	std::string name, author, published;

	getline(file, line);

	name = line.substr(0, line.find(";"));
	author = line.substr(line.find(";") + 1, find_nth(line, ";", 2) - (line.find(";") + 1));
	published = line.substr(find_nth(line, ";", 2) + 1, 4);

	while (getline(file, line))
	{
		name = line.substr(0, line.find(";"));
		author = line.substr(line.find(";") + 1, find_nth(line, ";", 2) - (line.find(";") + 1));
		published = line.substr(find_nth(line, ";", 2) + 1, 4);

		std::string str = "insert into " + tableName + " values ('" + name + "', '" + author + "', " + published + ");";
		session.sql(str).execute();
	}

	file.close();

	return 0;
}


// Needed to find the nth occurance of a char
// Source: https://stackoverflow.com/questions/18972258/index-of-nth-occurrence-of-the-string
int find_nth(const std::string& str, const std::string& key, int nth)
{
	size_t pos = 0;
	int cnt = 0;

	while (cnt != nth)
	{
		pos += 1;
		pos = str.find(key, pos);
		if (pos == std::string::npos) { return 1; }
		cnt++;	
	}

	return pos;
}

// Outputs strings.c_str() into debug window
void Output(const char* szFormat, ...)
{
	char szBuff[1024];
	va_list arg;
	va_start(arg, szFormat);
	_vsnprintf_s(szBuff, sizeof(szBuff), szFormat, arg);
	va_end(arg);

	OutputDebugString(szBuff);
	OutputDebugString("\n");
}