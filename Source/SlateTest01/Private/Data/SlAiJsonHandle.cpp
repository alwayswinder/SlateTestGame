// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiJsonHandle.h"
#include "SlAiHelper.h"



SlAiJsonHandle::SlAiJsonHandle()
{
	RecordDataFileName = FString("RecordData.json");
	RelativePath = FString("Res/ConfigData/");
}

SlAiJsonHandle::~SlAiJsonHandle()
{
}

void SlAiJsonHandle::RecordDataJsonRead(FString& Culture, float& MusicVolume, float& SoundVolume,
	TArray<FString>& RecordDataList)
{
	FString JsonValue;
	LoadStringFromFile(RecordDataFileName, RelativePath, JsonValue);

	TArray<TSharedPtr<FJsonValue>> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);
	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
	{
		Culture = JsonParsed[0]->AsObject()->GetStringField(FString("Culture"));

		MusicVolume = JsonParsed[1]->AsObject()->GetNumberField(FString("MusicVolume"));
		SoundVolume = JsonParsed[2]->AsObject()->GetNumberField(FString("SoundVolume"));

		TArray<TSharedPtr<FJsonValue>> RecordDataArray = JsonParsed[3]->AsObject()->GetArrayField(FString("RecordData"));
		for (int i=0; i<RecordDataArray.Num(); i++)
		{
			FString RecordDataName = RecordDataArray[i]->AsObject()->GetStringField(FString::FromInt(i));
			RecordDataList.Add(RecordDataName);
		}

	}
	else
	{
		SlAiHelper::Debug(FString("Deserialize Failed"));
	}
}

TSharedPtr<FJsonObject> SlAiJsonHandle::UpdateRecordData(FString Culture, float MusicVolume, float SoundVolume, 
	TArray<FString>*RecordDataList)
{
	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject);

	TArray<TSharedPtr<FJsonValue>> BaseDataArray;

	TSharedPtr<FJsonObject> CultureObject = MakeShareable(new FJsonObject);
	CultureObject->SetStringField("Culture", Culture);
	TSharedPtr<FJsonValueObject> CultureValue = MakeShareable(new FJsonValueObject(CultureObject));

	TSharedPtr<FJsonObject> MusicVolumeObject = MakeShareable(new FJsonObject);
	MusicVolumeObject->SetNumberField("MusicVolume", MusicVolume);
	TSharedPtr<FJsonValueObject> MusicVolumeValue = MakeShareable(new FJsonValueObject(MusicVolumeObject));

	TSharedPtr<FJsonObject> SoundVolumeObject = MakeShareable(new FJsonObject);
	SoundVolumeObject->SetNumberField("SoundVolume", SoundVolume);
	TSharedPtr<FJsonValueObject> SoundVolumeValue = MakeShareable(new FJsonValueObject(SoundVolumeObject));

	TArray<TSharedPtr<FJsonValue>> RecordDataArray;

	for (int i=0; i<RecordDataList->Num(); i++)
	{
		TSharedPtr<FJsonObject> RecordItem = MakeShareable(new FJsonObject);
		RecordItem->SetStringField(FString::FromInt(i), (*RecordDataList)[i]);
		TSharedPtr<FJsonValueObject> RecordItemValue = MakeShareable(new FJsonValueObject(RecordItem));
		RecordDataArray.Add(RecordItemValue);
	}

	TSharedPtr<FJsonObject> RecordDataObject = MakeShareable(new FJsonObject);
	RecordDataObject->SetArrayField("RecordData", RecordDataArray);
	TSharedPtr<FJsonValueObject> RecordDataValue = MakeShareable(new FJsonValueObject(RecordDataObject));

	BaseDataArray.Add(CultureValue);
	BaseDataArray.Add(MusicVolumeValue);
	BaseDataArray.Add(SoundVolumeValue);
	BaseDataArray.Add(RecordDataValue);

	JsonObj->SetArrayField("T", BaseDataArray);
	FString JsonStr;
	GetFStringInJsonData(JsonObj, JsonStr);
	//SlAiHelper::Debug(FString("Origin Str :" + JsonStr), 60.f);

	JsonStr.RemoveAt(0, 8);
	JsonStr.RemoveFromEnd(FString("}"));
	//SlAiHelper::Debug(FString("Final Str:" + JsonStr), 60.f);

	WriteFileWithJsonData(JsonStr, RelativePath, RecordDataFileName);

	return NULL;
}

bool SlAiJsonHandle::LoadStringFromFile(const FString& FileName, const FString& Relapath, FString& ResultString)
{
	if (!FileName.IsEmpty())
	{
		FString AbsoPath = FPaths::GameContentDir() + Relapath + FileName;
		if (FPaths::FileExists(AbsoPath))
		{
			if (FFileHelper::LoadFileToString(ResultString, *AbsoPath))
			{
				return true;
			}
			else
			{
				SlAiHelper::Debug(FString("Load Error") + AbsoPath);

			}
		}
		else
		{
			SlAiHelper::Debug(FString("File Not Exist") + AbsoPath);
		}
	}
	return false;
}

//保存json到文件
bool SlAiJsonHandle::WriteFileWithJsonData(const FString& JsonStr, const FString& RelaPath, const FString& FileName)
{
	if (!JsonStr.IsEmpty())
	{
		if (!FileName.IsEmpty())
		{
			FString AbsoPath = FPaths::GameContentDir() + RelaPath + FileName;

			if (FFileHelper::SaveStringToFile(JsonStr, *AbsoPath))
			{
				return true;
			}
			else
			{
				SlAiHelper::Debug("WriteFileWithJsonData Error");
			}
		}
	}
	return false;
}

bool SlAiJsonHandle::GetFStringInJsonData(const TSharedPtr<FJsonObject>& JsonObj, FString& JsonStr)
{
	if (JsonObj.IsValid() && JsonObj->Values.Num() > 0)
	{
		TSharedRef<TJsonWriter<TCHAR>> JSonWrite = TJsonWriterFactory<TCHAR>::Create(&JsonStr);
		FJsonSerializer::Serialize(JsonObj.ToSharedRef(), JSonWrite);
		return true;
	}
	return false;
}
