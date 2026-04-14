// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

// 이름 자동완성 해주는 함수.
FString MakeRandomName()
{
	// 3글자.
	TCHAR FirstChar[] = TEXT("김이박최");
	TCHAR MiddleChar[] = TEXT("상혜지성");
	TCHAR LastChar[] = TEXT("수은원연");

	// 동적 배열을 사용할 때 가능하다면 재할당을 방지하는게 좋음.
	TArray<TCHAR> RandArray;
	RandArray.SetNum(3);
	RandArray[0] = FirstChar[FMath::RandRange(0, 3)];
	RandArray[1] = MiddleChar[FMath::RandRange(0, 3)];
	RandArray[2] = LastChar[FMath::RandRange(0, 3)];

	// 문자열로 변환이 가능하도록 반환.
	return RandArray.GetData();
}

void UMyGameInstance::Init()
{
	Super::Init();

	// 학생 이름 데이터 생성.
	const int32 StudentNum = 300;
	for (int32 ix = 1; ix <= StudentNum; ++ix)
	{
		StudentsData.Emplace(FStudentData(MakeRandomName(), ix));
	}

	// 구조체 TArray 배열
	UE_LOG(
		LogTemp,
		Log,
		TEXT("모든 학생 이름의 수: %d"),
		StudentsData.Num()
	);

	// 학생 데이터에서 이름 값만 추출해서 배열에 저장.
	TArray<FString> AllStudentNames;

	// 알고리즘을 활용해서 이름 값 추출.
	Algo::Transform(StudentsData, AllStudentNames,
		[](const FStudentData& Val)
		{
			return Val.Name;
		}
	);

	UE_LOG(
		LogTemp,
		Log,
		TEXT("모든 학생 이름의 수: %d"),
		AllStudentNames.Num()
	);

	// 학생 데이터를 TSet으로 변환.
	TSet<FString> AllUniqueNames;
	Algo::Transform(
		StudentsData,
		AllUniqueNames,
		[](const FStudentData& Val)
		{
			return Val.Name;
		}
	);

	// 중복을 제거해서 출력
	UE_LOG(
		LogTemp,
		Log,
		TEXT("중복 없는 학생 이름의 수: %d"),
		AllUniqueNames.Num()
	);

	// 학생 데이터를 TMap으로 변환.
	Algo::Transform(
		StudentsData,
		StudentsMap,
		[](const FStudentData& Val)
		{
			return TPair<int32, FString>(
				Val.Order, Val.Name
			);
		}
	);


	UE_LOG(
		LogTemp,
		Log,
		TEXT("순번에 따른 학생 맵의 데이터 수: %d"),
		StudentsMap.Num()
	);

	// 이름 값을 키로하는 맵.
	TMap<FString, int32> StudentsMapByUniqueName;

	// 학생 데이터를 Map으로 변환.
	Algo::Transform(
		StudentsData,
		StudentsMapByUniqueName,
		[](const FStudentData& Val)
		{
			return TPair<FString, int32>(
				Val.Name, Val.Order
			);
		}
	);

	UE_LOG(
		LogTemp,
		Log,
		TEXT("이름에 따른 학생 맵의 데이터 수: %d"),
		StudentsMapByUniqueName.Num()
	);

	// 이름 중복을 허용하려는 경우.
	TMultiMap<FString, int32> StudentsMapByName;
	Algo::Transform(
		StudentsData,
		StudentsMapByName,
		[](const FStudentData& Val) -> TPair<FString, int32> // 반환값 명시 지정
		{
			return TPair<FString, int32>(
				Val.Name, Val.Order
			);
		}
	);

	UE_LOG(
		LogTemp,
		Log,
		TEXT("이름에 따른 학생 멀티맵의 데이터 수: %d"),
		StudentsMapByName.Num()
	);

	// 검색.
	const FString TargetName(TEXT("이혜은"));
	TArray<int32> AllOrders;
	StudentsMapByName.MultiFind(TargetName, AllOrders);

	UE_LOG(
		LogTemp,
		Log,
		TEXT("이름이 %s인 학생 수: %d"),
		*TargetName, AllOrders.Num()
	);

	// TSet에 구조체 넣어보기.
	TSet<FStudentData> StudentsSet;
	for (int32 ix = 1; ix <= StudentNum; ++ix)
	{
		StudentsSet.Emplace(FStudentData(MakeRandomName(), ix));
	}

	UE_LOG(
		LogTemp,
		Log,
		TEXT("학생 데이터 셋의 수: %d"),
		StudentsSet.Num()
	);
}