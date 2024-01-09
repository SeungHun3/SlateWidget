#include "Slice.h"

#define LOCTEXT_NAMESPACE "UMG"

// Slate ������ UMG ���� ���� �Ӽ��� ����ȭ�ϴ� �� ��� = UMG ������ �Ӽ��� ����� �� ȣ��
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
// SSlateSlice�� �����ϰ� �ʱ�ȭ�ϸ�, �׷��� ������ SSlateSlice�� ȭ�鿡 ǥ���� UMG �������� ���� = > SSlateSlice �� construct �̺�Ʈ�� �Ѿ
TSharedRef<SWidget> USlice::RebuildWidget()
{
	MySlice = SNew(SSlateSlice)
		.Brush(&Brush)
		.Angle(Angle)
		.ArcSize(ArcSize);
	return MySlice.ToSharedRef(); 
}
