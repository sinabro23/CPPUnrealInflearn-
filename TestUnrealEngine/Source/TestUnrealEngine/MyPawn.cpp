// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "GameFramework/FloatingPawnMovement.h"


// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH")); // ������ ����Ʈ �����͸� ����Ѱ� NEW DELETE�ʿ� ����.
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));

	RootComponent = Mesh; // ������Ʈ�� �ϳ��� ��Ʈ������Ʈ�� �����ؾ���.

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Couch.SM_Couch'"));

	if (SM.Succeeded())
	{
		Mesh->SetStaticMesh(SM.Object); // ������ �ε��� ���ҽ��� �������� ����ƽ�޽�������Ʈ�� ����ƽ�޽��� �ִ´�.
	}

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// �𸮾󿡼��� ��ǲ���� Tick���� ���� �ʰ� ���� ����ȭ �� ����
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//PlayerInputComponent->BindAction(); ���̽�ƽ�� ��ư(��ư�� �������� �ȴ�������) 
	//PlayerInputComponent->BindAxis(); ���̽�ƽ�� ��ƽ(�󸶸�ŭ �а� ������ ���� ���̵� ����)
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyPawn::LeftRight);
	// �׳� �̷��� �Լ��� �����Ѵٰ� �Ǵ°� �ƴ϶� ������ ������Ʈ����->�Է¿��� �����ؾ���
	// ����ο��� �̸��� �����Ҷ� "UpDown", "LeftRight" �̸��� �������

	


}

void AMyPawn::UpDown(float Value)
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

void AMyPawn::LeftRight(float Value)
{
	if (Value == 0.f)
		return;

	//UE_LOG(LogTemp, Warning, TEXT("LeftRight %f"), Value) // Printf ���� ��

	AddMovementInput(GetActorRightVector(), Value);
}

