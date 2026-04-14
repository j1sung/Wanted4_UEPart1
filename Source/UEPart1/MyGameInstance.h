// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "StudentData.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UEPART1_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

private:
	// 구조체의 경우, 스택 메모리(항상은 아님)에서 관리.
	TArray<FStudentData> StudentsData;

	// UObject의 경우 힙에 배치 및 관리됨.
	// TArray에서 UObject 타입을 사용할 때는 UPROPERTY 필수.
	UPROPERTY()
	TArray<TObjectPtr<class UStudent>> Students;

	TMap<int32, FString> StudentsMap;
};
