// Copyright (c) 2015 Jussi Saarivirta 2016 conflict.industries MIT License (MIT)

#pragma once

#include "ModuleManager.h"

class FDatabaseSQLite : public IModuleInterface
{
public:

  /** IModuleInterface implementation */
  virtual void StartupModule() override;
  virtual void ShutdownModule() override;
};

DECLARE_LOG_CATEGORY_EXTERN(LogDatabase, All, All);