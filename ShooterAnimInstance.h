// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ShooterAnimInstance.generated.h"


UENUM(BlueprintType)
enum class EOffsetState : uint8
{
	EOS_Aiming UMETA(DisplayName = "Aiming"),
	EOS_Hip UMETA(DisplayName = "Hip"),
	EOS_Reloading UMETA(DisplayName = "Reloading"),
	EOS_InAir UMETA(DisplayName = "InAir"),
	
	EOS_MAX UMETA(DisplayName = "DefaultMAX")
	
};

/**
 * 
 */
UCLASS()
class SHOOTER_3P_API UShooterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

	UShooterAnimInstance();
	
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);

	virtual void NativeInitializeAnimation() override;

protected:
	
	// Handle turning in place variables
	void TurnInPlace();

	// Handle calculations for leaning while running
	void Lean(double Deltatime);
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"));
	class AShooterCharacter* ShooterCharacter;

	// The speed of the Character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "True"));
	float Speed;

	// Check for Character in air or not
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "True"));
	bool bIsInAir;

	// Check for Character is moving
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "True"));
	bool bIsAccelerating;

	// Strafe movement offset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "True"));
	float MovementOffsetYaw;

	// Offset yaw the frame before we stopped moving
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "True"));
	float LastMovementOffsetYaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "True"));
	bool bAiming;

	// Yaw [Turn in place] of the Character this frame; only updating when NOT in air/ standing still
	float TIPCharacterYaw;

	// Yaw [Turn in place] of the Character the previous frame; only updating when NOT in air/ standing still
	float TIPCharacterYawLastFrame;

	// Offset the Yaw in relation to the Root 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn In Place", meta = (AllowPrivateAccess = "true"))
	float RootYawOffset;

	// Rotation curve value this frame
	float RotationCurve;
	// Rotation curve value last frame
	float RotationCurveLastFrame;

	// The pitch of the aim rotation, used for AimOffset
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn In Place", meta = (AllowPrivateAccess = "true"))
	float Pitch;

	// True when reloading, used to prevent AimOffset while reloading
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn In Place", meta = (AllowPrivateAccess = "true"))
	bool bReloading;

	// Offset State; used to determine which Aim Offset to use 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn In Place", meta = (AllowPrivateAccess = "true"))
	EOffsetState OffsetState;

	// Character Yaw this frame
	FRotator CharacterRotation;

	// Character Yaw last frame
	FRotator CharacterRotationLastFrame;

	// Yaw delta used for leaning in the running blendspace
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Leaning", meta = (AllowPrivateAccess = "true"))
	float YawDelta;

	// True when Crouching
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crouching", meta = (AllowPrivateAccess = "true"))
	bool bCrouching;

	// Change the RecoilWeight based on TurnInPlace and Aiming
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float RecoilWeight;

	// True when Equipping
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crouching", meta = (AllowPrivateAccess = "true"))
	bool bEquipping;

	// True if Character is Turning In Place 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool bTurningInPlace;
};