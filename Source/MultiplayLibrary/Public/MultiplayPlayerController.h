// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MultiplayClientEventListener.h"
#include "MultiplayPlayerController.generated.h"

/**
 * 
 */
class AMultiplayGameState;
class AMultiplayPlayerState;
class AMultiplayGameMode;

UCLASS()
class MULTIPLAYLIBRARY_API AMultiplayPlayerController : public APlayerController, public IMultiplayClientEventListener
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int PlayerStateNum = 0;

public:
	UPROPERTY(BlueprintReadOnly)
	AMultiplayGameState* SyncedGameState;

	//Work for only client
	UPROPERTY(BlueprintReadOnly)
	TArray<AMultiplayPlayerState*> SyncedPlayerStates;

	void BeginPlay() override;

	void GameStateBegin_Implementation(AMultiplayGameState* MultiplayGameState) override;

	void LocalPlayerStateBegin_Implementation(AMultiplayPlayerState* MultiplayPlayerState) override;

	void LocalPlayerStateDestroyed_Implementation(AMultiplayPlayerState* MultiplayPlayerState) override;

	void OtherPlayerStateBegin_Implementation(AMultiplayPlayerState* MultiplayPlayerState) override;

	void OtherPlayerStateDestroyed_Implementation(AMultiplayPlayerState* MultiplayPlayerState) override;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRPCOnPlayerStatesUpdate(const TArray<AMultiplayPlayerState*>& States);

	bool HasAllSyncedPlayerStates();
};
