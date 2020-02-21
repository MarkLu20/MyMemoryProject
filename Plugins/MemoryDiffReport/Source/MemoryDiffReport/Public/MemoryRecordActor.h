// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MemoryRecordActor.generated.h"

UENUM()
enum class ERecordType :uint8
{
	OnlyDedicatedServer,
	OnyClient,
	All



};

UCLASS()
class MEMORYDIFFREPORT_API AMemoryRecordActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMemoryRecordActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	/*每间隔多少小时对比内存情况*/
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		float RecordHour = 24;
	/*当游戏启动后间隔多少时间后开始记录内存*/
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		float StartDelayHour = 1;
	/*记录的类型 
	ERecordType：：OnlyDedicatedServer,只在独立服务器上记录内存情况
	ERecordType：：OnlyClient,只在客户端上记录内存情况
	ERecordType：：All,客户端服务器上都记录内存情况
	*/
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		ERecordType RecordType;
	/*开始记录内存使用情况*/
	void StartRecord();
};
