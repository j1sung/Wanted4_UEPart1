// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UEPART1_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();

protected:
	virtual void Init() override;

	// 패키지 저장 함수.
	void SaveStudentPackage() const;

	// 패키지 로드 함수.
	void LoadStudentPackage() const;

	// 경로 기반 언리얼 오브젝트를 로드하는 함수.
	void LoadStudentObject() const;
	
private:

	// 패키지 이름.
	static const FString PackageName;

	// 에셋 이름.
	static const FString AssetName;

	UPROPERTY()
	TObjectPtr<class UStudent> StudentSource; // 전방선언
};
