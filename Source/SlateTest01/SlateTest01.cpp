// Fill out your copyright notice in the Description page of Project Settings.

#include "SlateTest01.h"
#include "Modules/ModuleManager.h"
#include "SlAiWidgetStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "SlAiDataHandle.h"


void FSlateTest01Module::StartupModule()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(SlAiWidgetStyle::GetStyleSetName());
	SlAiWidgetStyle::Initialze();
	SlAiDataHandle::Initialize();
}

void FSlateTest01Module::ShutdownModule()
{
	SlAiWidgetStyle::ShutDown();
}
IMPLEMENT_PRIMARY_GAME_MODULE(FSlateTest01Module, SlateTest01, "SlateTest01");