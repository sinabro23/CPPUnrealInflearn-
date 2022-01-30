// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class TESTUNREALENGINE_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	// Actor를 생성할때는 없었던 함수. // 입력을 받아서 움직일때 쓰는 함수
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void UpDown(float Value); // UpDown 입력받았을때 호출할 함수.
	void LeftRight(float Value); // LeftRight 입력받았을때 호출할 함수.
private:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	class UFloatingPawnMovement* Movement; // 움직임을 위한 컴포넌트중 하나(간단한 이동을 제공하는 컴포넌트)
};
