// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/GameKitFL.h"

#include "Blueprint/UserWidget.h"

float UGameKitFL::CalculateAnimationCurrentTime(UUserWidget* SelfReference, UWidgetAnimation* InAnimation)
{

	if (!SelfReference)
	{
		UE_LOG(LogTemp, Error, TEXT("GameKitFL: CalculateAnimationCurrentTime - SelfReference is not initialized!"));
		return 0.0f;
	}

	if (!InAnimation)
	{
		UE_LOG(LogTemp, Error, TEXT("GameKitFL: CalculateAnimationCurrentTime - InAnimation is not initialized!"));
		return 0.0f;
	}

	const float PauseTime = SelfReference->PauseAnimation(InAnimation);
	const float EndTime = InAnimation->GetEndTime();
	
	
	return PauseTime == 0.0f ? 0.0f : EndTime - PauseTime;
}
