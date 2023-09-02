#include "Characters/CCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Utilities/CLog.h"

ACCharacterBase::ACCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// Camera Section
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 900.0f;
	SpringArm->SocketOffset = FVector(0, 0, 400);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->SetRelativeRotation(FRotator(-20, 0, 0));
	Camera->bUsePawnControlRotation = false;

	// Character Movement Section
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;
}

void ACCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Input Mapping Context Setting
	if (!DefaultMappingContext)
	{
		PrintLine();
		UE_LOG(Caiman, Error, TEXT("DefaultMappingContext is Null"));
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	// Input Action Setting
	if (MoveAction)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACCharacterBase::OnMove);
	}

	if (LookAction)
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACCharacterBase::OnLook);
	}

	if (RunningAction)
	{
		EnhancedInputComponent->BindAction(RunningAction, ETriggerEvent::Triggered, this, &ACCharacterBase::OnRunning);
		EnhancedInputComponent->BindAction(RunningAction, ETriggerEvent::Completed, this, &ACCharacterBase::OffRunning);
	}

	if (JumpAction)
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACCharacterBase::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACCharacterBase::StopJumping);
	}

	if (DashAction)
	{
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &ACCharacterBase::OnDash);
	}
}

void ACCharacterBase::OnMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void ACCharacterBase::OnLook(const FInputActionValue& Value)
{
	FVector2D MouseVector = Value.Get<FVector2D>();

	AddControllerYawInput(MouseVector.X);
	AddControllerPitchInput(MouseVector.Y);
}

bool ACCharacterBase::GetIsRunning()
{
	return bIsRunning;
}

void ACCharacterBase::OnRunning()
{
	bIsRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
}

void ACCharacterBase::OffRunning()
{
	bIsRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
}

void ACCharacterBase::OnDash()
{
	const FVector FwdVector = this->GetActorRotation().Vector();
	const float DashDistance = 3000.0f;

	LaunchCharacter(FwdVector * DashDistance, true, true);

	if (DashMontage)
	{
		UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
		animInstance->Montage_Play(DashMontage);
	}
}
