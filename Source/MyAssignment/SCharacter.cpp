// Fill out your copyright notice in the Description page of Project Settings.

#include "SCharacter.h"

#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("Spring Arm Component");
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComp->SetupAttachment(SpringArmComp);

	SpringArmComp->bUsePawnControlRotation = true;//Spring Arm Component
	GetCharacterMovement()->bOrientRotationToMovement = true;//Character Movement Component, lets the mouse turn the body to look in direction without moving it
	bUseControllerRotationYaw = false;//Pawn Class below the actor class

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;
	AddMovementInput(ControlRotation.Vector(),Value);
}

void ASCharacter::MoveRight(float Value)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;
	FVector RightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector,Value);
}
 void ASCharacter::Jump(float Value)
{
	
	float ret =1.f;
	//return ret;
	UE_LOG(LogTemp, Warning, TEXT("Jump"));
}

void ASCharacter::StopJump(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Stop Jump"));
}

void ASCharacter::PrimaryAttack(float Value)
{
	
	UE_LOG(LogTemp, Warning, TEXT("Primary Attack"));
}


// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Moveright", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);//Bind Action
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASCharacter::StopJump);//Bind Action
}

