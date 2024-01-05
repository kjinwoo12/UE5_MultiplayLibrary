// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayGameState.h"
#include "MultiplayPlayerController.h"

void AMultiplayGameState::BeginPlay()
{
    if(GetNetMode() != ENetMode::NM_Client)
    {
        //Server
        return;
    }

    AMultiplayPlayerController* localPlayerController = GetWorld()->GetFirstPlayerController<AMultiplayPlayerController>();
    if (!IsValid(localPlayerController))
        return;

    localPlayerController->OnGameStateBegin(this);
    
}