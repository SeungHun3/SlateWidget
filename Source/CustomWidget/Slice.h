#pragma once

#include "CoreMinimal.h"


#include "SSlateSlice.h"
#include "Components/Widget.h"
#include "Slice.generated.h"

UCLASS()
class CUSTOMWIDGET_API USlice : public UWidget
{
	GENERATED_BODY()
public:
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Appearance")
	FSlateBrush Brush;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Appearance")
	float Angle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Appearance")
	float ArcSize;

	UFUNCTION(BlueprintCallable, Category="Appearance")
    void SetAngle(float InAngle);

	UFUNCTION(BlueprintCallable, Category="Appearance")
    void SetArcSize(float InArcSize);

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif
	
protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	TSharedPtr<SSlateSlice> MySlice;
};

/*
* USlice 클래스
* UMG(UISystem/WidgetSystem)의 일부로, Blueprint에서 사용되는 위젯을 정의하고 관리
* 
*  흐름 
*  SSlateSlice를 SNew(SSlateSlice)를 통해 생성하고, 여러 속성들(Brush, Angle, ArcSize)을 설정한 후, MySlice 변수에 저장
*/