#include "SQLiteDBHelper.h"
#include <iostream>

int ResultCallback(void*, int columns, char** text, char** names)
{
	printf("Result: \n");
	printf(" num columns: %d\n", columns);

	for (int i = 0; i < columns; i++)
	{
		printf("%s\n", text[i]);
	}
	for (int i = 0; i < columns; i++)
	{
		printf("%s\n", names[i]);
	}

	return 0;
}
SQLiteDBHelper::SQLiteDBHelper()
	: m_DB(nullptr)
	, m_IsConnected(false)
{
}

SQLiteDBHelper::~SQLiteDBHelper()
{
	if (m_DB)
	{
		std::cout << "Connection to Leaderboard Database closed." << std::endl;
		sqlite3_close(m_DB);
	}
}
void SQLiteDBHelper::ConnectToDB(const char* dbName)
{
	if (m_IsConnected)
	{
		std::cout << "Already connected to the " << dbName << " Database." << std::endl;
		return;
	}

	int result = sqlite3_open(dbName, &m_DB);
	if (result != SQLITE_OK)
	{
		std::cout << "Failed to open our SQLite DB " << dbName << " with error code : " << result << std::endl;
		return;
	}

	m_IsConnected = true;
}

void SQLiteDBHelper::ExecuteQuery(const char* sql, int* res)
{
	if (!m_IsConnected)
	{
		std::cout << "Query failed, not connected to a Database..." << std::endl;
		return;
	}

	sqlite3_stmt* stmt;
	int result = sqlite3_prepare_v2(m_DB, sql, strlen(sql), &stmt, nullptr);
	if (result != SQLITE_OK) {
		std::cout << "Query failed, error: " << result << std::endl;
	}
	// Get the result
	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
		*res = sqlite3_column_int(stmt, 0);
	}
	// Free the statement
	sqlite3_finalize(stmt);
}
void SQLiteDBHelper::ExecuteQuery(const char* sql, std::vector<int>* res)
{
	if (!m_IsConnected)
	{
		std::cout << "Query failed, not connected to a Database..." << std::endl;
		return;
	}

	sqlite3_stmt* stmt;
	int result = sqlite3_prepare_v2(m_DB, sql, strlen(sql), &stmt, nullptr);
	if (result != SQLITE_OK) {
		std::cout << "Query failed, error: " << result << std::endl;
	}

	// Execute the query and fetch the results
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		res->push_back(sqlite3_column_int(stmt, 0));
	}

	// Free the statement
	sqlite3_finalize(stmt);
}