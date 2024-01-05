// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayPlayerState.h"
#include "MultiplayPlayerController.h"

void AMultiplayPlayerState::BeginPlay()
{
    if(GetNetMode() != ENetMode::NM_Client)
    {
        //Server
        return;
    }

    AMultiplayPlayerController* localPlayerController = Cast<AMultiplayPlayerController>(GetOwner());
    if (IsValid(localPlayerController))
    { // if the localPlayerController is the owner of this state, 
        localPlayerController->OnLocalPlayerStateBegin(this);
    }
    else
    {
        localPlayerController = GetWorld()->GetFirstPlayerController<AMultiplayPlayerController>();
        if (!IsValid(localPlayerController))
            return;

        localPlayerController->OnOtherPlayerStateBegin(this);
    }
}

void AMultiplayPlayerState::Destroyed()
{
    AMultiplayPlayerController* localPlayerController = GetWorld()->GetFirstPlayerController<AMultiplayPlayerController>();
    if(!IsValid(localPlayerController))
        return;

    localPlayerController->OnPlayerStateDestroyed(this);
}