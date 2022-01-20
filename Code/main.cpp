#include "main.h"

void Output(const char*, ...);

int main(void)
{
	WebScraper webScraper;
	webScraper.Download();
	/*/
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
	string tableName = "info";
	string dbName = "books_db";

	mysqlx::Session session(mysqlx::SessionOption::USER, username,
							mysqlx::SessionOption::PWD, password,
							mysqlx::SessionOption::HOST, localHost,
							mysqlx::SessionOption::PORT, 33060);
	
	SQL_login.close();

	
	session.sql("create database if not exists " + dbName + ";").execute();
	session.sql("use " + dbName + ";").execute();
	session.sql("create table if not exists " + tableName + "(name varchar(100), author varchar(100), date_published varchar(4));").execute();
	session.sql("truncate table " + tableName + ";").execute();

	std::ifstream file;
	file.open("Data/book_data.txt");

	std::string name, author, published;

	getline(file, line);

	name = line.substr(0, line.find(";"));
	author = line.substr(line.find(";") + 1, line.find(";", 2));
	published = line.substr(line.find(";", 2) + 1, 4);

	Output(name.c_str(), author.c_str(), published.c_str());

	/*
	while (getline(file, line))
	{
		name = line.substr(0, line.find(";"));
		author = line.substr(line.find(";") + 1, line.find(";", 2));
		published = line.substr(line.find(";", 2) + 1, 4);

		std::cout << name + " " + author + " " + published + "\n";
		std::cin.get();

		session.sql("INSERT INTO " + tableName + "(" + name + ", " + author + ", " + published + ")").execute();
	}
	
	file.close();
	*/
	return 0;
}

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