// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_3P_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyController();
	virtual void OnPossess(APawn* InPawn) override;

private:
	// Blackboard component for the AI Enemy class
	UPROPERTY(BlueprintReadWrite, Category = "AI Behaviour", meta = (AllowPrivateAccess = "true"))
	class UBlackboardComponent* BlackboardComponent;

	// Behaviour Tree component for the AI Enemy class
	UPROPERTY(BlueprintReadWrite, Category = "AI Behaviour", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviorTreeComponent;

public:
	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComponent; }
	
};
