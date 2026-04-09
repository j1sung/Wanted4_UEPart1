// Fill out your copyright notice in the Description page of Project Settings.


#include "Teacher.h"

UTeacher::UTeacher()
{
	Name = TEXT("안지성");
	Year = 5;
	Id = 3;
}

void UTeacher::DoLesson()
{
	Super::DoLesson();

	UE_LOG(
		LogTemp,
		Log,
		TEXT("%d년차 선생님 %s님이 수업을 진행합니다."),
		Year,
		*Name
	);
}
