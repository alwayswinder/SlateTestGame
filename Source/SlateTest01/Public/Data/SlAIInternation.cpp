#include "SlAIInternation.h"



#define LOCTEXT_NAMESPACE "SlAiMenu"

SlAIInternation::SlAIInternation()
{

	SlAIInternation::Register(LOCTEXT("Menu", "Menu"));

	SlAIInternation::Register(LOCTEXT("StartGame", "StartGame"));
	SlAIInternation::Register(LOCTEXT("GameOption", "GameOption"));
	SlAIInternation::Register(LOCTEXT("QuitGame", "QuitGame"));
	SlAIInternation::Register(LOCTEXT("NewGame", "NewGame"));
	SlAIInternation::Register(LOCTEXT("LoadRecord", "LoadRecord"));
	SlAIInternation::Register(LOCTEXT("ChooseRecord", "ChooseRecord"));
	SlAIInternation::Register(LOCTEXT("EnterGame", "EnterGame"));
	SlAIInternation::Register(LOCTEXT("RecordNameHint", "RecordNameHint"));
	SlAIInternation::Register(LOCTEXT("NameRepeateHint", "NameRepeateHint"));
	SlAIInternation::Register(LOCTEXT("Chinese", "Chinese"));
	SlAIInternation::Register(LOCTEXT("English", "English"));
	SlAIInternation::Register(LOCTEXT("Music", "Music"));
	SlAIInternation::Register(LOCTEXT("Sound", "Sound"));
	SlAIInternation::Register(LOCTEXT("GoBack", "GoBack"));
	SlAIInternation::Register(LOCTEXT("InputRecordName", "InputRecordName"));

}

#undef LOCTEXT_NAMESPACE