#pragma once

#include "CoreMinimal.h"

struct FStudentData
{
	FStudentData() {}
	FStudentData(int32 InOrder, const FString& InName)
		: Order(InOrder), Name(InName)
	{
	}

	friend FArchive& operator<<(FArchive& Ar, FStudentData& InStudentData)
	{
		Ar << InStudentData.Order;
		Ar << InStudentData.Name;

		return Ar;
	}

	int32 Order = -1;
	FString Name = TEXT("홍길동");
};