#include "main.h"

/*
* ---- C4267 IGNORED ----
*
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
*/
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

	mysqlx::Session session(mysqlx::SessionOption::USER, username,
							mysqlx::SessionOption::PWD, password,
							mysqlx::SessionOption::HOST, localHost,
							mysqlx::SessionOption::PORT, 33060);
	
	SQL_login.close();

	std::string tableName = "books_info";
	std::string dbName = "books_db";
	std::string c1 = "name", c2 = "author", c3 = "date_published";

	/* C++ Connector Code */
	// * If database already exists, drop it
	if (session.getSchema(dbName).existsInDatabase()) { session.dropSchema(dbName); }
	// * Create Database
	mysqlx::Schema db = session.createSchema(dbName);

	// * Create Table (Cant find method to specify columns, using SQL code for this)
	// mysqlx::Table table(db, tableName);


	/**********************/

	/* ---- SQL Code ---- */
	// * Create Database
	// session.sql("create database if not exists " + dbName + ";").execute();

	// * specify database that will contain the table
	session.sql("use " + dbName + ";").execute();
 
	// * Create Table
	session.sql("create table if not exists " + tableName + "(" + c1 + " varchar(100), " + c2 + " varchar(100), " + c3 + " varchar(5));").execute();
	
	/*********************/

	// * Get table
	mysqlx::Table table = db.getTable(tableName);

	std::ifstream file;
	file.open("Data/book_data.txt");

	std::string name, author, published;
	mysqlx::TableInsert tableInsert(table);
	while (getline(file, line))
	{
		// Find substrings with seperator charactor ";"
		name = line.substr(0, line.find(";"));
		author = line.substr(line.find(";") + 1, find_nth(line, ";", 2) - (line.find(";") + 1));
		published = line.substr(find_nth(line, ";", 2) + 1, 4);

		/* C++ Connector Code */
		// * Insert into table
		tableInsert.values(name, author, published);

		/**********************/


		/* ---- SQL Code ---- */
		// std::string str = "insert into " + tableName + " values ('" + name + "', '" + author + "', " + published + ");";
		// session.sql(str).execute();

		/**********************/
	}
	
	// Execute the tableInsert
	tableInsert.execute();

	/* C++ Connector Code */
	// Show all entries through console
	mysqlx::RowResult rr = table.select(c1,c2,c3).execute();
	for (mysqlx::Row row : rr.fetchAll())
	{
		std::cout << row[0] << ", ";
		std::cout << row[1] << ", ";
		std::cout << row[2] << std::endl;
	}
	/**********************/

	file.close();

	return 0;
}


// Needed to find the nth occurance of a char
// Source: https://stackoverflow.com/questions/18972258/index-of-nth-occurrence-of-the-string
int find_nth(const std::string& str, const std::string& key, int nth)
{
	int pos = 0;
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
void output(const char* szFormat, ...)
{
	char szBuff[1024];
	va_list arg;
	va_start(arg, szFormat);
	_vsnprintf_s(szBuff, sizeof(szBuff), szFormat, arg);
	va_end(arg);

	OutputDebugString(szBuff);
	OutputDebugString("\n");
}