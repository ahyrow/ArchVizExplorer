// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool.h"
#include"kismet/KismetsystemLibrary.h"
void UTool::Log(
	UObject* WorldContextObject, 
	FString One, 
	FString Two, 
	FString Three, 
	float Duration, 
	FLinearColor color, 
	bool Activity, 
	bool Screen)
{
	if (!Activity) return;

	One.Append(" ");
	One.Append(Two);
	One.Append(" ");
	One.Append(Three);
	UKismetSystemLibrary::PrintString(WorldContextObject, One, 1, 1, color, Duration);

}

FString UTool::StringMapJsonBody(TMap<FString, FString> doc)
{
	FString Body;
	//创建Json
    TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Body);
	//开启json写入
	JsonWriter->WriteObjectStart();
	//写入数据
	for(auto it =doc.CreateConstIterator();it;++it)
	{
		JsonWriter->WriteValue(it.Key(), *it.Value());
	}
	//关闭写入
	JsonWriter->WriteObjectEnd();
	//关闭json写入
	JsonWriter->Close();

	return Body;

}
