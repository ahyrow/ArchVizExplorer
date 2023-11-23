// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/WeekOfDay.h"
#include "Runtime/Core/Public/Misc/DateTime.h"
#include "Kismet/KismetStringLibrary.h"

void UWeekOfDay::GetDayOfWeek(int32 Day, int32 Mouth, int32 Year, int32 C, int32& W)
{
	if (Day == 0 || Mouth == 0)
	{
		FDateTime Time = FDateTime::Now();
		FString CAndYear = FString::FromInt(Time.GetYear());
		FString Century = UKismetStringLibrary::GetSubstring(CAndYear, 0, 2);
		FString Y = UKismetStringLibrary::GetSubstring(CAndYear, 2, 4);
		C = FCString::Atoi(*Century);
		Year = FCString::Atoi(*Y);
		Day = Time.GetDay();
		Mouth = Time.GetMonth();
	};
	if (Mouth == 1 || Mouth == 2)
	{
		Mouth += 12;
		if (Year == 0)
		{
			Year = 99;
			C -= 1;
		}
		else
		{
			Year -= 1;
		}

	}
	float a;
	a = C / 4;
	float b;
	b = Year / 4;
	float c;
	c = 26 * (Mouth + 1) / 10;


	W = (FMath::CeilToInt(a) - 2 * C + Year + FMath::CeilToInt(b) + FMath::CeilToInt(c) + Day - 1) % 7;
}