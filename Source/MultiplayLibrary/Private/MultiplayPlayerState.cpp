// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayPlayerState.h"
#include "MultiplayPlayerController.h"
#include "MultiplayClientEventListener.h"

#include "Kismet/GameplayStatics.h"

void AMultiplayPlayerState::BeginPlay()
{
    if(GetNetMode() != ENetMode::NM_Client)
    {
        //Server
        return;
    }

    AMultiplayPlayerController* localPlayerController = Cast<AMultiplayPlayerController>(GetOwner());
    TArray<AActor*> foundActors;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMultiplayClientEventListener::StaticClass(), foundActors);
    if (IsValid(localPlayerController))
    {
        for(AActor* actor : foundActors)
        {
            IMultiplayClientEventListener::Execute_LocalPlayerStateBegin(actor, this);
        }
    }
    else
    {
        for(AActor* actor : foundActors)
        {
            IMultiplayClientEventListener::Execute_OtherPlayerStateBegin(actor, this);
        }
    }
}

void AMultiplayPlayerState::Destroyed()
{
    AMultiplayPlayerController* localPlayerController = Cast<AMultiplayPlayerController>(GetOwner());
    TArray<AActor*> foundActors;
    if(IsValid(localPlayerController))
    {
        for(AActor* actor : foundActors)
        {
            IMultiplayClientEventListener::Execute_LocalPlayerStateDestroyed(actor, this);
        }
    }
    else
    {
        for(AActor* actor : foundActors)
        {
            IMultiplayClientEventListener::Execute_OtherPlayerStateDestroyed(actor, this);
        }
    }
}