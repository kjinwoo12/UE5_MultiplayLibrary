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

void AMultiplayGameMode::Logout(AController * Exiting)
{
    AMultiplayPlayerController* multiplayPlayerController = Cast<AMultiplayPlayerController>(Exiting);
    if(IsValid(multiplayPlayerController))
    {
        ReadyPlayers.Remove(multiplayPlayerController);
    }

    Super::Logout(Exiting);
}

void AMultiplayGameMode::PlayerStateUpdate_Implementation(AMultiplayPlayerController* PlayerController)
{
    if(PlayerController->HasAllSyncedPlayerStates())
    {
        ReadyPlayers.Add(PlayerController);
    }
    else
    {
        ReadyPlayers.Remove(PlayerController);
    }
}

bool AMultiplayGameMode::IsGameFullOfPlayers()
{
    AMultiplayGameState* multiplayGameState = GetGameState<AMultiplayGameState>();
    if(IsValid(multiplayGameState))
        return GetNumPlayers() >= multiplayGameState->MaxPlayer;
    else
        return false;
}


bool AMultiplayGameMode::IsAllPlayersSynced()
{
    AMultiplayGameState* multiplayGameState = GetGameState<AMultiplayGameState>();
    if(IsValid(multiplayGameState))
        return false;

    for(APlayerState* readyPlayerState : multiplayGameState->PlayerArray)
    {
        AMultiplayPlayerController* readyPlayer = Cast<AMultiplayPlayerController>(readyPlayerState->GetOwner());
        if(!IsValid(readyPlayer)||!readyPlayer->HasAllSyncedPlayerStates())
            return false;
    }
    return true;
}