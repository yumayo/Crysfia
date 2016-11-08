#pragma once

//描画順用ステータス
enum zOder {
	Menu = 1,
	Option,
};

//メニューステータス
//追加するときはMAXの上に記述すること
enum MenuType {
	STORY,
	BREEDING,
	DIARY,
	OPTION,

	MAX
};