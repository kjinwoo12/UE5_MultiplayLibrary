// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayHUD.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void AMultiplayHUD::GameStateBegin_Implementation(AMultiplayGameState* MultiplayGameState)
{
	TArray<UUserWidget*> foundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), foundWidgets, UMultiplayClientEventListener::StaticClass(), true);
	for(UUserWidget* widget : foundWidgets)
	{
		IMultiplayClientEventListener::Execute_GameStateBegin(widget, MultiplayGameState);
	}
}

void AMultiplayHUD::LocalPlayerStateBegin_Implementation(AMultiplayPlayerState* MultiplayPlayerState)
{
	TArray<UUserWidget*> foundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), foundWidgets, UMultiplayClientEventListener::StaticClass(), true);
	for (UUserWidget* widget : foundWidgets)
	{
		IMultiplayClientEventListener::Execute_LocalPlayerStateBegin(widget, MultiplayPlayerState);
	}
}


void AMultiplayHUD::LocalPlayerStateDestroyed_Implementation(AMultiplayPlayerState* MultiplayPlayerState)
{
	TArray<UUserWidget*> foundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), foundWidgets, UMultiplayClientEventListener::StaticClass(), true);
	for(UUserWidget* widget : foundWidgets)
	{
		IMultiplayClientEventListener::Execute_LocalPlayerStateDestroyed(widget, MultiplayPlayerState);
	}
}

void AMultiplayHUD::OtherPlayerStateBegin_Implementation(AMultiplayPlayerState* MultiplayPlayerState)
{
	TArray<UUserWidget*> foundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), foundWidgets, UMultiplayClientEventListener::StaticClass(), true);
	for (UUserWidget* widget : foundWidgets)
	{
		IMultiplayClientEventListener::Execute_OtherPlayerStateBegin(widget, MultiplayPlayerState);
	}
}

void AMultiplayHUD::OtherPlayerStateDestroyed_Implementation(AMultiplayPlayerState* MultiplayPlayerState)
{
	TArray<UUserWidget*> foundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), foundWidgets, UMultiplayClientEventListener::StaticClass(), true);
	for(UUserWidget* widget : foundWidgets)
	{
		IMultiplayClientEventListener::Execute_OtherPlayerStateDestroyed(widget, MultiplayPlayerState);
	}
}