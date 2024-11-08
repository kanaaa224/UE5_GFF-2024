// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_NormalAttack_Enemy2.generated.h"

#define ATTACK_SPEED 2

/**
 * 
 */
UCLASS()
class UE5_GFF2024_API UBTT_NormalAttack_Enemy2 : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:
	//初期化がされたか
	bool initFlg;

	//攻撃が終わったか
	bool endAttack;
	//攻撃が始まったか
	bool startAttack;
	//ジャンプが終わったか
	bool endJump;
	//ジャンプ処理が何回行われたか
	int frameCnt_Jump;
	//攻撃を終えて立ち始める
	bool startStandUp;


	//現在のRotation
	FRotator nowRotaton;
	//現在のLocation
	FVector nowLocation;

public:
	explicit UBTT_NormalAttack_Enemy2(FObjectInitializer const& ObjectInitializer);

	// タスクが開始された時に呼ばれる
	void Init();
	//タスク実行
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	//:::::Blackboard::::://

	//Attack(プレイヤーまでの距離を入れる変数)
	UPROPERTY(EditDefaultsOnly, Category = AI)
	FName AttackKeyName;

private:
	FRotator CombineRotators(FRotator R1, FRotator R2);
};
