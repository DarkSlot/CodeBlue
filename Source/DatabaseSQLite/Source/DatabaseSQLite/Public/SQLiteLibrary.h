#pragma once
#include "sqlite3.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SQLiteLibrary.generated.h"

enum class SQLiteResultValueTypes : uint8
{
	Integer,
	Float,
	Text,
	NullValue,
	UnsupportedValueType
};

// Result field, used as an intermediary when collecting results from
// an SQLITE3 query.
struct SQLiteField
{
	FString StringValue;
	float RealValue;
	int32 IntValue;

	SQLiteResultValueTypes Type;

	FString ToString()
	{
		if (Type == SQLiteResultValueTypes::Text)
			return StringValue;
		else if (Type == SQLiteResultValueTypes::Integer)
			return FString::Printf(TEXT("%i"), IntValue);
		else if (Type == SQLiteResultValueTypes::Float)
			return FString::Printf(TEXT("%f"), RealValue);

		return StringValue;
	}
};

// Represents a single row in the result.
struct SQLiteRow
{
	TMap<FString, SQLiteField> Fields;
};

// The internal result object.
struct SQLiteResult
{
	bool Success;
	FString ErrorMessage;
	TArray<SQLiteRow> Rows;
};

/**
* SQLite main database class.
*/
UCLASS()
class DATABASESQLITE_API USQLiteLibrary : public UObject
{
	GENERATED_BODY()

public:
	/** Add new database */
	UFUNCTION(BlueprintCallable, Category = "SQLite")
		bool NewDatabase();

	/** Add new database */
	UFUNCTION(BlueprintCallable, Category = "SQLite")
		bool LoadDatabase(FString &filename);

	UFUNCTION(BlueprintCallable, Category = "SQLite")
		bool SaveDatabase(FString &filename);

	UFUNCTION(BlueprintCallable, Category = "SQLite")
		bool CloseDatabase();

	SQLiteResult ExecuteQuery(FString Query);
	int32 ExecuteNoQuery(FString Query);

protected:
	sqlite3 *database;
};
