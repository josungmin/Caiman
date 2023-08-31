#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(Caiman, Log, All);

#define PrintLine() {CLog::Log(__FUNCTION__, __LINE__);}

class CAIMAN_API CLog
{
public:
	static void Log(const FString& InFuncName, int32 InLineNumber);
};
