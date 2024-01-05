// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayGameMode.h"
#include "MultiplayGameState.h"
#include "MultiplayPlayerController.h"
#include "MultiplayPlayerState.h"


AMultiplayGameMode::AMultiplayGameMode()
{
    GameStateClass = AMultiplayGameState::StaticClass();
    PlayerControllerClass = AMultiplayPlayerController::StaticClass();
    PlayerStateClass = AMultiplayPlayerState::StaticClass();
}

void AMultiplayGameMode::PreLogin(const FString& Options,
                                           const FString& Address,
                                           const FUniqueNetIdRepl& UniqueId,
                                           FString& ErrorMessage)
{
    if (IsGameFullOfPlayers())
    {
        ErrorMessage = "The Game is full of players.";
        return;
    }
}

void AMultiplayGameMode::OnPlayerReady(AMultiplayPlayerController* MultiplayPlayerController)
{
	ReadyPlayers.Add(MultiplayPlayerController);
	PlayerReady(MultiplayPlayerController);
}

void AMultiplayGameMode::PlayerReady_Implementation(AMultiplayPlayerController* MultiplayPlayerController)
{
}

void AMultiplayGameMode::Logout(AController * Exiting)
{
    AMultiplayPlayerController* multiplayPlayerController = Cast<AMultiplayPlayerController>(Exiting);
    if(IsValid(multiplayPlayerController))
    {
        ReadyPlayers.Remove(multiplayPlayerController);
    }

    Super::Logout(Exiting);
}

bool AMultiplayGameMode::IsGameFullOfPlayers()
{
    AMultiplayGameState* multiplayGameState = GetGameState<AMultiplayGameState>();
    if(IsValid(multiplayGameState))
        return GetNumPlayers() >= multiplayGameState->MaxPlayer;
    else
        return false;
}