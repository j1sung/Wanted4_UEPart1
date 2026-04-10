// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Person.h"
#include "LessonInterface.h"
#include "Teacher.generated.h"

/**
 * 
 */
UCLASS()
class UEPART1_API UTeacher : public UPerson, public ILessonInterface
{
	GENERATED_BODY() // 이전 RTTI보다 더 많은 내용
	
public:
	UTeacher();

	virtual void DoLesson() override;
};
