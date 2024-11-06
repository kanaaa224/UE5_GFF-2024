// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/UI/HUD_TitleMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void AHUD_TitleMenu::BeginPlay()
{
	// WidgetBlueprintのClassを取得
	FString path = TEXT("/Game/Game/UI/Blueprints/WBP_TitleMenu.WBP_TitleMenu_C");
	TSubclassOf<UUserWidget> widgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*path)).LoadSynchronous();

	// PlayerControllerを取得
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (widgetClass && playerController)
	{
		// Widgetを作成し、Viewportに追加
		UUserWidget* userWidget = UWidgetBlueprintLibrary::Create(GetWorld(), widgetClass, playerController);
		userWidget->AddToViewport(0);

		// MouseCursorを表示
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(playerController, userWidget, EMouseLockMode::DoNotLock, true, false);
		playerController->SetShowMouseCursor(true);
	}
}

/* void AHUD_TitleMenu::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// プレイヤーコントローラーを取得
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (playerController)
	{
		// マウスカーソルを非表示に設定
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(playerController);
		playerController->SetShowMouseCursor(false);
	}
} */