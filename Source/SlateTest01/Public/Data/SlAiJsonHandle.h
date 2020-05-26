// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlAiTypes.h"
#include "Json.h"

/**
 * 
 */
class SLATETEST01_API SlAiJsonHandle
{
public:
	SlAiJsonHandle();
	~SlAiJsonHandle();

	void RecordDataJsonRead(FString& Culture, float& MusicVolume, float& SoundVolume, TArray<FString>& RecordDataList);


	//���´浵
	TSharedPtr<FJsonObject> UpdateRecordData(FString Culture, float MusicVolume, float SoundVolume,
	TArray<FString>*RecordDataList);

private:
	//��ȡJson�ļ����ַ���
	bool LoadStringFromFile(const FString& FileName, const FString& Relapath, FString& ResultString);

	bool WriteFileWithJsonData(const FString& JsonStr, const FString& RelaPath, const FString& FileName);

	//Json���ݵ�Json�ַ���
	bool GetFStringInJsonData(const TSharedPtr<FJsonObject>& JsonObj, FString& JsonStr);
private:
	FString RecordDataFileName;
	FString RelativePath;
};
