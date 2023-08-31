#include "Utilities/CLog.h"
#include "Engine.h"

DEFINE_LOG_CATEGORY(Caiman);

void CLog::Log(const FString& InFuncName, int32 InLineNumber)
{
	FString str;
	str.Append(InFuncName);
	str.Append(", ");
	str.Append(FString::FromInt(InLineNumber));

	UE_LOG(Caiman, Display, TEXT("%s"), *str);
}
