// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init();

	// 로그 출력.
	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("Hello Unreal"));
	// L"%s"랑 같은 widechar로 변환 - 16비트 2
	// TEXT매크로가 ##으로 이어 붙여주는 

	// TCHAR | FString.
	TCHAR LogCharArray[] = TEXT("Hello Unreal");
	// UE_LOG 함수.
	// Log 카테고리(타입).
	// 로그 수준(Log, Warning, Error).
	// 포맷 (format, 서식) - 출력할 값의 타입.
	// 가변 인자: 포맷에 지정한 타입에 알맞은 값을 전달.
	UE_LOG(LogTemp, Log, TEXT("%s"), LogCharArray);

	FString LogCharString = LogCharArray;
	//UE_LOG(LogTemp, Log, TEXT("%s"), LogCharString);
	// FString은 앞에 *연산자를 붙여야함
	UE_LOG(LogTemp, Log, TEXT("%s"), *LogCharString);

	// FString에서 TCHAR 포인터를 가져오는 방법.
	const TCHAR* LogCharPtr = *LogCharString;
	TCHAR* LogCharDataPtr = LogCharString.GetCharArray().GetData();

	// 문자열 복사.
	TCHAR LogCharArrayWithSize[100] = {};
	FCString::Strcpy(
		LogCharArrayWithSize, 
		LogCharString.Len(),
		*LogCharString
	);

	// 복사된 문자열 출력.
	UE_LOG(LogTemp, Log, TEXT("%s"), LogCharArrayWithSize);

	// 문자열 자르기.
	if (LogCharString.Contains(TEXT("unreal"), ESearchCase::IgnoreCase))
	{
		// 시작 문자열 검색.
		int32 Index 
			= LogCharString.Find(TEXT("unreal"), ESearchCase::IgnoreCase);

		FString EndString = LogCharString.Mid(Index);

		UE_LOG(LogTemp, Log, TEXT("EndString: %s"), *EndString);
	}

	// 문자열 나누기.
	FString Left, Right;
	if (LogCharString.Split(TEXT(" "), &Left, &Right))
	{
		UE_LOG(LogTemp, Log, TEXT("split Result: %s 와 %s"), *Left, *Right);
	}

	// 변환 함수.
	int32 IntValue = 32;
	float FloatValue = 3.141592f;

	FString FloatIntString
		= FString::Printf(TEXT("Int: %d, Float: %f"), IntValue, FloatValue);

	FString FloatString = FString::SanitizeFloat(FloatValue);
	FString IntString = FString::FromInt(IntValue);

	UE_LOG(LogTemp, Log, TEXT("%s"), *FloatIntString);
	UE_LOG(LogTemp, Log, TEXT("Int: %s, Float: %s"), *IntString, *FloatString);

	// 문자열에서 숫자로 변환.
	int32 IntValueFromString = FCString::Atoi(*IntString);
	float FloatValueFromString = FCString::Atof(*FloatString);

	UE_LOG(LogTemp, Log, TEXT("Int: %d, Float: %f"), 
		IntValueFromString, FloatValueFromString);

	// FNAME 사용.
	FName Key1(TEXT("PELVIS"));
	FName Key2(TEXT("pelvis"));

	// 비교 결과.
	FString Result = Key1 == Key2 ? TEXT("같음") : TEXT("다름");
	UE_LOG(LogTemp, Log, TEXT("FName 비교 결과: %s"), *Result);
	
	// 부하가 큰 경우.
	for (int ix = 0; ix < 10000; ++ix)
	{
		// 키 값.
		// FName SearchInNamePool = FName(TEXT("pelvis")); 이렇게 하지 말자

		const static FName SearchInNamePool = FName(TEXT("pelvis"));
		// 읽기 전용이면 const를 잘 쓰자

	}
}