// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/Enemy/2/Enemy2Character.h"
#include "Perception/PawnSensingComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Game/Player_Cube.h"
#include "Game/Enemy/2/AIC_Enemy2.h"

// Sets default values
AEnemy2Character::AEnemy2Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	// 視野
	PawnSensingComp->SetPeripheralVisionAngle(60.f);
	// 見える範囲
	PawnSensingComp->SightRadius = 2000;
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemy2Character::OnSeePlayer);
}

// Called when the game starts or when spawned
void AEnemy2Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy2Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy2Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy2Character::OnSeePlayer(APawn* Pawn)
{
	AAIC_Enemy2* AIController = Cast<AAIC_Enemy2>(GetController());
	// プレイヤー
	APlayer_Cube* player = Cast<APlayer_Cube>(Pawn);

	if (AIController && player)
	{
		// AIControllerにプレイヤー情報を設定
		AIController->SetPlayerKey(player);
	}

	// 視野に入ったら画面に"See"と表示
	UKismetSystemLibrary::PrintString(this, "Enemy2 : SeePlayer", true, true, FColor::Blue, 2.f);
}

