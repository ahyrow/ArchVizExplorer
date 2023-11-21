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
	//����Json
    TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Body);
	//����jsonд��
	JsonWriter->WriteObjectStart();
	//д������
	for(auto it =doc.CreateConstIterator();it;++it)
	{
		JsonWriter->WriteValue(it.Key(), *it.Value());
	}
	//�ر�д��
	JsonWriter->WriteObjectEnd();
	//�ر�jsonд��
	JsonWriter->Close();

	return Body;

}
