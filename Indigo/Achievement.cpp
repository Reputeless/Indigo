#include"Header.h"

void updateAchievement()
{
	if (numUnits >= 100 && achievements[0] == 0) {
		achievements[0] = -1;
		SoundAsset(L"7").playMulti();
		twitterText1 = L"���сF�����ȑ��̑���\n";
		twitterText2 = Format(year, L"�N��", season, L"���ɉ����I\n");
	}
	if (numUnits >= 250 && achievements[1] == 0) {
		achievements[1] = -1;
		SoundAsset(L"7").playMulti();
		twitterText1 = L"���сF�M���̒u���鑺��\n";
		twitterText2 = Format(year, L"�N��", season, L"���ɉ����I\n");
	}
	if (numUnits >= 500 && achievements[2] == 0) {
		achievements[2] = -1;
		SoundAsset(L"7").playMulti();
		twitterText1 = L"���сF����S��Y��Ȃ�����\n";
		twitterText2 = Format(year, L"�N��", season, L"���ɉ����I\n");
	}
	if (numUnits >= 1000 && achievements[3] == 0) {
		achievements[3] = -1;
		SoundAsset(L"7").playMulti();
		twitterText1 = L"���сF���|�I����\n";
		twitterText2 = Format(year, L"�N��", season, L"���ɉ����I\n");
	}
	if (achievements[4] > 10)
	{
		achievements[4] = -100000;
		SoundAsset(L"7").playMulti();
		twitterText1 = L"���сF�n����\n����10�����\n";
		twitterText2 = Format(year, L"�N��", season, L"���ɉ����I\n");
	}
	if (achievements[5] > 1000)
	{
		achievements[5] = -100000;
		SoundAsset(L"7").playMulti();
		twitterText1 = L"���сF�������W���[\n�_�n��1000�����\n";
		twitterText2 = Format(year, L"�N��", season, L"���ɉ����I\n");
	}
	if (achievements[6] == -2)
	{
		achievements[6] = -1;
		SoundAsset(L"7").playMulti();
		twitterText1 = L"���сF�������`��\n�������100�ȏ㐶�Y����\n";
		twitterText2 = Format(year, L"�N��", season, L"���ɉ����I\n");
	}
	if (achievements[7] == 0 && year >= 1000)
	{
		achievements[7] = -1;
		SoundAsset(L"7").playMulti();
		twitterText1 = L"���сF���̂Ă�ꂽPlatanus\n1000�N���o��\n";
		twitterText2 = Format(year, L"�N��", season, L"���ɉ����I\n");
	}
	if (achievements[8] == 1)
	{
		achievements[8] = -1;
		SoundAsset(L"7").playMulti();
		twitterText1 = L"���сF�łԉ^��\n�X���Ȃ����ɑ�������\n";
		twitterText2 = Format(year, L"�N��", season, L"���ɉ����I\n");
	}
	if (achievements[9] > 100)
	{
		achievements[9] = -100000;
		SoundAsset(L"7").playMulti();
		twitterText1 = L"���сF�A�E�g�o�[��\n���H��100��~��\n";
		twitterText2 = Format(year, L"�N��", season, L"���ɉ����I\n");
	}

}

