// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayGameState.h"
#include "MultiplayPlayerController.h"
#include "MultiplayClientEventListener.h"

#include "Kismet/GameplayStatics.h"

void AMultiplayGameState::BeginPlay()
{
    if(GetNetMode() != ENetMode::NM_Client)
    {
        //Server
        return;
    }

    TArray<AActor*> foundActors;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMultiplayClientEventListener::StaticClass(), foundActors);
    for(AActor* actor : foundActors)
    {
        IMultiplayClientEventListener::Execute_GameStateBegin(actor, this);
    }
}