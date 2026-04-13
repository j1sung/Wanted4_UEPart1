// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Card.h"
#include "CourseInfo.h" // 전방선언 했으니

UMyGameInstance::UMyGameInstance()
{
	// 기본 값은 CDO라는 특별한 템플릿 객체에 저장됨.
	SchoolName = TEXT("기본학교");
}

void UMyGameInstance::Init()
{
	Super::Init();
	
	UE_LOG(LogTemp, Log, TEXT("========================"));

	// 학사 정보 객체 생성.
	CourseInfo = NewObject<UCourseInfo>(this); // outer 지정 this 추가(런타임 지정이라 필요시)

	// 3명 학생 추가.
	UStudent* Student1 = NewObject<UStudent>();
	Student1->SetName(TEXT("학생1"));

	UStudent* Student2 = NewObject<UStudent>();
	Student2->SetName(TEXT("학생2"));

	UStudent* Student3 = NewObject<UStudent>();
	Student3->SetName(TEXT("학생3"));

	// 알림에 구독.
	CourseInfo->OnChanged.AddUObject(Student1, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student2, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student3, &UStudent::GetNotification);

	// 변경된 학사 정보 발행.
	CourseInfo->ChangeCourseInfo(SchoolName, TEXT("변경된 학사 정보"));

	UE_LOG(LogTemp, Log, TEXT("========================"));


	/*
	// TArray는 언리얼 엔진이 지원하는 동적 배열
	// STL의 std::vector와 동일한 기능 제공.
	// 언리얼 오브젝트에 특화된 동적 배열.
	TArray<UPerson*> Persons =
	{ 
		NewObject<UStudent>(),
		NewObject<UTeacher>(),
		NewObject<UStaff>()
	};

	// 이름 출력.
	for (const UPerson* Person : Persons)
	{
		UE_LOG(LogTemp, Log, TEXT("구성원 이름: %s"), *Person->GetName());
	}

	UE_LOG(LogTemp, Log, TEXT("========================"));

	for (UPerson* Person : Persons)
	{
		// 인터페이스로 형변환. -> 인터페이스가 없으면 else로 빠지게
		// 다운 캐스팅 (위험한 형변환 - RTTI 고려해야 함).
		ILessonInterface* LessonInterface
			= Cast<ILessonInterface>(Person); // 빠른 형변환
		if (LessonInterface)
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여할 수 있습니다."),
				*Person->GetName()
			);
			LessonInterface->DoLesson();
		}
		else 
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여할 수 없습니다."),
				*Person->GetName()
			);
		}
	}
	UE_LOG(LogTemp, Log, TEXT("========================"));

	for (const auto Person : Persons)
	{
		// 카드 가져오기.
		const UCard* OwnCard = Person->GetCard();
		// 어서트.
		ensureAlways(OwnCard); // OwnCard값이 null이면 안된다.

		//*UE_LOG(
		//	LogTemp, Log, TEXT("%s님이 소유한 카드 종류: %d"),
		//	*Person->GetName(),
		//	OwnCard->GetCardType()
		//);

		// 열거형의 문자열 값 가져오기.
		const UEnum* CardEnumType = FindObject<UEnum>(nullptr, 
				TEXT("/Script/UEPart1.ECardType")
			);

		if (CardEnumType)
		{
			FString CardMetaData = CardEnumType->GetDisplayNameTextByValue(
				(int64)OwnCard->GetCardType()
			).ToString();

			UE_LOG(
				LogTemp,
				Log,
				TEXT("%s님이 소유한 카드 종류 %s"),
				*Person->GetName(), *CardMetaData
			);
		}
	}
	*/

	/*
	// 클래스 정보 가져오기.
	UClass* ClassRuntime = GetClass();
	UClass* ClassCompile = UMyGameInstance::StaticClass();

	// 어서트.
	// check(ClassRuntime != ClassCompile); // 크래시까지 발생시키는 어써트.
	// ensure(ClassRuntime == ClassCompile); // 출력 로그 창에 오류 표시. 한번만.
	// ensureAlways() // 실행에서 반복적

	// 클래스 이름 출력.
	UE_LOG(
		LogTemp, 
		Log, 
		TEXT("학교를 담당하는 클래스: %s, %s"),
		*ClassRuntime->GetName(),
		*ClassCompile->GetName()
	);

	SchoolName = TEXT("청강문화산업대학교");
	UE_LOG(
		LogTemp,
		Log,
		TEXT("학교 이름: %s"),
		*SchoolName
	);
	UE_LOG(
		LogTemp,
		Log,
		TEXT("학교 이름: %s"),
		*GetClass()->GetDefaultObject<UMyGameInstance>()->SchoolName
	);
	// 둘의 값이 다름 -> CDO와 런타임 변수 값이 다름

	UE_LOG(LogTemp, Log, TEXT("====================="));

	// 학생/선생님 객체 생성.
	UStudent* Student = NewObject<UStudent>();
	UTeacher* Teacher = NewObject<UTeacher>();

	// 학생 클래스의 Getter/Setter 사용.
	Student->SetName(TEXT("학생1"));
	UE_LOG(LogTemp, Log, TEXT("새로운 학생 이름: %s"), *Student->GetName());

	// 언리얼의 리플렉션을 활용해 프로퍼티 정보 설정 및 가져오기.
	
	//UTeacher::StaticClass()->FindPropertyByName(TEXT("Name"));
	FProperty* NameProp = 
		Teacher->GetClass()->FindPropertyByName(TEXT("Name"));
	if (NameProp)
	{
		// 리플렉션을 활용해 현재 프로퍼티에 저장된 값 가져오기.
		FString CurrentTeacherName;
		NameProp->GetValue_InContainer(Teacher, &CurrentTeacherName);
		UE_LOG(
			LogTemp,
			Log,
			TEXT("현재 선생님 이름: %s"),
			*CurrentTeacherName
		);

		// 리플렉션을 활용해 프로퍼티에 새로운 값 저장.
		FString NewTeacherName = (TEXT("지성"));
		NameProp->SetValue_InContainer(Teacher, &NewTeacherName);
		UE_LOG(
			LogTemp,
			Log,
			TEXT("현재 선생님 이름: %s"),
			*Teacher->GetName()
		);
	}

	// 함수 호출 (리플렉션 활용).
	UFunction* DoLessonFunc 
		= Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson"));

	if (DoLessonFunc)
	{
		Teacher->ProcessEvent(DoLessonFunc, nullptr);
	}*/

	/*
	// 로그 출력.
	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("Hello Unreal"));
	// L"%s"랑 같은 widechar로 변환 - 16비트 2
	// TEXT매크로가 ##으로 이어 붙여주는 

	// TCHAR | FString.
	// TCHAR = wchar_t
	TCHAR LogCharArray[] = TEXT("Hello Unreal");  // L 붙여주는거랑 똑같다.
	// UE_LOG 함수.
	// 1. Log 카테고리(타입).
	// 2. 로그 수준(Log, Warning, Error).
	// 3. 포맷 (format, 서식) - 출력할 값의 타입.
	// 가변 인자: 포맷에 지정한 타입에 알맞은 값을 전달.
	UE_LOG(LogTemp, Log, TEXT("%s"), LogCharArray);

	FString LogCharString = LogCharArray;
	//UE_LOG(LogTemp, Log, TEXT("%s"), LogCharString);
	// FString은 앞에 *연산자를 붙여야함 -> 연산자 오버로딩(operator) 사용됨
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

	}*/
}