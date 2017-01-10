#pragma once

//描画順用ステータス
enum class zOder {
	BACKGROUND = 0,
	CHARACTER,
	UI_MANAGER,
	MENU,
	OPTION,
	FOREGROUND,
	
};

enum class tabLayer
{
	BACKGROUND = 0,
	CHARACTER,
	UI_MANAGER,
	BREEDING,
	CLEANING,
	FOREGROUND,
	LAYER_MANAGER = -1,
	DIARY,

	MAX
};

//メニューステータス
//追加するときはMAXの上に記述すること
enum class ButtonType {
	STORY = 0,
	BREEDING,
	DIARY,
	OPTION,

	MAX
};

enum class SubButtonType
{
	BACK,
	MEAL,
	CLOTHES,
	CLEANING,

	MAX
};

enum class tabMenu {
	MAIN_MENU = 0,
	BREEDING_MENU,
	DIARY_MENU,
	OPTION,

	MAX
};

enum BreedingID {
	MEAL,
	DRESS_CLOSET
};