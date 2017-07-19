#include "DatabaseSQLite.h"
#include "SQLiteLibrary.h"
#include "Misc/Paths.h"
#define LOGSQLITE(verbosity, text) UE_LOG(LogDatabase, verbosity, TEXT("SQLite: %s"), text)

bool USQLiteLibrary::NewDatabase() {
	if (sqlite3_open(":memory:", &database) == SQLITE_OK)
	{
		return true;
	}
	return false;
}
bool USQLiteLibrary::LoadDatabase(FString &filename) {
	sqlite3_close(database);
	if (sqlite3_open(":memory:", &database) != SQLITE_OK)
	{
		return false;
	}
	int rc;
	sqlite3 *pFile;
	sqlite3_backup *pBackup;
	rc = sqlite3_open(TCHAR_TO_ANSI(*filename), &pFile);
	if (rc != SQLITE_OK)
	{
		return false;
	}
	pBackup = sqlite3_backup_init(database, "main", pFile, "main");

	if (pBackup)
	{
		sqlite3_backup_step(pBackup, -1);
		sqlite3_backup_finish(pBackup);
	}
	rc = sqlite3_errcode(database);
	sqlite3_close(pFile);
	if (rc != SQLITE_OK)
	{
		return false;
	}
	return true;
}
bool USQLiteLibrary::SaveDatabase(FString &filename) {
	int rc;
	sqlite3 *pFile;
	sqlite3_backup *pBackup;
	rc = sqlite3_open(TCHAR_TO_ANSI(*filename), &pFile);
	if (rc != SQLITE_OK)
	{
		return false;
	}
	pBackup = sqlite3_backup_init(pFile, "main", database, "main");

	if (pBackup)
	{
		sqlite3_backup_step(pBackup, -1);
		sqlite3_backup_finish(pBackup);
	}
	rc = sqlite3_errcode(pFile);
	sqlite3_close(pFile);
	if (rc != SQLITE_OK)
	{
		return false;
	}
	return true;
}
bool USQLiteLibrary::CloseDatabase() {
	sqlite3_close(database);
	return true;
}

SQLiteResult USQLiteLibrary::ExecuteQuery(FString Query) {
	SQLiteResult result;

	int32 sqlReturnCode = 0;
	sqlite3_stmt* preparedStatement;

	sqlReturnCode = sqlite3_prepare_v2(database, TCHAR_TO_UTF8(*Query), -1, &preparedStatement, NULL);

	if (sqlReturnCode != SQLITE_OK)
	{
		const char* errorMessage = sqlite3_errmsg(database);
		FString error = "SQL error: " + FString(UTF8_TO_TCHAR(errorMessage));
		LOGSQLITE(Error, *error);
		LOGSQLITE(Error, *FString::Printf(TEXT("The attempted query was: %s"), *Query));
		result.ErrorMessage = error;
		result.Success = false;
		sqlite3_finalize(preparedStatement);
		return result;
	}

	//////////////////////////////////////////////////////////////////////////
	// Get and assign the data
	//////////////////////////////////////////////////////////////////////////

	TArray<SQLiteRow> resultRows;

	for (sqlReturnCode = sqlite3_step(preparedStatement);
		sqlReturnCode != SQLITE_DONE && sqlReturnCode == SQLITE_ROW;
		sqlReturnCode = sqlite3_step(preparedStatement))
	{
		SQLiteRow row;

		LOGSQLITE(Verbose, TEXT("Query returned a result row."));
		int32 resultColumnCount = sqlite3_column_count(preparedStatement);
		for (int32 c = 0; c < resultColumnCount; c++)
		{
			int32 columnType = sqlite3_column_type(preparedStatement, c);
			const char* columnName = sqlite3_column_name(preparedStatement, c);
			FString columnNameStr = UTF8_TO_TCHAR(columnName);
			SQLiteField val;
			switch (columnType)
			{
			case SQLITE_INTEGER:
				val.Type = SQLiteResultValueTypes::Integer;
				val.IntValue = sqlite3_column_int64(preparedStatement, c);
				break;
			case SQLITE_TEXT:
				val.Type = SQLiteResultValueTypes::Text;
				val.StringValue = UTF8_TO_TCHAR(sqlite3_column_text(preparedStatement, c));
				break;
			case SQLITE_FLOAT:
				val.Type = SQLiteResultValueTypes::Float;
				val.RealValue = sqlite3_column_double(preparedStatement, c);
				break;
			case SQLITE_NULL:
				val.Type = SQLiteResultValueTypes::NullValue;
				break;
			default:
				val.Type = SQLiteResultValueTypes::UnsupportedValueType;
			}

			if (val.Type != SQLiteResultValueTypes::UnsupportedValueType)
			{
				row.Fields.Add(columnNameStr, val);
			}
		}

		resultRows.Add(row);
	}

	//////////////////////////////////////////////////////////////////////////
	// Release the statement and close the connection
	//////////////////////////////////////////////////////////////////////////

	sqlite3_finalize(preparedStatement);

	result.Rows = resultRows;
	result.Success = true;
	return result;
}
int32 USQLiteLibrary::ExecuteNoQuery(FString Query) {
	int32 sqlReturnCode = 0;
	sqlite3_stmt* preparedStatement;
	sqlReturnCode = sqlite3_prepare_v2(database, TCHAR_TO_UTF8(*Query), -1, &preparedStatement, NULL);
	if (sqlReturnCode != SQLITE_OK)
	{
		const char* errorMessage = sqlite3_errmsg(database);
		FString error = "SQL error: " + FString(UTF8_TO_TCHAR(errorMessage));
		LOGSQLITE(Error, *error);
		LOGSQLITE(Error, *FString::Printf(TEXT("The attempted query was: %s"), *Query));
		sqlite3_finalize(preparedStatement);
		return false;
	}
	//////////////////////////////////////////////////////////////////////////
	// Release the statement and close the connection
	//////////////////////////////////////////////////////////////////////////
	bool result = sqlite3_step(preparedStatement) == SQLITE_DONE;
	int32 affected = sqlite3_changes(database);
	sqlite3_finalize(preparedStatement);
	return result? affected : 0;
}