// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "MyAnimInstance.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	//������Ʈ������ �θ� ������ �ϴ� �� �ٿ������, ĸ��������Ʈ�� ��ǻ� ��Ʈ������Ʈ�̱� ������ ĸ���� ����
	SpringArm->SetupAttachment(GetCapsuleComponent()); 
	Camera->SetupAttachment(SpringArm); // ī�޶�� �������Ͽ� ����

	SpringArm->TargetArmLength = 500.f;// ��ī���� ����
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));

	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f)); // �޽��� �⺻��ġ�� ���� ���꼼��

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackMontageEnded);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &AMyCharacter::Yaw);

	// ������ ���� �Լ��� �������� �ʾƵ���. // ������ ACharacterŬ���� �ȿ� �̸� ���� �� ����
	PlayerInputComponent->BindAction(TEXT("JUMP"), EInputEvent::IE_Pressed, this, &AMyCharacter::Jump);

	// attack���� ���ε��� ���콺 ������ ������ Attack�̶� �Լ��� ������ �ǰ� �ϴ°�.
	PlayerInputComponent->BindAction(TEXT("ATTACK"), EInputEvent::IE_Pressed, this, &AMyCharacter::Attack);
}


void AMyCharacter::UpDown(float Value)
{
	// ������ ������Ʈ���ÿ��� �Է��� �����ϰ��� Value�� �Ѿ��

	if (Value == 0.f)
		return;

	//UE_LOG(LogTemp, Warning, TEXT("UpDown %f"), Value) // Printf ���� ��

	// transform�� �������ٵ� ���� ���⼭ �ٷ� transform������ �ϸ� ������������ ����
	// ������� ������ �̵��Ѵٴ��� �꿡�� �̵��Ѵ��Ҷ��� �޶����ٵ� ������ ����
	// �׷��� �̵��� ���õȰ͵� �ϳ��� ������Ʈ�� ���� ������

	AddMovementInput(GetActorForwardVector(), Value);
}

void AMyCharacter::LeftRight(float Value)
{
	if (Value == 0.f)
		return;

	//UE_LOG(LogTemp, Warning, TEXT("LeftRight %f"), Value) // Printf ���� ��

	AddMovementInput(GetActorRightVector(), Value);
}

void AMyCharacter::Yaw(float Value)
{
	// �������� UseController Rotation Yaw�� true�� üũ ���ֱ� ������ ��밡��
	AddControllerYawInput(Value); // ī�޶� ���콺 �����Ӷ����� �߰��� �Լ�. 
	// ĳ���Ϳ� ����Ǵ� �Լ����ƴ϶� ��Ʈ�ѷ��� �����
}

void AMyCharacter::Attack()
{
	if (IsAttacking)
		return;

	AnimInstance->PlayAttackMontage();
	
	IsAttacking = true;
}

void AMyCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
}
