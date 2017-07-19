// Copyright (c) 2016 conflict.industries MIT License (MIT)

#include "DatabaseSQLite.h"

DEFINE_LOG_CATEGORY(LogDatabase)

#define LOCTEXT_NAMESPACE "FDatabaseSQLite"

void FDatabaseSQLite::StartupModule() {}
void FDatabaseSQLite::ShutdownModule() {}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDatabaseSQLite, DatabaseSQLite)

