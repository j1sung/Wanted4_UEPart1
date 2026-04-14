#pragma once

#include "CoreMinimal.h"

class UStudent;
class UEPART1_API FStudentManager : public FGCObject
{
public:
	FStudentManager(UStudent* InStudent)
		:SafeStudent(InStudent)
	{

	}

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	virtual FString GetReferencerName() const override
	{
		return TEXT("FStudentManager");
	}

	// Getter.
	const UStudent* GetStudent() const { return SafeStudent; }

private:
	UStudent* SafeStudent = nullptr;
};