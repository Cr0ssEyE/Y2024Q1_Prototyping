// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LLLStringDataTable.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FStringDataTable : public FTableRowBase
{
	GENERATED_BODY()
	
	// 해당 FName과 일치하는 열의 값 읽어옴
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName Kor;
};

UCLASS()
class Y2024Q1_PROTOTYPING_API ULLLStringDataTable : public UDataTable
{
	GENERATED_BODY()
	
};