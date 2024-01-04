// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LLL_InteractiveEntityInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULLL_InteractiveEntityInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class Y2024Q1_PROTOTYPING_API ILLL_InteractiveEntityInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void InteractiveEvent() = 0;
	
};
