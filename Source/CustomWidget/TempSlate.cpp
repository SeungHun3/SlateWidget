// Fill out your copyright notice in the Description page of Project Settings.


#include "TempSlate.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"

void STempSlate::Construct(const FArguments& InArgs)
{
    // 위젯에 버튼 추가
    ChildSlot
        [
            SNew(SBox)
                .HAlign(HAlign_Center)
                .VAlign(VAlign_Center)
                [
                    SNew(SButton)
                        //.OnClicked(this, &SYourWidget::OnButtonClicked)
                        .Text(FText::FromString(TEXT("Create Blocking Volume")))
                ]
        ];
}

int32 STempSlate::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	return int32();
}