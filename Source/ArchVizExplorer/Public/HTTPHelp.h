// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
//#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
//#include "Interfaces/IHttpResponse.h"
#include "HTTPHelp.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHttpCallBack, int32, ResponseCode, FString, Token, FString, Str);
UCLASS()
class ARCHVIZEXPLORER_API UHTTPHelp : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable);
	FHttpCallBack OnSuccess;
	UPROPERTY(BlueprintAssignable);
	FHttpCallBack OnFail;
public:

	UFUNCTION(BlueprintCallable,Category = "zz||Http", meta = (BlueprintInternalUseOnly = "true"))
	static UHTTPHelp* Get(FString ip, FString port, FString path, FString token, TMap<FString, FString> doc);
		
	UFUNCTION(BlueprintCallable,Category = "zz||Http", meta = (BlueprintInternalUseOnly = "true"))
	static UHTTPHelp* Post(FString ip, FString port, FString path, FString token, TMap<FString, FString> doc);
		

	void RequestComplete(FHttpRequestPtr RequesPtr, FHttpResponsePtr ResponsePtr, bool bIsSuccess);

	
};
