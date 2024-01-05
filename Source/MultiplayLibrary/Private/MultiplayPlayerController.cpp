// Fill out your copyright notice in the Description page of Project Settings.

#include "MultiplayPlayerController.h"
#include "MultiplayGameMode.h"
#include "MultiplayGameState.h"
#include "MultiplayPlayerState.h"
#include "MultiplayEventListener.h"

#include "Kismet/GameplayStatics.h"

void AMultiplayPlayerController::BeginPlay()
{
    if (GetNetMode() == ENetMode::NM_Client)
        return;

	SyncedGameState = GetWorld()->GetGameState<AMultiplayGameState>();
}
	
void AMultiplayPlayerController::OnGameStateBegin(AMultiplayGameState* MultiplayGameState)
{
    SyncedGameState = MultiplayGameState;
	GameStateBegin(SyncedGameState);

    TArray<AActor*> foundActors;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMultiplayEventListener::StaticClass(), foundActors);
    for(AActor* actor : foundActors)
    {
        IMultiplayEventListener::Execute_GameStateBegin(actor, MultiplayGameState);
    }
}

void AMultiplayPlayerController::GameStateBegin_Implementation(AMultiplayGameState* MultiplayGameState)
{
}

void AMultiplayPlayerController::OnLocalPlayerStateBegin(AMultiplayPlayerState* MultiplayPlayerState)
{
    SyncedPlayerStates.Add(MultiplayPlayerState);
	LocalPlayerStateBegin(MultiplayPlayerState);

    TArray<AActor*> foundActors;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMultiplayEventListener::StaticClass(), foundActors);
    for (AActor* actor : foundActors)
    {
        IMultiplayEventListener::Execute_LocalPlayerStateBegin(actor, MultiplayPlayerState);
    }

    PlayerStateBegin(MultiplayPlayerState);
}

void AMultiplayPlayerController::LocalPlayerStateBegin_Implementation(AMultiplayPlayerState* MultiplayPlayerState)
{
}

void AMultiplayPlayerController::OnOtherPlayerStateBegin(AMultiplayPlayerState* MultiplayPlayerState)
{
    SyncedPlayerStates.Add(MultiplayPlayerState);
	OtherPlayerStateBegin(MultiplayPlayerState);

    TArray<AActor*> foundActors;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMultiplayEventListener::StaticClass(), foundActors);
    for (AActor* actor : foundActors)
    {
        IMultiplayEventListener::Execute_OtherPlayerStateBegin(actor, MultiplayPlayerState);
    }

    PlayerStateBegin(MultiplayPlayerState);
}

void AMultiplayPlayerController::OtherPlayerStateBegin_Implementation(AMultiplayPlayerState* MultiplayPlayerState)
{
}

void AMultiplayPlayerController::PlayerStateBegin_Implementation(AMultiplayPlayerState* MultiplayPlayerState)
{
}

void AMultiplayPlayerController::OnPlayerStateDestroyed(AMultiplayPlayerState* Destroyed)
{
    SyncedPlayerStates.Remove(Destroyed);
}