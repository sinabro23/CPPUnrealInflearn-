// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

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
