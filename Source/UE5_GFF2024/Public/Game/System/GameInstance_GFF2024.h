// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstance_GFF2024.generated.h"

/**
 *
 */
UCLASS()
class UE5_GFF2024_API UGameInstance_GFF2024 : public UGameInstance
{
	GENERATED_BODY()

public:
	//残機
	int32 Life = 2;

	//階層
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	int32 Floor = 1;

public:
	//初期化
	UFUNCTION(BlueprintCallable)
	void Initialize();

};
