#pragma once

//�`�揇�p�X�e�[�^�X
enum class zOder {
	BACKGROUND =  0,
	MAIN_MENU,
	SUB_MENU,
	OPTION,
};

enum class LayerType
{
	BACGROUND = 0,
	MAIN_MENU,
	SUB_MENU,
	DIARY_MENU,
	OPTION,

	MAX
};

//���j���[�X�e�[�^�X
//�ǉ�����Ƃ���MAX�̏�ɋL�q���邱��
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

enum class BGType {
	MAIN_MENU = 0,
	BREEDING_MENU,

	MAX
};
