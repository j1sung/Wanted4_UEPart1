// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "StudentData.h"
#include "Student.h"
#include "JsonObjectConverter.h"
#include "UObject/SavePackage.h"

// static 변수 초기화.
// /Game -> 프로젝트 경로/Content 경로를 가리킴.
const FString UMyGameInstance::PackageName = TEXT("/Game/Student");
const FString UMyGameInstance::AssetName = TEXT("Student");

// UStudent 출력용 함수.
void PrintStudentInfo(
	const UStudent* InStudent,
	const FString& InTag)
{
	// 출력.
	UE_LOG(
		LogTemp,
		Log,
		TEXT("[%s] 이름: %s, 순번: %d"),
		*InTag,
		*InStudent->GetName(),
		InStudent->GetOrder()
	);
}

UMyGameInstance::UMyGameInstance()
{
}

void UMyGameInstance::Init()
{
	Super::Init();

	// 구조체 객체 생성.
	FStudentData RawDataSource(23, TEXT("안지성"));

	// 파일로 저장하기 위한 경로 생성.
	const FString SavePath = FPaths::Combine(
		FPlatformMisc::ProjectDir(), TEXT("Saved")
	);

	// 파일 저장 테스트를 위한 구간.
	{
		// 파일 이름.
		const FString RawDataFileName(TEXT("RawData.bin"));

		// 저장 경로 + 파일 이름.
		FString RawDataAbsolutePath
			= FPaths::Combine(SavePath, RawDataFileName);

		// 파일 경로 출력
		UE_LOG(
			LogTemp,
			Log,
			TEXT("저장할 파일 전체 경로: %s"),
			*RawDataAbsolutePath
		);

		// 경로 처리.
		FPaths::MakeStandardFilename(RawDataAbsolutePath);

		UE_LOG(
			LogTemp,
			Log,
			TEXT("변경할 파일 전체 경로: % s"),
			*RawDataAbsolutePath
		);

		// 직렬화 사용해서 저장.
		// FArchive = FileOpen과 비슷함 Writer로 열기.
		FArchive* RawFileWriteAr
			= IFileManager::Get().CreateFileWriter(
				*RawDataAbsolutePath);
		if (RawFileWriteAr)
		{
			// 파일에 기록.
			//*RawFileWriteAr << RawDataSource.Order;
			//*RawFileWriteAr << RawDataSource.Name;
			// 연산자 오버로딩으로 StudentData.h에서 구현
			*RawFileWriteAr << RawDataSource;

			// 파일 닫기.
			RawFileWriteAr->Close();

			// 메모리 해제.
			delete RawFileWriteAr;
			RawFileWriteAr = nullptr;
		}

		// 파일로부터 데이터를 읽어와서 구조체에 복원.
		// 역직렬화(Deserialization).
		FStudentData RawDataDeserialized;

		// 파일 읽기를 위한 아카이브 얻어오기.
		FArchive* RawFileReaderAr
			= IFileManager::Get().CreateFileReader(
				*RawDataAbsolutePath);
		if (RawFileReaderAr) // 경로 읽기 실패 처리
		{
			// 구조체로 값 전달.
			*RawFileReaderAr << RawDataDeserialized;

			// 파일 닫기.
			RawFileReaderAr->Close();

			// 객체 메모리 해제.
			delete RawFileReaderAr;
			RawFileReaderAr = nullptr;

			// 복원된 구조체 값 출력.
			UE_LOG(
				LogTemp,
				Log,
				TEXT("[RawData] 이름: %s, 순번: %d"),
				*RawDataDeserialized.Name,
				RawDataDeserialized.Order
			);
		}
	}

	// 언리얼 오브젝트 생성.
	StudentSource = NewObject<UStudent>();
	StudentSource->SetName(TEXT("지성"));
	StudentSource->SetOrder(31);

	// 직렬화 테스트를 위한 구간 나누기.
	{
		// 저장할 파일 이름 값.
		const FString& ObjectDataFileName(
			TEXT("ObjectData.bin")
		);

		// 파일 이름을 포함한 경로 생성.
		FString ObjectDataAlsolutePath
			= FPaths::Combine(SavePath, ObjectDataFileName);

		// 경로 값 정리.
		FPaths::MakeStandardFilename(ObjectDataAlsolutePath);

		// 메모리를 담을 버퍼.
		TArray<uint8> BufferArray;
		FMemoryWriter MemoryWriter(BufferArray);

		// MemoryWriter를 사용해서
		// 언리얼 오브젝트를 직렬화해 값을 기록.
		StudentSource->Serialize(MemoryWriter);

		// 파일에 기록.
		TUniquePtr<FArchive> FileWriteAr
			= TUniquePtr<FArchive>(
				IFileManager::Get().CreateFileWriter(
					*ObjectDataAlsolutePath)
			);
		// 파일을 잘 열었는지 확인.
		if (FileWriteAr)// Null check
		{
			// 파일에 기록 처리.
			*FileWriteAr << BufferArray;
			// 파일 닫기.
			FileWriteAr->Close();
		}


		// 언리얼 오브젝트로 복원.
		TArray<uint8> BufferArrayFromFile;
		TUniquePtr<FArchive> FileReaderAr
			= TUniquePtr<FArchive>(
				IFileManager::Get().CreateFileReader(
					*ObjectDataAlsolutePath)
			);
		if (FileReaderAr)
		{
			*FileReaderAr << BufferArrayFromFile;
			FileReaderAr->Close();

			// 바이트 배열에 저장된 정보를
			// 메로리 리더를 통해 객체로 복원.
			FMemoryReader MemoryReaderAr(BufferArrayFromFile);
			UStudent* StudentDest = NewObject<UStudent>();
			StudentDest->Serialize(MemoryReaderAr);

			// 출력.
			UE_LOG(
				LogTemp,
				Log,
				TEXT("[ObjectData] 이름: %s, 순번: %d"),
				*StudentDest->GetName(),
				StudentDest->GetOrder()
			);
		}
	}

	// JSON(JavaScript Object Notation) 직렬화.
	{
		const FString JsonDataFileName(
			TEXT("StudentJsonData.txt")
		);

		// 저장할 파일 경로 값.
		FString JsonDataAbsolutePath
			= FPaths::Combine(SavePath, JsonDataFileName);

		// 경로 값 정리.
		FPaths::MakeStandardFilename(JsonDataAbsolutePath);

		// JSON 직렬화 과정.
		// UObject-> JSON Object -> JSON 문자열 -> 기록
		TSharedRef<FJsonObject> JsonObjectRef
			= MakeShared<FJsonObject>();

		// JSON 오브젝트로 변환
		FJsonObjectConverter::UStructToJsonObject( // 리플랙션 전달/비교
			StudentSource->StaticClass(),
			StudentSource,
			JsonObjectRef
		);

		// 직렬화.
		FString JsonOutString;
		TSharedRef<TJsonWriter<TCHAR>> JsonWriterAr =
			TJsonWriterFactory<TCHAR>::Create(&JsonOutString);

		if(FJsonSerializer::Serialize(JsonObjectRef, JsonWriterAr))
		{
			// 성공한 경우에 파일에 저장
			FFileHelper::SaveStringToFile(
				JsonOutString,
				*JsonDataAbsolutePath
			);
		}

		// 역직렬화.
		FString JsonInString;
		// 파일에서 문자열로 읽어오기.
		FFileHelper::LoadFileToString(JsonInString, *JsonDataAbsolutePath);

		UE_LOG(
			LogTemp,
			Log,
			TEXT("[Json] %s"),
			*JsonInString
		);

		// 역직렬화를 위한 아카이브 생성.
		TSharedRef<TJsonReader<TCHAR>> JsonReaderAr
			= TJsonReaderFactory<TCHAR>::Create(JsonInString);

		TSharedPtr<FJsonObject> JsonObjectDest;
		if (FJsonSerializer::Deserialize(JsonReaderAr, JsonObjectDest))
		{
			// 언리얼 오브젝트 생성 후 변환.
			UStudent* JsonStudentDest = NewObject<UStudent>();
			// JsonObjectConverter를 활용해 변환.
			if (FJsonObjectConverter::JsonObjectToUStruct(
				JsonObjectDest.ToSharedRef(),
				UStudent::StaticClass(),
				JsonStudentDest))
			{
				//// 출력.
				//UE_LOG(
				//	LogTemp,
				//	Log,
				//	TEXT("[JsonData] 이름: %s, 순번: %d"),
				//	*JsonStudentDest->GetName(),
				//	JsonStudentDest->GetOrder()
				//);
				PrintStudentInfo(JsonStudentDest, TEXT("JsonData"));
			}
		}
	}

	// 패키지 저장 함수 실행(호출).
	//SaveStudentPackage();

	// 패키지 로드 함수 실행
	//LoadStudentPackage();

	// 경로 값을 사용해 오브젝트를 로드하는 함수 실행.
	//LoadStudentObject();

	// 에셋 스트리밍 관리자를 통한 에셋 로드.
	// 경로 값.
	const FString SoftObjectPath 
		= FString::Printf(TEXT("%s.%s"),
		*PackageName, *AssetName
		);
	
	// 비동기 로드.
	Handle = StreamableManager.RequestAsyncLoad(
		SoftObjectPath,
		[&]()
		{
			// 로드가 문제없이 완료됐는지 확인.
			if (Handle.IsValid() && Handle->HasLoadCompleted())
			{
				// 핸들로부터 언리얼 오브젝트 가져오기.
				UStudent* Student 
					= Cast<UStudent>(Handle->GetLoadedAsset());
				if (Student)
				{
					PrintStudentInfo(
						Student,
						TEXT("AsyncLoad")
					);

					// 핸들 해제.
					Handle->ReleaseHandle();
					Handle.Reset();
				}
			}
		}
	);
}

