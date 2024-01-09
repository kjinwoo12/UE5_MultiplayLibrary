// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MultiplayGameState.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYLIBRARY_API AMultiplayGameState : public AGameStateBase
{
	GENERATED_BODY()

	void BeginPlay() override;

public:
	// Default 2.
	UPROPERTY(BlueprintReadWrite)
	int MaxPlayer=2;
};
