// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTUNREALENGINE_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
    // Defulat Pawn : 주인공 설정.
	// 디폴트 폰을 설정하기 위해 생성자를 만들었음.
	AMyGameModeBase();
	
};