void UMyGameInstance::SaveStudentPackage() const
{
	// 예외 처리(이미 만들어졌는데 또 실행해서 만들면 안되니까)
	UPackage* StudentPackage = LoadPackage(nullptr, *PackageName, LOAD_None);
	// 패키지가 이미 있다면, 에셋을 완전히 처리.
	if (StudentPackage)
	{
		StudentPackage->FullyLoad();
	}

	// 패키지 생성.
	StudentPackage = CreatePackage(*PackageName);
	// 패키지에 사용할 플래그 지정.
	// RF_Public | RF_Standalone 플래그 값이 가장 일반적
	EObjectFlags ObjectFlag = RF_Public | RF_Standalone;

	// 패키지에 저장할 언리얼 오브젝트 생성.
	UStudent* Student = NewObject<UStudent>(
		StudentPackage,
		UStudent::StaticClass(),
		*AssetName,
		ObjectFlag
	);
	Student->SetName(TEXT("안지성"));
	Student->SetOrder(11);

	// 서브 오브젝트 추가.
	const int32 SubObjectCount = 10;
	for (int32 ix = 1; ix <= SubObjectCount; ++ix)
	{
		// 생성할 객체의 이름.
		FString SubObjectName
			= FString::Printf(TEXT("Student%d"), ix);

		// 객체 생성.
		UStudent* SubStudent
			= NewObject<UStudent>(
				Student,
				UStudent::StaticClass(),
				*SubObjectName,
				ObjectFlag
			);

		// 값 설정.
		SubStudent->SetName(FString::Printf(TEXT("학생%d"), ix));
		SubStudent->SetOrder(ix);
	}

	// 패키지 저장.
	FString PackageFileName
		= FPackageName::LongPackageNameToFilename(
			PackageName, FPackageName::GetAssetPackageExtension()
		);

	// 참고로.. 이렇게도 가능.
	/*FString PackageFileName2
		= FPaths::Combine(
			FPlatformMisc::ProjectDir(),
			TEXT("Content"),
			FString::Printf(TEXT("%s%s"),
				*PackageName, 
				*FPackageName::GetAssetPackageExtension())
			);*/

	// 경로 값 정리.
	FPaths::MakeStandardFilename(PackageFileName);

	// 저장할 옵션 설정.
	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = ObjectFlag;

	// 패키지 저장.
	if (UPackage::SavePackage(
		StudentPackage,
		nullptr,
		*PackageFileName,
		SaveArgs))
	{
		UE_LOG(
			LogTemp,
			Log,
			TEXT("패키지가 성공적으로 저장되었습니다.")
		);
	}
	
}

void UMyGameInstance::LoadStudentPackage() const
{
	// 패키지 로드.
	UPackage* StudentPackage 
		= LoadPackage(nullptr, *PackageName, LOAD_None);
	// 패키지 로드 실패 처리
	if (!StudentPackage)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("패키지를 찾을 수 없습니다.")
		);
		return;
	}

	// 완전히 로드되도록 함수 실행.
	StudentPackage->FullyLoad();

	// 패키지 안에 있는 언리얼 오브젝트(에셋) 검색.
	UStudent* Student 
		= FindObject<UStudent>(StudentPackage, *AssetName);

	if (Student)
	{
		// 로드한 결과 출력.
		PrintStudentInfo(Student, TEXT("FindObject Asset"));
	}
}

void UMyGameInstance::LoadStudentObject() const
{
	// 오브젝트 경로 값.
	const FString SoftObjectPath
		= FString::Printf(TEXT("%s.%s"),
			*PackageName, *AssetName
		);

	// 오브젝트 로드.
	UStudent* Student 
		= LoadObject<UStudent>(nullptr, *SoftObjectPath);
	if (Student)
	{
		// 로드한 오브젝트 정보 출력.
		PrintStudentInfo(
			Student, TEXT("LoadObject Asset")
		);
	}
}
