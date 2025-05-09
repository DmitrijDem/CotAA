// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "Enum_GameState.generated.h"

/**
 * Enum to describe the states of the game - BeginPlay, MainMenu, InGameMenu, LoadinScreen, Playing
 */
UENUM(BlueprintType)
enum class Enum_GameState : uint8
{
	BeginPlay UMETA(DisplayName = "Begin Play", Desription = "State displays only once on begin play."),
	MainMenu UMETA(DisplayName = "Main Menu", Description = "State for main menu"),
	InGameMenu UMETA(DisplayName = "In Game Menu", Description = "State for ingame menus which can be opened while playing."),
	PauseMenu UMETA(DisplayName = "Pause Menu", Description = "State for pause menu"),
	LoadingScreen UMETA(DisplayName = "Loading Screen", Description = "State when game is on loading screen"),
	Playing UMETA(DisplayName = "Playing", Description = "Selected state while playing"),
};
