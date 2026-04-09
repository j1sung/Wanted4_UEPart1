// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

UCLASS()
class UEPART1_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();
public:
	// 게임 인스턴스를 초기화 할때 사용하는 함수.
	virtual void Init() override;

private:
	// 학교 이름 변수
	UPROPERTY()
	FString SchoolName;
};
