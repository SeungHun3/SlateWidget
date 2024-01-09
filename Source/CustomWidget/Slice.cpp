#include "Slice.h"

#define LOCTEXT_NAMESPACE "UMG"

// Slate 위젯과 UMG 위젯 간의 속성을 동기화하는 데 사용 = UMG 위젯의 속성이 변경될 때 호출
void USlice::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	MySlice->SetBrush(&Brush);
	MySlice->SetAngle(Angle);
	MySlice->SetArcSize(ArcSize);
}

void USlice::ReleaseSlateResources(bool bReleaseChildren)
{
	MySlice.Reset();
}

void USlice::SetAngle(float InAngle)
{
	Angle = InAngle;
	if (MySlice)
	{
		MySlice->SetAngle(Angle);
	}
}

void USlice::SetArcSize(float InArcSize)
{
	ArcSize = InArcSize;
	if (MySlice)
	{
		MySlice->SetArcSize(ArcSize);
	}
}

#if WITH_EDITOR
const FText USlice::GetPaletteCategory()
{
	return LOCTEXT("CustomPaletteCategory", "My custom category!");
}
#endif
// SSlateSlice를 생성하고 초기화하며, 그렇게 생성된 SSlateSlice를 화면에 표시할 UMG 위젯으로 설정 = > SSlateSlice 의 construct 이벤트로 넘어감
TSharedRef<SWidget> USlice::RebuildWidget()
{
	MySlice = SNew(SSlateSlice)
		.Brush(&Brush)
		.Angle(Angle)
		.ArcSize(ArcSize);
	return MySlice.ToSharedRef(); 
}
