// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Enemy/2/BTT_SpecialAttack_Enemy2.h"

//Enemy2Controller
#include "Game/Enemy/2/AIC_Enemy2.h"
//PlayController
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

UBTT_SpecialAttack_Enemy2::UBTT_SpecialAttack_Enemy2(FObjectInitializer const& ObjectInitializer)
{
	stopMove = false;
}

void UBTT_SpecialAttack_Enemy2::Init()
{
	onecCalcFTL_Flg = false;
	floatEnd = true;
}

EBTNodeResult::Type UBTT_SpecialAttack_Enemy2::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//AIコントローラーを取得
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr) {
		return EBTNodeResult::Failed;
	}
	//コントローた(AIC_Enemy2)を取得
	AAIC_Enemy2* MyAIController = Cast<AAIC_Enemy2>(AIController);
	if (MyAIController == nullptr) {
		return EBTNodeResult::Failed;
	}
	//コントローラ(AIC_Enemy2)からPawnを取得
	APawn* ControlledPawn = MyAIController->GetPawn();
	if (ControlledPawn == nullptr) {
		return EBTNodeResult::Failed;
	}
	AEnemy2Character* MyPawn = Cast<AEnemy2Character>(ControlledPawn);
	if (MyPawn == nullptr) {
		return EBTNodeResult::Failed;
	}

	//プレイヤーコントローラーを取得
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController == nullptr) {
		return EBTNodeResult::Failed;
	}
	//コントローラからPawnを取得
	APawn* PlayerPawn = PlayerController->GetPawn();
	if (PlayerPawn == nullptr) {
		return EBTNodeResult::Failed;
	}

	//通常攻撃中だった場合はすぐに攻撃にうつらず体制を戻す
	FRotator checkRotator = MyPawn->GetActorRotation();
	if (checkRotator.Pitch != 0.0f) {
		stopMove = true;
		checkRotator.Pitch += 3.0f;

		if (checkRotator.Pitch >= 0.0f) {
			checkRotator.Pitch = 0.0f;
			stopMove = false;
		}

		MyPawn->SetActorRotation(checkRotator);
	}
	else if (checkRotator.Pitch == 0.0f) {
		stopMove = false;
	}


	//浮き上がり処理
	if (stopMove == false) {
		Float(MyPawn, OnecCalcFloatTargetLocation(MyPawn));
	}
	//棒の生成処理
	if (floatEnd == true) {
		//UE_LOG(LogTemp, Log, TEXT("Float End -----> next CreateActor"));
		if (endCreateObject == false) {
			for (int i = 1; i <= 4; i++) {
				//Objectを１つ生成する
				MyPawn->SpawnAttackObject(i);
				if (i == 4) {
					endCreateObject = true;
				}
			}
		}
	}

	return EBTNodeResult::Succeeded;
}

void UBTT_SpecialAttack_Enemy2::Float(AEnemy2Character* myPawn, FVector targetLocation)
{
	FVector nowLocation = myPawn->GetActorLocation();

	nowLocation = FMath::VInterpTo(nowLocation, targetLocation, GetWorld()->GetDeltaSeconds(), 3.0f);

	myPawn->SetActorLocation(nowLocation);
}

FVector UBTT_SpecialAttack_Enemy2::OnecCalcFloatTargetLocation(AEnemy2Character* pawn)
{
	FVector tmp = pawn->GetActorLocation();
	
	if (onecCalcFTL_Flg == false) {
		calcResultFTL = FVector(tmp.X, tmp.Y, tmp.Z + 1600.0f);//数字の部分で上昇する値を変える
		onecCalcFTL_Flg = true;
	}
	else if (onecCalcFTL_Flg == true) {
		if (calcResultFTL.Z - 30.0f <= tmp.Z) {
			floatEnd = true;
		}
	}

	return calcResultFTL;
}
