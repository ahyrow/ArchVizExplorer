// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Math/Color.h"
#include "GameFrameWork/Pawn.h"
#include "Tool.generated.h"

/**
 * 
 */
UCLASS()
class ARCHVIZEXPLORER_API UTool : public UObject
{
	GENERATED_BODY()
public:
	//log
	UFUNCTION(Blueprintcallable, Category = "zz||log", meta = (worldcontext = "WorldContextObject"))//Blueprintcallable, Category = "zz||log", meta = (worldcontext = "WorldContextObject")
		static void Log(UObject* WorldContextObject,
			FString One,
			FString Two,
			FString Three,
			float  Duration = 50.f,
			FLinearColor color = FLinearColor(0, 10, 0, 1.0), 
			bool  Activity = true,
			bool  Screen = true
		);
	//fstring map ×ª  json×Ö·û´®
	UFUNCTION(Blueprintcallable, Category = "zz||map", meta = (worldcontext = "WorldContextObject"))
		static FString StringMapJsonBody(TMap<FString, FString> Doc);
		
};
