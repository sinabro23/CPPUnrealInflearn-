// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

// cpp는 c#처럼 reflection이 없었음 (reflection은 컴파일러가 읽을수 있는 주석이라 보면 된다.)

UCLASS() // 언리얼이 만들어 놓은 reflection기능. UCLASS()는 언리얼 클래스다라는 걸 알려주는것./
class TESTUNREALENGINE_API AMyActor : public AActor // 엑터를 상속받음 
{
	// AActor AActor를 상속받는 아이는 이름앞에 A를 붙이는게 네이밍 컨벤션임. ex) AMyActor

	GENERATED_BODY() 
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	// VisibleAnywhere : 이 포인터가 가리키는 멤버들을 외부에서 볼수있고 수정가능
	//					 이렇게 해야 만들어 놨던 액터의 스태틱메쉬 컴포넌트의 인자들 변경가능
	UPROPERTY(VisibleAnywhere) 
	UStaticMeshComponent* Mesh; // 언리얼엔진의 기본 컨벤션이 멤버변수가 대문자 시작, // #include "CoreMinimal.h"때문
	// 헤더가 없는 버전이면 구글링해서 헤더파일 위치 찾을것.

	// UStaticMeshComponent는 스태틱메쉬를 보여주는 하나의 큰 틀.?

	//int32 HP; // 이런식으로만 설정하면 툴에 변수가 노출 되지 않음
	//int32 MP;
	UPROPERTY(EditAnywhere, Category = BattleStat) // Category=BattleStat 툴상에 뜨는 카테고리
	int32 HP;
	UPROPERTY(EditAnywhere, Category = BattleStat)
	int32 MP;

	UPROPERTY(EditAnywhere, Category = BattleStat)
	float RotateSpeed = 30.f;
};
