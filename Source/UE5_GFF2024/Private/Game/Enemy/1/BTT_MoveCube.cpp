// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Enemy/1/BTT_MoveCube.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Game/Enemy/1/Enemy1Character.h"
#include "Game//Enemy/1/AIC_Enemy1.h"
#include "Game/Enemy/Commons/PolygonRotationManager.h"
#include "Math\RandomStream.h"
#include "Kismet/GameplayStatics.h"

UBTT_MoveCube::UBTT_MoveCube()
{
	NodeName = "Custom Task";
}

EBTNodeResult::Type UBTT_MoveCube::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    //初期化
    if (!IsInit)
    {
        Init();
    }

    // AIコントローラとブラックボードコンポーネントを取得
    AAIController* AIController = OwnerComp.GetAIOwner();
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (AIController == nullptr || BlackboardComp == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    // `Target` キーの値を取得
    UObject* PlayerObject = BlackboardComp->GetValueAsObject(GetSelectedBlackboardKey());

    if (PlayerObject != nullptr)
    {
        // `Target` の値を使った処理を行う
        // 例: ターゲットが見つかった場合の処理など
        //UKismetSystemLibrary::PrintString(this, "tes", true, true, FColor::Blue, 2.f);
        
        if (AAIC_Enemy1* AIC = Cast<AAIC_Enemy1>(OwnerComp.GetAIOwner()))
        {
            if (AEnemy1Character* Enemy = Cast<AEnemy1Character>(AIC->GetPawn()))
            {
                if (AActor* Player = Cast<AActor>(PlayerObject))
                {
                    //状態更新
                    FVector EnemyVector = Player->GetActorLocation() - Enemy->GetActorLocation();
                    FVector Normalize = EnemyVector / EnemyVector.Length();
                    Normalize = { Normalize.X, Normalize.Y, 0. };
                    Enemy->SetVector(Normalize);
                    Enemy->SetIsMoving(true);
                    Enemy->AttackState = 0;

                  
                    //回転終了
                    if (!Enemy->GetPolygonRotationManager()->GetIsRotating())
                    {
                        //サウンド
                        if (SoundToPlay)
                        {
                            FVector PlayLocation = Enemy->GetActorLocation() + SoundLocationOffset;
                            UGameplayStatics::PlaySoundAtLocation(
                                Enemy->GetWorld(),
                                SoundToPlay,
                                PlayLocation,
                                VolumeMultiplier,
                                PitchMultiplier
                            );
                        }
                        //プレイヤーの距離を見て次の状態へ行くか判断
                        if (EnemyVector.Length() < 500)
                        {
                            FTimerHandle TimerHandle;
                            GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
                                {
                                    if (!IsValid(this))
                                    {
                                        return;
                                    }
                                    IsNextState = true;
                                }, 3.f, false);  // 3秒後に無効化
                        }
                    }

                    //次の状態へ
                    if (IsNextState && !Enemy->GetPolygonRotationManager()->GetIsRotating())
                    {
                        Enemy->SetIsMoving(false);
                        AIC->SetState(3);
                        FRandomStream r;
                        r.GenerateNewSeed();
                        AIC->SetNextState(r.RandRange(1, 2));
                        IsNextState = false;
                        IsInit = false;
                    }
                    

                    return EBTNodeResult::Succeeded;
 
                }
            }
        }

    }
    else
    {
        // `Target` が設定されていない場合の処理

    }

    // タスク実行後、`Target` に新しい値を設定する例
   // BlackboardComp->SetValueAsObject(GetSelectedBlackboardKey(), nullptr); // 例として `null` に設定

    return EBTNodeResult::Failed;
}

void UBTT_MoveCube::Init()
{
    IsNextState = false;

    IsInit = true;
}
