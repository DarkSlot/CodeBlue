// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeBlue.h"
#include "NewGameDataCommand.h"
//#include "SQLiteDatabase.h"

NewGameDataCommand::NewGameDataCommand(TArray<FUserDataTable *> info)
{
	for (auto infoline: info)
	{
		userinfo.Push(*infoline);
	}
}

NewGameDataCommand::~NewGameDataCommand()
{
}

void NewGameDataCommand::Execute()
{
	CreateUserInfo();
}
void NewGameDataCommand::CreateUserInfo() {

	//FString createusertable_sql = TEXT("CREATE TABLE `User` ( `userid` INTEGER NOT NULL PRIMARY"
	//	" KEY AUTOINCREMENT UNIQUE, `username` TEXT NOT NULL, `description` TEXT,"
	//	" `usertype` INTEGER NOT NULL, `money` REAL NOT NULL )");
	//USQLiteDatabase::ExecuteNoQuery(TEXT("market"), createusertable_sql);

	////UDataTable* GameObjectLookupTable;
	////static ConstructorHelpers::FObjectFinder<UDataTable>
	////	GameObjectLookupDataTable_BP(TEXT("DataTable'/Game/Data/UserData.UserData'"));
	////GameObjectLookupTable = GameObjectLookupDataTable_BP.Object;
	////UDataTable* GameObjectLookupTable = LoadObject<UDataTable>(nullptr,
	////	TEXT("/Game/Data/UserData.UserData"));
	////static const FString ContextString(TEXT("GENERAL"));
	////// o-- Search using FindRow. It returns a handle to the row.
	////// Access the variables like GOLookupRow->Blueprint_Class, GOLookupRow->Usecode
	////TArray<FUserDataTable *> rows;
	////GameObjectLookupTable->GetAllRows(ContextString, rows);
	//for (auto &row: userinfo)
	//{
	//	FString adduser_sql = FString::Printf(TEXT("INSERT INTO `User`(`username`,"
	//		"`description`,`usertype`,`money`) VALUES ('%s','%s',%d,%d);"), *row.username,*row.description,
	//		row.usertype, row.money);
	//	USQLiteDatabase::ExecuteNoQuery(TEXT("market"), adduser_sql);
	//}
}
