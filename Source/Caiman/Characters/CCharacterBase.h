#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CCharacterBase.generated.h"

UCLASS()
class CAIMAN_API ACCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACCharacterBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Cameara")
		TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Cameara")
		TObjectPtr<class UCameraComponent> Camera;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> RunningAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> DashAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> LookAction;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation/Dash", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UAnimMontage> DashMontage;


protected:
	void OnMove(const FInputActionValue& Value);
	void OnLook(const FInputActionValue& Value);

	bool bIsRunning = false;
	void OnRunning();
	void OffRunning();

	bool bIsDash = false;
	void OnDash();

public:
	UFUNCTION(BlueprintCallable)
		bool GetIsRunning();
};
