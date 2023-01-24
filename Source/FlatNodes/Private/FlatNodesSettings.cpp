// Copyright 2023 Les Androïds Associés. All Rights Reserved.

#include "FlatNodesSettings.h"
#include "Materials/MaterialInstanceDynamic.h"

#define LOCTEXT_NAMESPACE "FlatNodes"

UFlatNodesSettings::UFlatNodesSettings()
{
	CategoryName = TEXT("Plugins");
	SectionName = TEXT("FlatNodes");
}

#if WITH_EDITOR
FText UFlatNodesSettings::GetSectionText() const
{
	return LOCTEXT("UserSettingsDisplayName", "Flat Nodes");
}

void UFlatNodesSettings::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property)
	{
		const FName NAME_HeaderBrightness = GET_MEMBER_NAME_CHECKED(UFlatNodesSettings, HeaderBrightness);
		const FName PropertyName = PropertyChangedEvent.GetPropertyName();

		if (PropertyName == NAME_HeaderBrightness)
		{
			UObject* ResourceObject = SlateBrushes["HeaderBrush"]->GetResourceObject();
			UMaterialInterface* Material = Cast<UMaterialInterface>(ResourceObject);

			if (Material)
			{
				UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(Material);
				DynamicMaterial->SetVectorParameterValue("Color", FVector(HeaderBrightness, HeaderBrightness, HeaderBrightness));
			}
		}
	}
}
#endif	// WITH_EDITOR

FSlateBrush* UFlatNodesSettings::CreateHeaderBrush()
{
	FSlateBrush* SlateBrush = new FSlateBrush();

	const FString MaterialPath = FString("/FLatNodes/Materials/Box.Box");
	UMaterial* Material = LoadObject<UMaterial>(nullptr, *MaterialPath);
	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);

	DynamicMaterial->SetVectorParameterValue("Color", FVector(HeaderBrightness, HeaderBrightness, HeaderBrightness));
	DynamicMaterial->AddToRoot();

	SlateBrush->SetResourceObject(DynamicMaterial);
	SlateBrushes.Add("HeaderBrush", SlateBrush);

	return SlateBrush;
}

#undef LOCTEXT_NAMESPACE
