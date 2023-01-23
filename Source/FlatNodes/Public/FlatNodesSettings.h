// Copyright 2023 Les Androïds Associés. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

#include "FlatNodesSettings.generated.h"

/**
 * Configure the Flat Nodes plug-in.
 */
UCLASS(config = EditorPerProjectUserSettings)
class UFlatNodesSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UFlatNodesSettings();

#if WITH_EDITOR
	//~ UDeveloperSettings interface
	virtual FText GetSectionText() const override;

	/**
	 * Called when a property on this object has been modified externally
	 *
	 * @param PropertyThatChanged the property that was modified
	 */
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	FSlateBrush* CreateHeaderBrush();

	/** Whether to use gradient on node header or not. Default: false */
	UPROPERTY(config, EditAnywhere, Category = "Header", DisplayName = "Use Gradient", meta = (ConfigRestartRequired = true))
	bool bHeaderUseGradient;

	/** Brightness of node header. Default: 0.25 */
	UPROPERTY(config, EditAnywhere, Category = "Header", DisplayName = "Brightness", meta = (EditCondition = "!bHeaderUseGradient", ClampMin = "0", ClampMax = "1"))
	float HeaderBrightness = 0.25f;

	TMap<FString, FSlateBrush*> SlateBrushes;
};
