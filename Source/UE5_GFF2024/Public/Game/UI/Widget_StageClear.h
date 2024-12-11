// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_StageClear.generated.h"

/**
 * 
 */
UCLASS()
class UE5_GFF2024_API UWidget_StageClear : public UUserWidget
{
	GENERATED_BODY()

public:
	void OpenNextLevel();
	
};
