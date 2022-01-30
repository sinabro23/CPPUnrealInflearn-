// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	// Super�� �� Ŭ������ �θ�Ŭ���� GENERATED_BODY()�� ���Ե��ִ� ���
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn = TryGetPawnOwner(); // �� ���� / ���� �����ϰ� �ִ� ���� �������ڴ� 

	if (IsValid(pawn))
	{
		// GetVelocity�� ���� �⺻������ ����ִ� �Լ�.
		Speed = pawn->GetVelocity().Size();
	}


}
