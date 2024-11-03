// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy1Character.generated.h"

class PolygonRotationManager;
class UStaticMeshComponent;

UCLASS()
class UE5_GFF2024_API AEnemy1Character : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy1Character();

protected:
	virtual void BeginPlay() override;
	//virtual void BeginDestroy() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	virtual void Tick(float DeltaTime) override;

private:
	/*:::::変数:::::*/
	//体力
	float health;

	bool IsMoving;

	FVector Vector;

	PolygonRotationManager* RotationManager;

	UPROPERTY(VisibleAnywhere, Category = Character, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> box;

public:
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnSeePlayer(APawn* Pawn);

public:
	//ダメージを受ける処理
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)override;

public:
	void MoveProcess();

	void SetVector(FVector v)
	{
		Vector = v;
	}
	void SetIsMoving(bool b)
	{
		IsMoving = b;
	}
public:
	//定義
	// 立方体の頂点を定義（中心が原点、1辺の長さが2の立方体と仮定）
	TArray<FVector> CubeVertices = {
		FVector(-1, -1, -1), FVector(1, -1, -1), FVector(1, 1, -1), FVector(-1, 1, -1),  // 下面
		FVector(-1, -1,  1), FVector(1, -1,  1), FVector(1,  1,  1), FVector(-1,  1,  1)   // 上面
	};

	// 立方体の6つの面を定義（各面は頂点インデックスのリスト）
	TArray<TArray<int32>> CubeFaces = {
		{0, 1, 2, 3},  // 底面
		{4, 5, 6, 7},  // 上面
		{0, 1, 5, 4},  // 前面
		{2, 3, 7, 6},  // 後面
		{0, 3, 7, 4},  // 左面
		{1, 2, 6, 5}   // 右面
	};
};