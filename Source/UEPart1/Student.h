// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Student.generated.h"

/**
 * 
 */
UCLASS()
class UEPART1_API UStudent : public UObject
{
	GENERATED_BODY()

public:
	UStudent();

	virtual void Serialize(FArchive& Ar) override;

	// Getter/Setter.
	int32 GetOrder() const { return Order; }
	void SetOrder(int32 InOrder) { Order = InOrder; }

	FString GetName() const { return Name; }
	void SetName(const FString& InName) { Name = InName; }
	
private:
	UPROPERTY(EditAnywhere, Category = "Data")
	int32 Order;

	UPROPERTY(EditDefaultsOnly, Category = "Data")
	FString Name;
};
