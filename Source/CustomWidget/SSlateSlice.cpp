#include "SSlateSlice.h"
#include "SlateOptMacros.h"


#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Layout/Geometry.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlateSlice::Construct(const FArguments& InArgs)
{
	Brush = FInvalidatableBrushAttribute(InArgs._Brush);
	Angle = InArgs._Angle;
	ArcSize = InArgs._ArcSize;

	// SOverlay를 사용하여 SSlateSlice와 버튼을 함께 표시

	// 버튼의 내용
	TSharedRef<SWidget> ButtonContent = SNew(STextBlock)
		.Text(FText::FromString(TEXT("Click Me")));
	ChildSlot
		[
			SNew(SOverlay)

				//// SSlateSlice 표시
				//+ SOverlay::Slot()
				//[
				//	// SSlateSlice의 내용을 여기에 추가
				//
				//]

				// 버튼 표시
				+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(SButton)
						.Content()
						[
							ButtonContent
						]
				]
		];
	Button = ButtonContent;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

int32 SSlateSlice::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
	FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
	bool bParentEnabled) const
{
	//// 기존의 OnPaint 함수 동작 수행
	//int32 NewLayerId = SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	

	const FVector2D Pos = AllottedGeometry.GetAbsolutePosition();
	const FVector2D Size = AllottedGeometry.GetAbsoluteSize();
	const FVector2D Center = Pos + 0.5 * Size;
	const float Radius = FMath::Min(Size.X, Size.Y) * 0.5f;

	const FSlateBrush* SlateBrush = Brush.GetImage().Get();
	
	FLinearColor LinearColor = GetColorAndOpacity() * InWidgetStyle.GetColorAndOpacityTint() * SlateBrush->GetTint(InWidgetStyle);
	FColor FinalColorAndOpacity = LinearColor.ToFColor(true);

	const int NumSegments = FMath::RoundToInt(ArcSize / 10.0f);
	TArray<FSlateVertex> Vertices;
	Vertices.Reserve(NumSegments + 3);

	// Add center vertex
	Vertices.AddZeroed();
	FSlateVertex& CenterVertex = Vertices.Last();
	FVector2f convertCenter;
	convertCenter.X = Center.X;
	convertCenter.Y =  Center.Y;

	CenterVertex.Position = convertCenter;
	CenterVertex.Color = FinalColorAndOpacity;

	// Add edge vertices
	for (int i = 0; i < NumSegments + 2; ++i)
	{
		const float CurrentAngle = FMath::DegreesToRadians(ArcSize * i / NumSegments + Angle);
		const FVector2D EdgeDirection(FMath::Cos(CurrentAngle), FMath::Sin(CurrentAngle));
		const FVector2D OuterEdge(Radius*EdgeDirection);

		Vertices.AddZeroed();
		FSlateVertex& OuterVert = Vertices.Last();

		FVector2f convertEdge;
		convertEdge.X = OuterEdge.X;
		convertEdge.Y = OuterEdge.Y;
		OuterVert.Position = convertCenter + convertEdge;
		OuterVert.Color = FinalColorAndOpacity;	

		
	}

	TArray<SlateIndex> Indices;
	for (int i = 0; i <= NumSegments; ++i)
	{
		Indices.Add(0);
		Indices.Add(i);
		Indices.Add(i + 1);
	}

	const FSlateResourceHandle Handle = FSlateApplication::Get().GetRenderer()->GetResourceHandle( *SlateBrush );
	FSlateDrawElement::MakeCustomVerts(
        OutDrawElements,
        LayerId,
        Handle,
        Vertices,
        Indices,
        nullptr,
        0,
        0
    );


	// 버튼의 OnPaint 호출
	if (Button.IsValid())
	{
		const FVector2D ButtonSize(200.0f, 50.0f);
		const FLinearColor ButtonColor = FLinearColor::White; // 버튼의 색상을 여기에서 지정
		//const FVector2D& ChildOffset, const FVector2D& InLocalSize, float ChildScale = 1.0f
		const FGeometry ButtonGeometry = AllottedGeometry.MakeChild(
			FVector2D::ZeroVector,
			FVector2D(ButtonSize),
			1.0f);
		const FSlateRect ButtonCullingRect = MyCullingRect; // 버튼의 CullingRect를 여기에서 지정

		FSlateDrawElement::MakeBox(
			OutDrawElements,
			LayerId,
			ButtonGeometry.ToPaintGeometry(),
			FCoreStyle::Get().GetBrush("Button.Background"), // 배경에 사용할 Brush를 여기에서 지정
			ESlateDrawEffect::DisabledEffect,
			ButtonColor
		);
	}

	//UE_LOG(LogTemp, Log, TEXT("// Paint SSlate "));
	return LayerId;
}

void SSlateSlice::SetBrush(FSlateBrush* InBrush)
{
	Brush.SetImage(*this, InBrush);
}

void SSlateSlice::SetAngle(float InAngle)
{
	Angle = InAngle;
}

void SSlateSlice::SetArcSize(float InArcSize)
{
	ArcSize = InArcSize;
}

