// Fill out your copyright notice in the Description page of Project Settings.


#include "CourseInfo.h"

UCourseInfo::UCourseInfo()
{
	Contents = TEXT("기본 학사 정보");
}

void UCourseInfo::ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents)
{
	// 업데이트된 정보 저장.
	Contents = InNewContents;

	// 로그 출력.
	UE_LOG(LogTemp, Log, TEXT("[CourseInfo] 학사 정보가 변경되어 알림을 발송 합니다."));

	// 델리게이트 호출
	OnChanged.Broadcast(InSchoolName, InNewContents);
}
