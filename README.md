# MultiplayLibrary
Have you ever got any situations about invalid `GameState` or `PlayerState` when you make your multiplay game? USE IT!

# How to use
1. Make sure the parent class of your Blueprint or C++ class is `Multiplay~`.
  - `MultiplayGameMode`
  - `MultiplayGameState`
  - `MultiplayPlayerController`
  - `MultiplayPlayerState`
  - `MultiplayHUD` : Optional, if you need to use Interface for Widgets.
2. You can use `AMultiplayGameMode::IsAllPlayersSynced()`. The function is going to return about that have all clients the valid PlayerStates in the GameMode::PlayerArray or not.
3. There are two interfaces for client-side event and server-side event. If you need 

## example
Simple Code
```C++
class MYGAME_API AMyGameMode : public AMultiplayGameMode
{
	GENERATED_BODY()
	
public:
	void PlayerStateUpdate_Implementation(AMultiplayPlayerController* PlayerController) override;

	UFUNCTION(BlueprintNativeEvent)
	void AllPlayersReady();
};

void AMyGameMode::PlayerStateUpdate_Implementation(AMultiplayPlayerController* PlayerController)
{
	Super::PlayerStateUpdate_Implementation(PlayerController);

	UE_LOG(LogTemp, Log, TEXT("AMyGameMode::PlayerStateUpdate"));

	if(!IsGameFullOfPlayers())
	{
		UE_LOG(LogTemp, Log, TEXT("AMyGameMode::PlayerStateUpdate - Players are not full"));
		return;
	}

	if(!IsAllPlayersSynced())
	{
		UE_LOG(LogTemp, Log, TEXT("AMyGameMode::PlayerStateUpdate - Players are not syncronized"));
		return;
	}

	AllPlayersReady();
}
```
Repository that use this library - [Link](https://github.com/kjinwoo12/UE5Game_LeagueOfWatch)
