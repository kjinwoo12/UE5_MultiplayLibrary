// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayPlayerState.h"
#include "MultiplayPlayerController.h"
#include "MultiplayClientEvent.h"

#include "Kismet/GameplayStatics.h"

void AMultiplayPlayerState::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("AMultiplayPlayerState::BeginPlay()"));
    if(GetNetMode() != ENetMode::NM_Client)
    {
        //Server
        UE_LOG(LogTemp, Log, TEXT("AMultiplayPlayerState::BeginPlay - Do nothing."));
        return;
    }
    AMultiplayPlayerController* localPlayerController = Cast<AMultiplayPlayerController>(GetOwner());
    TArray<AActor*> foundActors;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMultiplayClientEvent::StaticClass(), foundActors);
    if (IsValid(localPlayerController))
    {
        for(AActor* actor : foundActors)
        {
            IMultiplayClientEvent::Execute_LocalPlayerStateBegin(actor, this);
        }
    }
    else
    {
        for(AActor* actor : foundActors)
        {
            IMultiplayClientEvent::Execute_OtherPlayerStateBegin(actor, this);
        }
    }
}

void AMultiplayPlayerState::Destroyed()
{
    Super::Destroyed();
    UE_LOG(LogTemp, Log, TEXT("AMultiplayPlayerState::Destroyed()"));
    if(GetNetMode() != ENetMode::NM_Client)
    {
        //Server
        UE_LOG(LogTemp, Log, TEXT("AMultiplayPlayerState::Destroyed - Do nothing."));
        return;
    }
    AMultiplayPlayerController* localPlayerController = Cast<AMultiplayPlayerController>(GetOwner());
    TArray<AActor*> foundActors;
    if(IsValid(localPlayerController))
    {
        for(AActor* actor : foundActors)
        {
            IMultiplayClientEvent::Execute_LocalPlayerStateDestroyed(actor, this);
        }
    }
    else
    {
        for(AActor* actor : foundActors)
        {
            IMultiplayClientEvent::Execute_OtherPlayerStateDestroyed(actor, this);
        }
    }
}