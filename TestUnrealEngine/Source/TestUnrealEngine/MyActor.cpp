// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
														//TEXT()는 플랫폼에 상관없이 변경해줌
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH")); // 일종의 스마트 포인터를 사용한격 NEW DELETE필요 없다.

	RootComponent = Mesh; // 컴포넌트중 하나를 루트컴포넌트로 설정해야함.

	// 리소스를 로드해서 클래스 자체에 박기위한 과정(툴에서 했으면 객체하나에만 해당됐음)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Couch.SM_Couch'"));
	// 경로 복사할때 그냥 툴 상에서 메쉬를 찾아서 클릭후 복사하면 자동으로 경로복사됨.
	// 스태틱 메쉬를 경로에서 로드했음.

	if (SM.Succeeded())
	{
		Mesh->SetStaticMesh(SM.Object); // 위에서 로드한 리소스를 내가만든 스태틱메쉬컴포넌트에 스태틱메쉬로 넣는다.
	}
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	// 시작

	// 카테고리, 로깅 수준, 형식, 인자
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay %d"), 3) // Printf 같은 것
	// 로깅 수준에 따라 파일에도 로그가 저장되는데 Saved폴더의 Logs폴더에 저장됨.
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Error, TEXT("Tick %f"), DeltaTime);
	AddActorLocalRotation(FRotator(RotateSpeed * DeltaTime, 0.0f, 0.0f));

	//FRotator()인자 Pitch(Y축) Roll(X축) Yaw(Z축) //https://docs.unrealengine.com/4.27/en-US/API/Runtime/Core/Math/FRotator/

}

