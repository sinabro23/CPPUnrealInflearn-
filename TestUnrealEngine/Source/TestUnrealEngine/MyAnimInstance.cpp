// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UMyAnimInstance::UMyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/Animations/Greystone_Skeleton_Montage.Greystone_Skeleton_Montage'"));
	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}
}

// ��ƽ���� �����Լ�
void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	// Super�� �� Ŭ������ �θ�Ŭ���� GENERATED_BODY()�� ���Ե��ִ� ���
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner(); // �� ���� / ���� �����ϰ� �ִ� ���� �������ڴ� 

	if (IsValid(Pawn))
	{
		// GetVelocity�� ���� �⺻������ ����ִ� �Լ�.
		Speed = Pawn->GetVelocity().Size();

		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsFalling = Character->GetMovementComponent()->IsFalling();
		}
	}
}

// Ŭ���ϴ� ������ ����ǰ�
void UMyAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.f);
	}
}
