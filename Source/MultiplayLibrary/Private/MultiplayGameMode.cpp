// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayGameMode.h"
#include "MultiplayGameState.h"
#include "MultiplayPlayerController.h"
#include "MultiplayPlayerState.h"

void AMultiplayGameMode::PreLogin(const FString& Options,
                                  const FString& Address,
                                  const FUniqueNetIdRepl& UniqueId,
                                  FString& ErrorMessage)
{
    Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
    if (IsGameFullOfPlayers())
    {
        ErrorMessage = "The Game is full of players.";
        return;
    }
}

void AMultiplayGameMode::Logout(AController * Exiting)
{
    Super::Logout(Exiting);
    AMultiplayPlayerController* multiplayPlayerController = Cast<AMultiplayPlayerController>(Exiting);
    if(IsValid(multiplayPlayerController))
    {
        ReadyPlayers.Remove(multiplayPlayerController);
    }
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
    {
        UE_LOG(LogTemp, Log, TEXT("AMultiplayGameMode::IsGameFullOfPlayers - GetNumPlayers %d, MaxPlayer %d"), GetNumPlayers(), multiplayGameState->MaxPlayer);
        return GetNumPlayers() >= multiplayGameState->MaxPlayer;
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("AMultiplayGameMode::IsGameFullOfPlayers - multiplayGameState invalid"));
        return false;
    }
}


bool AMultiplayGameMode::IsAllPlayersSynced()
{
    AMultiplayGameState* multiplayGameState = GetGameState<AMultiplayGameState>();
    if(!IsValid(multiplayGameState))
    {
        UE_LOG(LogTemp, Log, TEXT("AMultiplayGameMode::IsAllPlayersSynced - multiplayGameState invalid"));
        return false;
    }

    for(APlayerState* readyPlayerState : multiplayGameState->PlayerArray)
    {
        AMultiplayPlayerController* readyPlayer = Cast<AMultiplayPlayerController>(readyPlayerState->GetOwner());
        if(!IsValid(readyPlayer))
        {
            UE_LOG(LogTemp, Log, TEXT("AMultiplayGameMode::IsAllPlayersSynced - readyPlayer invalid"));
            return false;
        }
        if(!readyPlayer->HasAllSyncedPlayerStates())
        {
            UE_LOG(LogTemp, Log, TEXT("AMultiplayGameMode::IsAllPlayersSynced - readyPlayer is not synced"));
            return false;
        }
    }
    return true;
}