#pragma once

#include "serverSQLite/sqlite3.h"
#include <vector>

class SQLiteDBHelper
{
public:
	SQLiteDBHelper();
	~SQLiteDBHelper();

	void ConnectToDB(const char* dbName);

	void ExecuteQuery(const char* sql, int* res);
	void ExecuteQuery(const char* sql, std::vector<int>* res);
private:
	sqlite3* m_DB;
	bool m_IsConnected;
};