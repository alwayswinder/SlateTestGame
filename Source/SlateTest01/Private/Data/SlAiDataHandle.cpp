// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiDataHandle.h"
#include "Internationalization.h"
#include "SlAiJsonHandle.h"
#include "SlAiSingleton.h"
#include "SlAiHelper.h"
#include "SlAiWidgetStyle.h"
#include "SlAiMenuSlateWidgetStyle.h"
#include "Sound/SoundCue.h"


TSharedPtr<SlAiDataHandle> SlAiDataHandle::DataInstance = NULL;

SlAiDataHandle::SlAiDataHandle()
{
	InitRecordData();
	InitializeMenuAudio();
}

SlAiDataHandle::~SlAiDataHandle()
{
}

void SlAiDataHandle::Initialize()
{
	if (!DataInstance.IsValid())
	{
		DataInstance = Create();
	}
}

TSharedPtr<SlAiDataHandle> SlAiDataHandle::Get()
{
	Initialize();
	return DataInstance;
}

void SlAiDataHandle::ChangeLocalizationCulture(ECultureTeam NewCulture)
{
	switch (NewCulture)
	{
	case ECultureTeam::EN:
		FInternationalization::Get().SetCurrentLanguage(TEXT("en"));
		break;
	case ECultureTeam::CN:
		FInternationalization::Get().SetCurrentLanguage(TEXT("zh"));
		break;
	}
	CurrnetCulture = NewCulture;
	SlAiSingleton<SlAiJsonHandle>::Get()->UpdateRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"),
		CurrnetCulture), MusicVolume, SoundVolume, &RecordDataList);
}

void SlAiDataHandle::ResetMenuVolume(float MusicVal, float SoundVal)
{
	if (MusicVal >= 0 && MusicVal <= 1)
	{
		MusicVolume = MusicVal;

		for (TArray<USoundCue*>::TIterator It(MenuAudioResource.Find(FString("Music"))->CreateIterator()); It; ++It)
		{
			(*It)->VolumeMultiplier = MusicVolume;
		}
	}
	if (SoundVal >= 0 && SoundVal <= 1)
	{
		SoundVolume = SoundVal;
		for (TArray<USoundCue*>::TIterator It(MenuAudioResource.Find(FString("Sound"))->CreateIterator()); It; ++It)
		{
			(*It)->VolumeMultiplier = SoundVolume;
		}
	}

	SlAiSingleton<SlAiJsonHandle>::Get()->UpdateRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"),
		CurrnetCulture), MusicVolume, SoundVolume, &RecordDataList);

}

TSharedRef<SlAiDataHandle> SlAiDataHandle::Create()
{
	TSharedRef<SlAiDataHandle> DataRef = MakeShareable(new SlAiDataHandle());
	return DataRef;
}

template<typename TEnum>
FString SlAiDataHandle::GetEnumValueAsString(const FString& name, TEnum Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *name, true);
	if (!EnumPtr)
	{
		return FString("InValid");
	}
	return EnumPtr->GetEnumName((int32)Value);
}

template<typename TEnum>
TEnum SlAiDataHandle::GetEnumValueFromString(const FString& name, FString Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *name, true);
	if (!EnumPtr)
	{
		return TEnum(0);
	}
	return (TEnum)EnumPtr->GetIndexByName(FName(*FString(Value)));
}

void SlAiDataHandle::InitRecordData()
{
	RecordName = FString("");

	FString Culture;
	SlAiSingleton<SlAiJsonHandle>::Get()->RecordDataJsonRead(Culture, MusicVolume, SoundVolume, RecordDataList);
	CurrnetCulture = GetEnumValueFromString<ECultureTeam>(FString("ECultureTeam"), Culture);
	ChangeLocalizationCulture(CurrnetCulture);


	
	/*SlAiHelper::Debug(Culture + FString("--") + FString::SanitizeFloat(MusicVolume) + FString("--") + 
		FString::SanitizeFloat(SoundVolume), 40.f);

	for (TArray<FString>::TIterator It(RecordDataList); It; ++It)
	{
		SlAiHelper::Debug(*It, 40.f);
	}*/
}

void SlAiDataHandle::InitializeMenuAudio()
{
	MenuStyle = &SlAiWidgetStyle::Get().GetWidgetStyle<FSlAiMenuSlateStyle>("BPSlAiMenuStyle");

	TArray<USoundCue*> MusicList;
	MusicList.Add(Cast<USoundCue>(MenuStyle->MenuBackgroundMusic.GetResourceObject()));
	
	TArray<USoundCue*> SoundList;
	SoundList.Add(Cast<USoundCue>(MenuStyle->StartGameSound.GetResourceObject()));
	SoundList.Add(Cast<USoundCue>(MenuStyle->ExitGameSound.GetResourceObject()));
	SoundList.Add(Cast<USoundCue>(MenuStyle->MenuItemChangeSound.GetResourceObject()));

	MenuAudioResource.Add(FString("Music"), MusicList);
	MenuAudioResource.Add(FString("Sound"), SoundList);

	ResetMenuVolume(MusicVolume, SoundVolume);

}
