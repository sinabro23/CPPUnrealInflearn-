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

	//컴포넌트들은은 부모를 누구로 하는 지 붙여줘야함, 캡슐컴포넌트가 사실상 루트컴포넌트이기 때문에 캡슐에 붙임
	SpringArm->SetupAttachment(GetCapsuleComponent()); 
	Camera->SetupAttachment(SpringArm); // 카메라는 스프링암에 붙임

	SpringArm->TargetArmLength = 500.f;// 셀카봉의 길이
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));

	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f)); // 메쉬의 기본위치와 방향 국룰세팅

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

	// 점프는 따로 함수를 구현하지 않아도됨. // 점프는 ACharacter클래스 안에 미리 구현 돼 있음
	PlayerInputComponent->BindAction(TEXT("JUMP"), EInputEvent::IE_Pressed, this, &AMyCharacter::Jump);

	// attack으로 바인딩한 마우스 왼쪽을 누르면 Attack이란 함수가 실행이 되게 하는것.
	PlayerInputComponent->BindAction(TEXT("ATTACK"), EInputEvent::IE_Pressed, this, &AMyCharacter::Attack);
}


void AMyCharacter::UpDown(float Value)
{
	// 툴에서 프로젝트세팅에서 입력한 스케일값이 Value로 넘어옴

	if (Value == 0.f)
		return;

	//UE_LOG(LogTemp, Warning, TEXT("UpDown %f"), Value) // Printf 같은 것

	// transform을 설정할텐데 지금 여기서 바로 transform설정을 하면 유동적이지가 못함
	// 예를들면 물에서 이동한다던지 산에서 이동한다할때는 달라질텐데 설정을 못함
	// 그래서 이동에 관련된것도 하나의 컴포넌트로 따로 빼놨음

	AddMovementInput(GetActorForwardVector(), Value);
}

void AMyCharacter::LeftRight(float Value)
{
	if (Value == 0.f)
		return;

	//UE_LOG(LogTemp, Warning, TEXT("LeftRight %f"), Value) // Printf 같은 것

	AddMovementInput(GetActorRightVector(), Value);
}

void AMyCharacter::Yaw(float Value)
{
	// 디테일의 UseController Rotation Yaw가 true로 체크 돼있기 때문에 사용가능
	AddControllerYawInput(Value); // 카메라 마우스 움직임때문에 추가한 함수. 
	// 캐릭터에 적용되는 함수가아니라 컨트롤러에 적용됨
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
