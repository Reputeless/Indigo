#include"Unit.h"
#include"Header.h"

String Unit::getMessage()
{
	switch (Status)
	{
	case DoNothing:		return L"�������Ă��Ȃ�";
	case IsSleeping:	return L"�Q�Ă�";
	case TakeMeal:		return L"�H����...";
	case GoToSleep:		return L"�Q�ɍs��";
	case WorkAsBuilder:
		break;
	case WorkAsFarmer:
		break;
	case WorkAsWoodcutter:
		break;
	case WorkAsBrewer:
		break;
	default:
		break;
	}
	/*
	switch (Status)
	{
	case DoNothing:		return L"�������ĂȂ�";
	case RestInHouse:	return L"�Ƃŋx��ł�";
	case EatBread:		return L"�p���H�ׂĂ�";
	case BakeBread:		return L"�p�����Ă��Ă�";
	case TakeWheat:		return L"���������ɍs��";
	case TakeWood:		return L"�؍ނ����ɍs��";
	case TakeBread:		return L"�p�������ɍs��";
	case TakeVenion:	return L"���������ɍs��";
	case TakeLeather:	return L"�є�����ɍs��";
	case WaitForWheat:	return L"�����̓��ב҂�";
	case WaitForWood:	return L"�؍ނ̓��ב҂�";
	case WaitForBread:	return L"�p���̓��ב҂�";
	case WaitForVenion:	return L"�����̓��ב҂�";
	case WaitForLeather:return L"�є�̓��ב҂�";
	case CantGoToJobHouse:return L"�d����ɍs���Ȃ�";
	case CantGoToHome:	return L"�Ƃɍs���Ȃ�";
	case CantGoToMarket:return L"�s����s�ꂪ�Ȃ�";
	case CantGoToForest:return L"�X�ւ̓����Ȃ�";
	case NoRoomForBread:return L"�p���̒u���ꂪ�Ȃ�";
	case SendItemToMarket:return L"�s��ɗa���ɍs��";
	case IsSleeping:	return L"���[�A���[";
	case GoToHome:		return L"�Ƃɍs��";
	case GoToJobHouse:	return L"�d����ɍs��";
	case GoToMarket:	return L"�s��ɍs��";
	case GoToForest:	return L"�X�тɍs��";
	case GoToPlannedSite:return L"���ݗ\��n�ɍs��";
	case TakeRest:		return L"�x�e��...";
	case NoHome:		return L"�Ƃ��Ȃ��I";
	case NoJobHouse:	return L"�d���ꂪ�Ȃ��I";
	case NoForest:		return L"�X�т��Ȃ��I";
	case NoPlannedSite: return L"���ݗ\��n���Ȃ��I";
	case ReapWheat:		return L"���������n��...";
	case PileUp:		return L"���ݒ�...";
	case CutTree:		return L"���̒�...";
	case Hunting:		return L"���...";
	case Brewing:		return L"������...";
	case NoRoomForSake: return L"���̒u���ꂪ�Ȃ��I";
	default:			return L"���b�Z�[�W�Ȃ�";
	}*/
	return L"Nothing";
}