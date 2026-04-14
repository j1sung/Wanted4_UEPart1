// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

// 전방 선언.
class UStudent;
class FStudentManager;

/**
 * 
 */
UCLASS()
class UEPART1_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	virtual void Init() override;

	// 종료할 때 정리 작업용으로 사용.
	virtual void Shutdown() override;

private:
	TObjectPtr<UStudent> NonPropStudent;

	UPROPERTY()
	TObjectPtr<UStudent> PropStudent;

	TArray<TObjectPtr<UStudent>> NonPropStudents;

	UPROPERTY()
	TArray<TObjectPtr<UStudent>> PropStudents;

	FStudentManager* StudentManager = nullptr;

};
