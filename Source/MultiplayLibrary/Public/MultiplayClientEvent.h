// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MultiplayClientEvent.generated.h"

class AMultiplayGameState;
class AMultiplayPlayerState;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMultiplayClientEvent : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MULTIPLAYLIBRARY_API IMultiplayClientEvent
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void GameStateBegin(AMultiplayGameState* MultiplayGameState);

	UFUNCTION(BlueprintNativeEvent)
	void LocalPlayerStateBegin(AMultiplayPlayerState* MultiplayPlayerState);

	UFUNCTION(BlueprintNativeEvent)
	void LocalPlayerStateDestroyed(AMultiplayPlayerState* MultiplayPlayerState);
	
	UFUNCTION(BlueprintNativeEvent)
	void OtherPlayerStateBegin(AMultiplayPlayerState* MultiplayPlayerState);

	UFUNCTION(BlueprintNativeEvent)
	void OtherPlayerStateDestroyed(AMultiplayPlayerState* MultiplayPlayerState);
};
