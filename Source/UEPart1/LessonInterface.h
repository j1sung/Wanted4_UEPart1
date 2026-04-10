// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LessonInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULessonInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UEPART1_API ILessonInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 이게 정석 (순수 가상 함수 = 추상 함수)
	//virtual void DoLesson() = 0;

	// 이 방법도 가능
	virtual void DoLesson();

	/*
	이 방법도 가능
	virtual void DoLesson()
	{

	}

	*/
};
