// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "GameFramework/FloatingPawnMovement.h"


// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH")); // 일종의 스마트 포인터를 사용한격 NEW DELETE필요 없다.
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));

	RootComponent = Mesh; // 컴포넌트중 하나를 루트컴포넌트로 설정해야함.

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Couch.SM_Couch'"));

	if (SM.Succeeded())
	{
		Mesh->SetStaticMesh(SM.Object); // 위에서 로드한 리소스를 내가만든 스태틱메쉬컴포넌트에 스태틱메쉬로 넣는다.
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
	// 언리얼에서는 인풋값을 Tick에서 받지 않고 따로 구조화 해 뒀음
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//PlayerInputComponent->BindAction(); 조이스틱의 버튼(버튼을 눌렀는지 안눌렀는지) 
	//PlayerInputComponent->BindAxis(); 조이스틱의 스틱(얼마만큼 밀고 당기느냐 정도 차이도 생김)
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyPawn::LeftRight);
	// 그냥 이렇게 함수만 설정한다고 되는게 아니라 툴에서 프로젝트세팅->입력에서 설정해야함
	// 축매핑에서 이름을 설정할때 "UpDown", "LeftRight" 이름은 맞춰야함

	


}

void AMyPawn::UpDown(float Value)
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

void AMyPawn::LeftRight(float Value)
{
	if (Value == 0.f)
		return;

	//UE_LOG(LogTemp, Warning, TEXT("LeftRight %f"), Value) // Printf 같은 것

	AddMovementInput(GetActorRightVector(), Value);
}

