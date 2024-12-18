// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_InGame.generated.h"

/**
 *
 */
UCLASS()
class UE5_GFF2024_API AGameMode_InGame : public AGameModeBase
{
	GENERATED_BODY()

public:
	FTransform SpawnTransform;			//スポーン座標

	TSubclassOf <class UUserWidget> GameOverWidget;

	TSubclassOf <class UUserWidget> GameClearWidget;

	TSubclassOf <class UUserWidget> StageClearWidget;

public:
	//コンストラクタ
	AGameMode_InGame();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	//Playerを破棄する
	void KillPlayer(class APlayer_Cube* Player);

	//GameをRestartする
	void RestartGame();

	//ゲームクリア
	void GameClear();

	//ステージクリア
	void StageClear();

private:
	//PlayerをRespawnする
	void RespawnPlayer();


};
