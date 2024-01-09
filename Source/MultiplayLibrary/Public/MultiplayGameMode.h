// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MultiplayServerEvent.h"
#include "MultiplayGameMode.generated.h"

class AMultiplayPlayerController;

/**
 *
 */
UCLASS()
class MULTIPLAYLIBRARY_API AMultiplayGameMode : public AGameModeBase, public IMultiplayServerEvent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<AMultiplayPlayerController*> ReadyPlayers;

public:
	void PreLogin(const FString& Options,
				  const FString& Address,
				  const FUniqueNetIdRepl& UniqueId,
				  FString& ErrorMessage) override;

	void Logout(AController* Exiting) override;

	void PlayerStateUpdate_Implementation(AMultiplayPlayerController* PlayerController) override;

	// CurrentPlayer Num >= MaxPlayer
	// It follows variable "int MaxPlayer"
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsGameFullOfPlayers();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsAllPlayersSynced();
};
