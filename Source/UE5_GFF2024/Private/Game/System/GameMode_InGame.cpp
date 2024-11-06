// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/System/GameMode_InGame.h"
#include "Game/Player_Cube.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Game/System/GameInstance_GFF2024.h"

AGameMode_InGame::AGameMode_InGame()
{
	DefaultPawnClass = APlayer_Cube::StaticClass();
}

void AGameMode_InGame::BeginPlay()
{
	Super::BeginPlay();

	//Viewportに配置されたPlayerStartを探す
	const APlayerStart* PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()));

	//PlayerStartの位置情報をRespawnの位置として保持する
	SpawnTransform = PlayerStart->GetActorTransform();

}

void AGameMode_InGame::KillPlayer(APlayer_Cube* Player)
{
	//Playerを破棄する
	Player->Destroy();

	//GameInstanceを取得する
	UGameInstance_GFF2024* GameInstance = Cast<UGameInstance_GFF2024>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstance)
	{
		//Lifeをデクリメントする
		GameInstance->Life--;

		if (0 <= GameInstance->Life)
		{
			//Respawnを行う
			RespawnPlayer();
		}
		else
		{
			//GameをRestartする
			UE_LOG(LogTemp, Display, TEXT("GameOver"));
			//RestartGame();
		}
	}
}

void AGameMode_InGame::RestartGame()
{

}

void AGameMode_InGame::RespawnPlayer()
{
	//PlayerをSpawnする
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	APlayer_Cube* Player = GetWorld()->SpawnActor<APlayer_Cube>(APlayer_Cube::StaticClass(), SpawnTransform, SpawnInfo);

	//Controllerを設定する
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->Possess(Player);
}
