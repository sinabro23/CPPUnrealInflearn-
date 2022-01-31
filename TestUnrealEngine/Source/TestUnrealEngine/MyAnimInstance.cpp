// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	// Super는 이 클래스의 부모클래스 GENERATED_BODY()에 포함돼있는 기능
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner(); // 폰 추출 / 나를 포함하고 있는 폰을 가져오겠다 

	if (IsValid(Pawn))
	{
		// GetVelocity은 폰이 기본적으로 들고있는 함수.
		Speed = Pawn->GetVelocity().Size();

		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsFalling = Character->GetMovementComponent()->IsFalling();
		}
	}
}
