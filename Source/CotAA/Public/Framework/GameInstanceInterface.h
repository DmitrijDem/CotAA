// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SavedGameplayInfo.h"
#include "Enums/GameProperties/Enum_GameState.h"
#include "Enums/UI/InGameMenu.h"
#include "UObject/Interface.h"
#include "GameInstanceInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameInstanceInterface : public UInterface
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FGameWidgetsStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* BeginPlay = nullptr;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* MainMenu = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* PauseMenu = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* LoadingScreen = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* InGame = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* InGameMenu = nullptr;
};

/**
 * 
 */
class COTAADEV_API IGameInstanceInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Complete Kit| Game")
	Enum_GameState PassGameState();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Complete Kit| Game")
	bool UpdateGameState (Enum_GameState DesiredGameState);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Complete Kit| Game")
	FGameWidgetsStruct GetGameWidgets();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Complete Kit| Game")
	void StartNewGame(FSavedGameplayInfo GameplayInfo, FName LevelName);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Complete Kit| Game")
	void OnAnyKey(FKey AnyKey);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Complete Kit| Widget Events")
	void DisplayGameWidget(Enum_GameState GameState);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Complete Kit| Widget Events")
	void TogglePauseMenu();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Complete Kit| Widget Events")
	void ToggleInGameMenu(EInGameMenu MenuType);

};
