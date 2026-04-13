// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CourseInfo.generated.h"

// 델리게이트 타입 선언.
DECLARE_MULTICAST_DELEGATE_TwoParams(FCourseInfoOnChangedSignature, 
	const FString& /*SchoolName*/, const FString& /*NewContents*/);

/**
 * 
 */
UCLASS()
class UEPART1_API UCourseInfo : public UObject
{
	GENERATED_BODY()

public:
	UCourseInfo();

	// 델리게이트 선언.
	FCourseInfoOnChangedSignature OnChanged;

	// 학사 정보 변경 시 호출할 함수.
	void ChangeCourseInfo(
		const FString& InSchoolName,
		const FString& InNewContents
	);
	
private:
	//발행 할 내용.
	FString Contents;

};
