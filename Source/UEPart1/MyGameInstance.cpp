// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "StudentManager.h"

// 유효성 검증 및 로그 출력 함수.
void CheckUObjectIsValid(
	const UObject* InObject,
	const FString& InTag)
{
	// 유효성 검사
	if (InObject->IsValidLowLevel())
	{
		UE_LOG(
			LogTemp,
			Log,
			TEXT("[%s] 유효한 언리얼 오브젝트"),
			*InTag
		);
	}
	else
	{
		UE_LOG(
			LogTemp,
			Log,
			TEXT("[%s] 유효하지 않은 언리얼 오브젝트"),
			*InTag
		);
	}
}

// 유효성 검증 및 로그 출력 함수.
void CheckUObjectIsNull(
	const UObject* InObject,
	const FString& InTag)
{
	// Null 여부 확인.
	if (!InObject /*InObject == nullptr*/)
	{
		UE_LOG(
			LogTemp,
			Log,
			TEXT("[%s] 널 포인터 언리얼 오브젝트"),
			*InTag
		);
	}
	else
	{
		UE_LOG(
			LogTemp,
			Log,
			TEXT("[%s] 널 포인터가 아닌 언리얼 오브젝트"),
			*InTag
		);
	}
}

void UMyGameInstance::Init()
{
	Super::Init();

	// 객체 생성.

	NonPropStudent = NewObject<UStudent>();
	PropStudent = NewObject<UStudent>();

	NonPropStudents.Add(NewObject<UStudent>());
	PropStudents.Add(NewObject<UStudent>());

	StudentManager = new FStudentManager(NewObject<UStudent>());
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();

	// 유효성 검사 및 로그 출력.

	// 삭제할 객체에서 관리하는 UObject 가져오기.
	const UStudent* StudentInManager
		= StudentManager->GetStudent();

	// StudentManager 객체 생성.
	delete StudentManager;
	StudentManager = nullptr;

	CheckUObjectIsNull(StudentInManager, TEXT("StudentInManager"));
	CheckUObjectIsValid(StudentInManager, TEXT("StudentInManager"));
	
	CheckUObjectIsNull(NonPropStudent, TEXT("NonPropStudent"));
	CheckUObjectIsValid(NonPropStudent, TEXT("NonPropStudent"));

	CheckUObjectIsNull(PropStudent, TEXT("PropStudent"));
	CheckUObjectIsValid(PropStudent, TEXT("PropStudent"));

	CheckUObjectIsNull(NonPropStudents[0], TEXT("NonPropStudents"));
	CheckUObjectIsValid(NonPropStudents[0], TEXT("NonPropStudents"));

	CheckUObjectIsNull(PropStudents[0], TEXT("PropStudents"));
	CheckUObjectIsValid(PropStudents[0], TEXT("PropStudents"));
}