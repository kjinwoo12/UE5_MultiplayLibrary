// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayGameState.h"
#include "MultiplayPlayerController.h"
#include "MultiplayClientEvent.h"

#include "Kismet/GameplayStatics.h"

void AMultiplayGameState::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Log, TEXT("AMultiplayGameState::BeginPlay"));
    if(GetNetMode() != ENetMode::NM_Client)
    {
        //Server
        return;
    }

    TArray<AActor*> foundActors;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMultiplayClientEvent::StaticClass(), foundActors);
    for(AActor* actor : foundActors)
    {
        IMultiplayClientEvent::Execute_GameStateBegin(actor, this);
    }
}