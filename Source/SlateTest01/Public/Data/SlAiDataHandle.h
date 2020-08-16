// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "SlAiTypes.h"
#include "CoreMinimal.h"

/**
 * 
 */
class USoundCue;

class SLATETEST01_API SlAiDataHandle
{
public:
	SlAiDataHandle();
	~SlAiDataHandle();
	static void Initialize();
	static TSharedPtr<SlAiDataHandle> Get();
	void ChangeLocalizationCulture(ECultureTeam NewCulture);
	void ResetMenuVolume(float MusicVal, float SoundVal);

	/*value*/
	//存档数据和存档名
	TArray<FString> RecordDataList;
	FString RecordName;
	//语言
	ECultureTeam CurrnetCulture;
	//音量
	float MusicVolume;
	float SoundVolume;

private:
	static TSharedRef<SlAiDataHandle> Create();
	template<typename TEnum>
	FString GetEnumValueAsString(const FString& name, TEnum Value);
	template<typename TEnum>
	TEnum GetEnumValueFromString(const FString& name, FString Value);
	void InitRecordData();
	void InitializeMenuAudio();

	/*value*/
	static TSharedPtr<SlAiDataHandle> DataInstance;
	TMap<FString, TArray<USoundCue*>> MenuAudioResource;
	const struct FSlAiMenuSlateStyle *MenuStyle;

	
};
