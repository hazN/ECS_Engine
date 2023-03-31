#pragma once

#include <SQLite/sqlite3.h>
namespace sas
{
	class SQLiteDBHelper
	{
	public:
		SQLiteDBHelper();
		~SQLiteDBHelper();

		void ConnectToDB(const char* dbName);

		void ExecuteQuery(const char* sql, int* res);
	private:
		sqlite3* m_DB;
		bool m_IsConnected;
	};
}