// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletHitInterface.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class SHOOTER_3P_API AEnemy : public ACharacter, public IBulletHitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void ShowHealthBar();
	void ShowHealthBar_Implementation();

	UFUNCTION(BlueprintImplementableEvent)
	void HideHealthBar();

	void Die();

	void PlayHitMontage(FName Section, float PlayRate = 1.0f);

	void ResetHitReactTimer();

	UFUNCTION(BlueprintCallable)
	void StoreHitNumber(UUserWidget* HitNumber, FVector Location);

	UFUNCTION()
	void DestroyHitNumber(UUserWidget* HitNumber);

	void UpdateHitNumbers();
	
private:
	// Spawn Particles on Enemy when hit by bullets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* ImpactParticles;

	// Sounds played on Enemy when hit by bullets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class USoundCue* ImpactSound;

	// Current Health of the Enemy
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float Health;

	// Maximum Health of the Enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	// Name of the Headbone, for the HeadShotDamage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	FString HeadBone;

	// Time to display/hide the Enemy HealthBar since shot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float HealthBarDisplayTime;
	
	FTimerHandle HealthBarTimer;

	// Montage for Enemy Hit and Death animations
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* HitMontage;

	FTimerHandle HitReactTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float HitReactTimeMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float HitReactTimeMax;

	bool bCanHitReact;

	// Storing HitNumbers, HitLocations and Widgets in TMap
	UPROPERTY(VisibleAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TMap<UUserWidget*, FVector> HitNumbers;

	// Time to remove HitNumbers from the viewport
	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float HitNumberDestroyTime;

	// Behaviour tree for the AI Character
	UPROPERTY(EditAnywhere, Category = "Behaviour Tree", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;

	// Point for the AI Enemy to move to (patrol)
	UPROPERTY(EditAnywhere, Category = "Behaviour Tree", meta = (AllowPrivateAccess = "true", MakeEditWidget = "true"))
	FVector PatrolPoint;

	class AEnemyController* EnemyController;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BulletHit_Implementation(FHitResult HitResult) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	FORCEINLINE FString GetHeadBone() const { return HeadBone; }
	FORCEINLINE UBehaviorTree* GetBehaviourTree() const { return BehaviorTree; }

	UFUNCTION(BlueprintImplementableEvent)
	void ShowHitNumber(int32 Damage, FVector HitLocation, bool bHeadShot);
};
