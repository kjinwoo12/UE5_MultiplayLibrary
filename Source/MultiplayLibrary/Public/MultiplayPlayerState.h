// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MultiplayPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYLIBRARY_API AMultiplayPlayerState : public APlayerState
{
	GENERATED_BODY()

	void BeginPlay() override;
	void Destroyed() override;
};
