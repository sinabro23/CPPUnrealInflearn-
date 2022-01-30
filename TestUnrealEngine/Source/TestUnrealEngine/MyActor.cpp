// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
														//TEXT()�� �÷����� ������� ��������
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH")); // ������ ����Ʈ �����͸� ����Ѱ� NEW DELETE�ʿ� ����.

	RootComponent = Mesh; // ������Ʈ�� �ϳ��� ��Ʈ������Ʈ�� �����ؾ���.

	// ���ҽ��� �ε��ؼ� Ŭ���� ��ü�� �ڱ����� ����(������ ������ ��ü�ϳ����� �ش����)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Couch.SM_Couch'"));
	// ��� �����Ҷ� �׳� �� �󿡼� �޽��� ã�Ƽ� Ŭ���� �����ϸ� �ڵ����� ��κ����.
	// ����ƽ �޽��� ��ο��� �ε�����.

	if (SM.Succeeded())
	{
		Mesh->SetStaticMesh(SM.Object); // ������ �ε��� ���ҽ��� �������� ����ƽ�޽�������Ʈ�� ����ƽ�޽��� �ִ´�.
	}
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	// ����

	// ī�װ�, �α� ����, ����, ����
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay %d"), 3) // Printf ���� ��
	// �α� ���ؿ� ���� ���Ͽ��� �αװ� ����Ǵµ� Saved������ Logs������ �����.
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Error, TEXT("Tick %f"), DeltaTime);
	AddActorLocalRotation(FRotator(RotateSpeed * DeltaTime, 0.0f, 0.0f));

	//FRotator()���� Pitch(Y��) Roll(X��) Yaw(Z��) //https://docs.unrealengine.com/4.27/en-US/API/Runtime/Core/Math/FRotator/

}

