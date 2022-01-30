// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

// cpp�� c#ó�� reflection�� ������ (reflection�� �����Ϸ��� ������ �ִ� �ּ��̶� ���� �ȴ�.)

UCLASS() // �𸮾��� ����� ���� reflection���. UCLASS()�� �𸮾� Ŭ�����ٶ�� �� �˷��ִ°�./
class TESTUNREALENGINE_API AMyActor : public AActor // ���͸� ��ӹ��� 
{
	// AActor AActor�� ��ӹ޴� ���̴� �̸��տ� A�� ���̴°� ���̹� ��������. ex) AMyActor

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
	// VisibleAnywhere : �� �����Ͱ� ����Ű�� ������� �ܺο��� �����ְ� ��������
	//					 �̷��� �ؾ� ����� ���� ������ ����ƽ�޽� ������Ʈ�� ���ڵ� ���氡��
	UPROPERTY(VisibleAnywhere) 
	UStaticMeshComponent* Mesh; // �𸮾����� �⺻ �������� ��������� �빮�� ����, // #include "CoreMinimal.h"����
	// ����� ���� �����̸� ���۸��ؼ� ������� ��ġ ã����.

	// UStaticMeshComponent�� ����ƽ�޽��� �����ִ� �ϳ��� ū Ʋ.?

	//int32 HP; // �̷������θ� �����ϸ� ���� ������ ���� ���� ����
	//int32 MP;
	UPROPERTY(EditAnywhere, Category = BattleStat) // Category=BattleStat ���� �ߴ� ī�װ�
	int32 HP;
	UPROPERTY(EditAnywhere, Category = BattleStat)
	int32 MP;

	UPROPERTY(EditAnywhere, Category = BattleStat)
	float RotateSpeed = 30.f;
};
