// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TempWidget.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class CUSTOMWIDGET_API UTempWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UTempWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	class UButton* MyButton;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Widget")
	//TSubclassOf<class USlice> SliceWidgetClass;



protected:
	//UPROPERTY()
	//class USlice* MySliceWidget;

};
