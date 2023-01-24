// Copyright 2023 Les Androïds Associés. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FFlatNodesModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void ApplyEditorStyle();
};
