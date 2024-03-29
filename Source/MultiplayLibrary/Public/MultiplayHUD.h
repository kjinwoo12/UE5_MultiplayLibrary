// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MultiplayClientEvent.h"
#include "MultiplayHUD.generated.h"

/**
 *
 */
UCLASS()
class MULTIPLAYLIBRARY_API AMultiplayHUD : public AHUD, public IMultiplayClientEvent
{
	GENERATED_BODY()

public:
	void GameStateBegin_Implementation(AMultiplayGameState* MultiplayGameState) override;

	void LocalPlayerStateBegin_Implementation(AMultiplayPlayerState* MultiplayPlayerState) override;

	void LocalPlayerStateDestroyed_Implementation(AMultiplayPlayerState* MultiplayPlayerState) override;

	void OtherPlayerStateBegin_Implementation(AMultiplayPlayerState* MultiplayPlayerState) override;

	void OtherPlayerStateDestroyed_Implementation(AMultiplayPlayerState* MultiplayPlayerState) override;
};
