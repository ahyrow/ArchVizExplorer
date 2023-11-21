// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPHelp.h"
#include "Serialization/JsonWriter.h"
//#include "Serialization/JsonSerializer.h"
//#include "Serialization/JsonTypes.h"
//#include "JsonObjectConverter.h"
#include"Policies/CondensedJsonPrintPolicy.h"
#include "HttpModule.h"
#include "Http.h"
//#include "Modules/ModuleManager.h"
#include "IImageWrapperModule.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/PreWindowsApi.h"
#include "Netlistmgr.h"
#include "Windows/PostWindowsApi.h"
//#include "Windows/HideWindowsPlatformTypes.h"


UHTTPHelp* UHTTPHelp::Get(FString ip, FString port, FString path, FString token, TMap<FString, FString> doc)
{
	FString Server_Data;
	//----转换url格式的参数字符串
	if(doc.Num()>0)
	{
		int index = 0;
		Server_Data.Append("?");
		for(auto It=doc.CreateConstIterator();It;++It)
		{
			index++;
			Server_Data.Append(It.Key());
			Server_Data.Append("=");
			Server_Data.Append(It.Value());
			if(doc.Num()!=index)
			{
				Server_Data.Append("&");
			}
		}
	}
    //创建HTTPHelp实例
	UHTTPHelp* node = NewObject<UHTTPHelp>();
	//创建http请求   request
	auto Request = FHttpModule::Get().CreateRequest();
	//设置请求头
	Request->SetHeader("content-Type", "application/json");
	UE_LOG(LogTemp, Log, TEXT("Token:%s"), *token);
	Request->SetHeader("Authorization", token);
	//设置请求方式
	Request->SetVerb("Get");
	Request->SetTimeout(60.f);
	//设置请求的urL拼接
	FString url = "";
	if(path=="")
	{
		url = ip + ":" + port + Server_Data;
	}else
	{
		url = ip + ":" + port +"/" +path + Server_Data;
	}
	Request->SetURL(url);

	UE_LOG(LogTemp, Log, TEXT("Get:%s"), *url); 

	//设置回调函数
	Request->OnProcessRequestComplete().BindUObject(node, &UHTTPHelp::RequestComplete);
	
	//发送请求
	Request->ProcessRequest();

	return node;
}

UHTTPHelp* UHTTPHelp::Post(FString ip, FString port, FString path, FString token, TMap<FString, FString> doc)
{

	FString Body;
	//创建Json
	TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Body);
	//开启json写入
	JsonWriter->WriteObjectStart();
	//写入数据
	for (auto it = doc.CreateConstIterator(); it; ++it)
	{
		JsonWriter->WriteValue(it.Key(), *it.Value());
	}
	//关闭写入
	JsonWriter->WriteObjectEnd();
	//关闭json写入
	JsonWriter->Close();
	//创建HTTPHelp实例
	UHTTPHelp* node = NewObject<UHTTPHelp>();
	//创建http请求   request
	auto Request = FHttpModule::Get().CreateRequest();
	//设置请求头
	Request->SetHeader("content-Type", "application/json");

	//------------

	UE_LOG(LogTemp, Log, TEXT("Token:%s"), *token);

	//------------
	Request->SetHeader("Authorization", token);
	//设置请求方式
	Request->SetVerb("Post");
	Request->SetTimeout(60.f);
	//设置请求的urL拼接
	FString url = "";
	if (path == "")
	{
		url = ip + ":" + port ;
	}
	else
	{
		url = ip + ":" + port + "/" + path ;
	}
	Request->SetURL(url);
	Request->SetContentAsString(Body);

    UE_LOG(LogTemp, Log, TEXT("Post url:%s"), *Request->GetURL());
	UE_LOG(LogTemp, Log, TEXT("Post body:%s"), *Body);

	//设置回调函数
	Request->OnProcessRequestComplete().BindUObject(node, &UHTTPHelp::RequestComplete);

	//发送请求
	Request->ProcessRequest();


	return  node;
}

//回调函数
void UHTTPHelp::RequestComplete
(FHttpRequestPtr RequesPtr, FHttpResponsePtr ResponsePtr, bool bIsSuccess)
{
	int32 ResponseCode = ResponsePtr->GetResponseCode();
	FString str = ResponsePtr->GetContentAsString();
	FString token = ResponsePtr->GetHeader("token");
	if(bIsSuccess&&ResponseCode==200)
	{
		UE_LOG(LogTemp,Log,TEXT("http success  %d %s"),ResponseCode,*str)
			if(OnSuccess.IsBound())
			{
				OnSuccess.Broadcast(ResponseCode, token, str);
			}
		

	}

	else
	{
		UE_LOG(LogTemp, Log, TEXT("http error  %d %s"), ResponseCode, *str)

			if(OnSuccess.IsBound())
			{
				OnFail.Broadcast(ResponseCode,"","");
			}
	}


}
