// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeekOfDay.generated.h"

/**
 * 
 */
UCLASS()
class ARCHVIZEXPLORER_API UWeekOfDay : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "DayOfWeek")

		static void GetDayOfWeek(int32 Day, int32 Mouth, int32 Year, int32 C, int32& W);
	
};
