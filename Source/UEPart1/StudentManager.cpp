#include "StudentManager.h"
#include "Student.h"

void FStudentManager::AddReferencedObjects(FReferenceCollector& Collector)
{
	// 유효성 확인 후 지정.
	// IsValid()
	if (SafeStudent->IsValidLowLevel())
	{
		Collector.AddReferencedObject(SafeStudent);
	}
}