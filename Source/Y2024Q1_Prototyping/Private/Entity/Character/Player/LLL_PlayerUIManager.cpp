// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Character/Player/LLL_PlayerUIManager.h"

#include "DataAsset/LLL_PlayerBaseDataAsset.h"
#include "Entity/Character/Player/LLL_PlayerBase.h"
#include "Entity/Object/Interactive/LLL_InteractiveObject.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Player/LLL_InteractionWidget.h"
#include "UI/Player/LLL_InventoryWidget.h"
#include "UI/Player/LLL_PlayerStatusWidget.h"
#include "UI/System/LLL_GamePauseWidget.h"

// Sets default values for this component's properties
ULLL_PlayerUIManager::ULLL_PlayerUIManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	PauseWidget = CreateDefaultSubobject<ULLL_GamePauseWidget>(TEXT("PauseWidget"));
	InventoryWidget = CreateDefaultSubobject<ULLL_InventoryWidget>(TEXT("InventoryWidget"));
	InteractionWidget = CreateDefaultSubobject<ULLL_InteractionWidget>(TEXT("InteractionWidget"));
	PlayerStatusWidget = CreateDefaultSubobject<ULLL_PlayerStatusWidget>(TEXT("StatusWidget"));
}


// Called when the game starts
void ULLL_PlayerUIManager::BeginPlay()
{
	Super::BeginPlay();

	const ULLL_PlayerBaseDataAsset* PlayerBaseDataAsset = CastChecked<ALLL_PlayerBase>(GetOwner())->GetPlayerDataAsset();
	PauseWidgetClass = PlayerBaseDataAsset->PauseWidgetClass;
	InventoryWidgetClass = PlayerBaseDataAsset->InventoryWidgetClass;
	InteractionWidgetClass = PlayerBaseDataAsset->InteractionWidgetClass;
	PlayerStatusWidgetClass = PlayerBaseDataAsset->StatusWidgetClass;
	
	if(IsValid(PauseWidgetClass))
	{
		PauseWidget = CastChecked<ULLL_GamePauseWidget>(CreateWidget(GetWorld(), PauseWidgetClass));
		PauseWidget->AddToViewport();
		PauseWidget->SetVisibility(ESlateVisibility::Hidden);
		PauseWidget->SetIsEnabled(false);
	}

	if(IsValid(InventoryWidgetClass))
	{
		InventoryWidget = CastChecked<ULLL_InventoryWidget>(CreateWidget(GetWorld(), InventoryWidgetClass));
		InventoryWidget->AddToViewport();
		InventoryWidget->SetIsEnabled(false);
	}

	if(IsValid(InteractionWidgetClass))
	{
		InteractionWidget = CastChecked<ULLL_InteractionWidget>(CreateWidget(GetWorld(), InteractionWidgetClass));
		InteractionWidget->AddToViewport();
		InteractionWidget->SetIsEnabled(false);
	}
	
	if(IsValid(PlayerStatusWidgetClass))
	{
		PlayerStatusWidget = CastChecked<ULLL_PlayerStatusWidget>(CreateWidget(GetWorld(), PlayerStatusWidgetClass));
		PlayerStatusWidget->AddToViewport();
	}
}


// Called every frame
void ULLL_PlayerUIManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULLL_PlayerUIManager::TogglePauseWidget() const
{
	if(PauseWidget->GetIsEnabled())
	{
		PauseWidget->SetVisibility(ESlateVisibility::Hidden);
		PauseWidget->SetIsEnabled(false);
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	}
	else
	{
		PauseWidget->SetVisibility(ESlateVisibility::Visible);
		PauseWidget->SetIsEnabled(true);
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), SMALL_NUMBER);
	}
}

void ULLL_PlayerUIManager::ToggleInventoryWidget() const
{
	//TODO: 애니메이션 처리 여부 생각하기
	if(!InventoryWidget->IsPlayingAnimation())
	{
		if(InventoryWidget->GetIsEnabled())
		{
			InventoryWidget->PlayCloseAnimation();
			InventoryWidget->SetIsEnabled(false);
		}
		else
		{
			InventoryWidget->PlayOpenAnimation();
			InventoryWidget->SetIsEnabled(true);
		}
	}
}

void ULLL_PlayerUIManager::EnableInteractionWidget() const
{
	if(!InteractionWidget->GetIsEnabled())
	{
		InteractionWidget->PlayVisibleAnimation();
		InteractionWidget->SetIsEnabled(true);
	}
}

void ULLL_PlayerUIManager::DisableInteractionWidget() const
{
	InteractionWidget->PlayHideAnimation();
	InteractionWidget->SetIsEnabled(false);
}

void ULLL_PlayerUIManager::UpdateInteractionWidget(ALLL_InteractiveObject* CurrentObject) const
{
	
}

void ULLL_PlayerUIManager::UpdateStatusWidget() const
{
	// TODO: 체력 시스템 구현하고 만들기
}

void ULLL_PlayerUIManager::SetAllWidgetVisibility(const bool Visible)
{
	if(Visible)
	{
		PauseWidget->SetVisibility(ESlateVisibility::Hidden);
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		PlayerStatusWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		PauseWidget->SetVisibility(ESlateVisibility::Visible);
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		PlayerStatusWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
