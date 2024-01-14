// Fill out your copyright notice in the Description page of Project Settings.

#include "MultiplayPlayerController.h"
#include "MultiplayGameMode.h"
#include "MultiplayGameState.h"
#include "MultiplayPlayerState.h"
#include "MultiplayClientEvent.h"
#include "MultiplayServerEvent.h"

#include "Kismet/GameplayStatics.h"

void AMultiplayPlayerController::BeginPlay()
{
    Super::BeginPlay();
    if (GetNetMode() == ENetMode::NM_Client)
        return;

	SyncedGameState = GetWorld()->GetGameState<AMultiplayGameState>();
}
	
void AMultiplayPlayerController::GameStateBegin_Implementation(AMultiplayGameState* MultiplayGameState)
{
    SyncedGameState = MultiplayGameState;
}

void AMultiplayPlayerController::LocalPlayerStateBegin_Implementation(AMultiplayPlayerState* MultiplayPlayerState)
{
    SyncedPlayerStates.Add(MultiplayPlayerState);
    ServerRPCOnPlayerStatesUpdate(SyncedPlayerStates);
}

void AMultiplayPlayerController::LocalPlayerStateDestroyed_Implementation(AMultiplayPlayerState* MultiplayPlayerState)
{
    SyncedPlayerStates.Remove(MultiplayPlayerState);
    ServerRPCOnPlayerStatesUpdate(SyncedPlayerStates);
}

void AMultiplayPlayerController::OtherPlayerStateBegin_Implementation(AMultiplayPlayerState* MultiplayPlayerState)
{
    SyncedPlayerStates.Add(MultiplayPlayerState);
    ServerRPCOnPlayerStatesUpdate(SyncedPlayerStates);
}

void AMultiplayPlayerController::OtherPlayerStateDestroyed_Implementation(AMultiplayPlayerState* MultiplayPlayerState)
{
    SyncedPlayerStates.Remove(MultiplayPlayerState);
    ServerRPCOnPlayerStatesUpdate(SyncedPlayerStates);
}

bool AMultiplayPlayerController::ServerRPCOnPlayerStatesUpdate_Validate(const TArray<AMultiplayPlayerState*>& States)
{
    return true;
}

void AMultiplayPlayerController::ServerRPCOnPlayerStatesUpdate_Implementation(const TArray<AMultiplayPlayerState*>& States)
{
    SyncedPlayerStates = States;
    TArray<AActor*> foundActors;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMultiplayServerEvent::StaticClass(), foundActors);
    for(AActor* actor : foundActors)
    {
        IMultiplayServerEvent::Execute_PlayerStateUpdate(actor, this);
    }
}

bool AMultiplayPlayerController::HasAllSyncedPlayerStates()
{
    if(SyncedPlayerStates.Num() != SyncedGameState->PlayerArray.Num())
    {
        UE_LOG(LogTemp, 
               Log, 
               TEXT("AMultiplayPlayerController::HasAllSyncedPlayerStates - SyncedPlayerStates.Num %d, SyncedgameState->PlayerArray.Num %d"), 
               SyncedPlayerStates.Num(), 
               SyncedGameState->PlayerArray.Num()
        );
        return false;
    }

    for(AMultiplayPlayerState* syncedPlayerState : SyncedPlayerStates)
    {
        bool hasSameInstance = false;
        for(APlayerState* playerStateOnServer : SyncedGameState->PlayerArray)
        {
            if(syncedPlayerState == playerStateOnServer)
            {
                hasSameInstance = true;
                break;
            }
        }
        if(!hasSameInstance)
        {
            UE_LOG(LogTemp, Log, TEXT("AMultiplayPlayerController::HasAllSyncedPlayerStates - PlayerState are not synced"));
            return false;
        }
    }
    return true;
}
