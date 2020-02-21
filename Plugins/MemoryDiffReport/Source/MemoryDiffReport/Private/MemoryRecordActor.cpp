// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryRecordActor.h"
#include "Engine/World.h"
#include "Misc/Paths.h"
#include "FileHelper.h"
#include "Core/Public/HAL/PlatformFilemanager.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AMemoryRecordActor::AMemoryRecordActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMemoryRecordActor::BeginPlay()
{
	Super::BeginPlay();
	if (!GIsEditor)
	{
		if (ERecordType::OnlyDedicatedServer == RecordType && IsRunningDedicatedServer())
		{
			StartRecord();
			
		}
		else if (ERecordType::OnyClient == RecordType && IsRunningClientOnly())
		{
			StartRecord();
		}
		else if (ERecordType::All == RecordType)
		{
			StartRecord();
		}
		
	}

	//StartRecord();

	//GetWorld()->Exec(GetWorld(),TEXT("")

}

// Called every frame
void AMemoryRecordActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMemoryRecordActor::StartRecord()
{
	
	
	
	auto StartRecordFunc = [&]()
	{
		UE_LOG(LogTemp, Error, TEXT("StartRecording............. StartDelayHour %f"), StartDelayHour * 60 * 60);
	FString MemoryPath = FPaths::ProjectSavedDir() / TEXT("Profiling") / TEXT("MemReports");
	
	if (IFileManager::Get().DirectoryExists(*MemoryPath))
	{
		IFileManager::Get().DeleteDirectory(*MemoryPath, false, true);
	}
	IFileManager::Get().MakeDirectory(*MemoryPath, true);
	UKismetSystemLibrary::ExecuteConsoleCommand(this, TEXT("MemReport-full"));
	FTimerHandle RecordHourHandle;
	GetWorld()->GetTimerManager().SetTimer(RecordHourHandle, [&](void)
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(this, TEXT("MemReport-full"));
		FTimerHandle DiffHandle;
		GetWorld()->GetTimerManager().SetTimer(DiffHandle, [&]() 
		{
			FString FullPlugintDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectPluginsDir()) ;
			FString CurrentDir = FullPlugintDir / TEXT("MemoryDiffReport") / TEXT("Binaries") / TEXT("Win64");
			FString FullBatExeDir = CurrentDir / TEXT("MemoryReport.exe");
			auto Handler = FPlatformProcess::CreateProc(*FullBatExeDir, nullptr, false, false, false, nullptr,0, *CurrentDir, nullptr);
			FTimerHandle ReaptRecord;
			GetWorld()->GetTimerManager().SetTimer(ReaptRecord,this,&AMemoryRecordActor::StartRecord, 30.0f,false);

		}, 15.0f, false);

	}, RecordHour * 60 * 60, false);
	
	};
	FTimerHandle TempHandle;
	GetWorld()->GetTimerManager().SetTimer(TempHandle, StartRecordFunc, StartDelayHour * 60 * 60, false);
}



