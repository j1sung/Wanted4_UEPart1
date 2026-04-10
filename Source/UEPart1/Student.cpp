// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"
#include "Card.h"

UStudent::UStudent()
{
	Name = TEXT("홍길동");
	Year = 3;
	Card->SetCardType(ECardType::Student);
}

void UStudent::DoLesson()
{
	ILessonInterface::DoLesson();

	UE_LOG(
		LogTemp,
		Log,
		TEXT("%s님이 수업을 듣습니다."),
		*Name
	);
}
