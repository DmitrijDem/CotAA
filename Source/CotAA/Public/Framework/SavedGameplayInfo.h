// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/GameProperties/GameDifficulty.h"
#include "SavedGameplayInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct COTAA_API FSavedGameplayInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Name")
	FString PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Game Difficulty")
	EGameDifficulty GameDifficulty;
};
