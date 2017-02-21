#include"Unit.h"
#include"Header.h"

void	Unit::unitAI()
{
	//Timer�̏�����
	Timer2 = 0;
	Timer1 = 0;
	switch (Status)
	{
	case DoNothing: //�H��A�N����Ɍʏ����ɕ��A���邽�߂̏ꏊ
		//�����󂢂Ă���̂��Ƃ�������
		if (NumEat == 0 || (NumEat == 1 && sec > 43200) || (NumEat == 2 && isNight())) setStatus(TakeMeal);
		else if (isNight()) setStatus(GoToSleep);
		else
		{

			switch (getJob())
			{
			case Labor:		setPenalty(3600); break;
			case Farmer:	setStatus(WorkAsFarmer); break;
			case Woodcutter:setStatus(WorkAsWoodcutter); break;
			case Builder:	setStatus(WorkAsBuilder); break;
			case Brewer:	setStatus(WorkAsBrewer); break;
			default:		setPenalty(600); break;
			}
		}
		break;

	case IsSleeping: //�Q�Ă��遨�N�����ꍇ
		setStatus(DoNothing);
		break;



		//�����Ă��镨��[�i����
	case Deliver:
		switch (aiProgress)
		{
		case 0:
			switch (getJob())
			{
			case Farmer:	//�s��ɗa����^�C�v
				if (goNearMarket()) aiProgress = 1;
				else setPenalty(3600);
				break;
			default:		//�����̎{�݂ɗa����^�C�v
				if (goTo(getJobFacility())) aiProgress = 1;
				else setPenalty(3600);
				break;
			}
			break;

		case 1:
			sendItemToFacility();
			setStatus(DoNothing);
			break;

		default: Println(L"D Progress Error"); setPenalty(3600); break;
		}
		break;



		/*
		�H�������
		�Ƃ�Rice��������Ύ��ɍs��
		�Ƃ�Wood��������Ύ��ɍs��
		*/
	case TakeMeal:
	{
		Facility* f;
		switch (aiProgress)
		{
		case 0:	//�A�C�e����a����
			if (!hasHomeFacility())
			{
				f = searchItem(Rice);
				if (f == NULL) setPenalty(3600);
				else
				{
					if (getStandingChip().getOwnFacility() == f)
					{
						receiveFromFacility(Rice, 1);
						aiProgress = 8;
						goRoomRandom();
					}
					else goTo(f);
				}
			}
			else if (NumItems > 0) setStatus(Deliver);	//�a���Ă���̏���
			else if (getHomeFacility()->getNumItem(Rice) == 0) aiProgress = 1;
			else if (getHomeFacility()->getNumItem(Wood) == 0) aiProgress = 2;
			else aiProgress = 7;
			break;

		case 1:	//Rice��T���A���ɍs��
			f = searchItem(Rice);
			if (f == NULL) setPenalty(3600);
			else { goTo(f); aiProgress = 3; }
			break;
		case 2:	//Wood��T���A���ɍs��
			f = searchItem(Wood);
			if (f == NULL) setPenalty(3600);
			else { goTo(f); aiProgress = 4; }
			break;
		case 3:	//Rice���擾�A�����ĉƂɖ߂�
			if (receiveFromFacility(Rice, 3) == 0) aiProgress = 1;	//�����A������΍ĒT��
			else if (goTo(getHomeFacility())) aiProgress = 6;
			else setPenalty(3600);
			break;
		case 4:	//Wood���擾�A�����ĉƂɖ߂�
			if (receiveFromFacility(Wood, 3) == 0) aiProgress = 2;	//�����A������΍ĒT��
			else if (goTo(getHomeFacility())) aiProgress = 6;
			else setPenalty(3600);
			break;
		case 6:	//�ƂɋA���Ă��āA�ו��𗎂Ƃ�
			if (getNumItem(Rice) > 0) sendItemToFacility(Rice);
			if (getNumItem(Wood) > 0) sendItemToFacility(Wood);
			aiProgress = 0;
			break;
		case 7:	//Rice�̏���^�C�}�[���Z�b�g
			if (getStandingChip().getOwnFacility() == getHomeFacility())
			{
				receiveFromFacility(Rice, 1);
				receiveFromFacility(Wood, 1);
				aiProgress = 8;
				goRoomRandom();
			}
			else if (!goTo(getHomeFacility())) setPenalty(3600);
			break;
		case 8:
			Timer1 = 60;
			aiProgress = 9;
			break;
		case 9:	//Rice������
			addItem(Rice, -1);
			addItem(Wood, -1);
			NumEat++;
			setStatus(DoNothing);
			break;

		default: Println(L"TM Progress Error"); setPenalty(3600); break;
		}
		break;
	}

	//�Q��
	case GoToSleep:
	{
		switch (aiProgress)
		{
		case 0:	//�Ƃɖ߂�
			if (NumItems > 0) setStatus(Deliver);
			else
			{
				goTo(getHomeFacility());	//�Ȃ��ꍇ�͂��̏�ő��s
				aiProgress = 1;
			}
			break;
		case 1:
			goRoomRandom();
			aiProgress = 2;
			break;
		case 2:
			IsSleep = true;
			setStatus(IsSleeping);
			break;
		default: Println(L"GTS Progress Error"); setPenalty(3600); break;
		}
		break;
	}

	//�����_��
	case WorkAsFarmer:
	{
		switch (aiProgress)
		{
		case 0:
			if (goTo(getJobFacility())) aiProgress = 1;
			else setPenalty(3600);
			break;
		case 1:
			goRoomRandom();
			aiProgress = 2;
			break;
		case 2:
			Timer1 = 3600;
			aiProgress = 3;
			break;
		case 3:
			produceItem(Rice, 1);
			setStatus(DoNothing);
			break;
		default: Println(L"WAF Progress Error"); setPenalty(3600); break;
		}
		break;
	}

	//�؂���
	case WorkAsWoodcutter:
	{
		switch (aiProgress)
		{
		case 0:
			if (getJobFacility()->getNumItem(Wood) > 1000) setPenalty(3600);
			if (goToNearForest()) aiProgress = 2;
			else setPenalty(3600);
			break;
		case 2:
			Timer1 = 300;
			aiProgress = 3;
			break;
		case 3:
			produceItem(Wood, 1);
			setStatus(DoNothing);
			break;
		default: Println(L"WAW Progress Error"); setPenalty(3600); break;
		}
		break;
	}

	//

	//��H
	case WorkAsBuilder:
	{
		Facility* f;
		if (!hasTarFacility() || getTarFacility()->BuildProgress == 0 || !isConeected(getTarFacility()->getEntranceChip())) setTarFacility(searchPlannedSite());
		if (getTarFacility() == NULL) aiProgress = 0;
		switch (aiProgress)
		{
		case 0:	//�d����̊m�F
			if (!hasTarFacility()) setPenalty(3600);
			else
			{
				if (getNumItem(Wood) == 0) aiProgress = 1;
				else aiProgress = 3;
			}
			break;

		case 1:	//�؍ނ������Ă���
			f = searchItem(Wood);
			if (f == NULL) setPenalty(3600);
			else
			{
				goTo(f);
				aiProgress = 2;
			}
			break;

		case 2:
			if (receiveFromFacility(Wood, 10) == 0) aiProgress = 1;
			else aiProgress = 3;
			break;

		case 3:
			if (goTo(getTarFacility())) aiProgress = 4;
			else aiProgress = 0;
			break;

		case 4:
			goRoomRandom();
			aiProgress = 5;
			break;
		case 5:
			Timer1 = 60;
			aiProgress = 6;
			break;
		case 6:
			addItem(Wood, -1);
			getTarFacility()->BuildProgress--;
			setStatus(DoNothing);
			break;
		default: Println(L"WAB1 Progress Error"); setPenalty(3600); break;
		}
		break;
	}

	//������
	case WorkAsBrewer:
	{
		Facility* f;
		switch (aiProgress)
		{
		case 0:	//�d����̊m�F
			if (getNumItem(Wood) == 0 && receiveFromFacility(Wood, 10) == 0) aiProgress = 1;
			else if (getNumItem(Rice) == 0 && receiveFromFacility(Rice, 10) == 0) aiProgress = 2;
			else
			{
				if (goTo(getJobFacility())) aiProgress = 3;
				else setPenalty(3600);
			}
			break;

		case 1:	//�؍ނ������Ă���
			f = searchItem(Wood);
			if (f == NULL) setPenalty(3600);
			else
			{
				goTo(f);
				aiProgress = 0;
			}
			break;

		case 2:
			f = searchItem(Rice);
			if (f == NULL) setPenalty(3600);
			else
			{
				goTo(f);
				aiProgress = 0;
			}
			break;

		case 3:
			goRoomRandom();
			aiProgress = 5;
			break;
		case 5:
			Timer1 = 60;
			aiProgress = 4;
			break;
		case 4:
			produceItem(Sake, 1);
			addItem(Wood, -1);
			addItem(Rice, -1);
			setStatus(DoNothing);
			break;
		default: Println(L"WAB2 Progress Error"); setPenalty(3600); break;
		}
		break;
	}

	default:
		Println(L"UnitAI Not Found Error"); setPenalty(3600);
		break;
	}
}