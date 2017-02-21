#pragma once
#include<Siv3D.hpp>
#include"Items.h"

class Chip;
class Unit;
class Place;
class PlacePointer;

#define RoadColor Palette::Khaki
#define PlainsColor Palette::Green
#define OceanColor Palette::Blue
#define ChipImageSize	64	//�`�b�v�摜�̑傫��
#define ChipXMax 2048	//�`�b�v�̕ۏ؂���ő�l
#define ChipYMax 2048	//�`�b�v�̕ۏ؂���ő�l

//�O���[�o���֐�
void drawAll();
void InitAll();
bool SetVillage(const Point& _pos);
extern bool destroyPlaceMode;
extern bool destroyRoadMode;
extern bool makingHouseMode;
extern bool settingRoadMode;
extern Place makingHouseP;
extern Chip* previousSelectedChip;
extern bool mouseOverInterface;
extern Texture mapTexture;

//�O���[�o���^�C�}
extern double sec;

//Interface
void UpdateInterface();	//draw�����˂�

#define PlaceMax 10000
extern Place places[PlaceMax];
enum PType
{
	House,
	Market,
	Farm,
};
class Place : Items
{
public:
	Place() { reset(); }
	void	Place::erase();
	Color	Place::getDrawColor() const;
	String	Place::getNameAsString() const;
	Point	Place::getSize() const;
	Point	Place::getEntrancePos() const;
	Rect	Place::getDrawRect() const { return Rect(pos*ChipImageSize, getSize()*ChipImageSize); }
	void	Place::drawFloor(const int& _type = 0) const;	//�����A_type==1�Ȃ�ΐԕ\��
	void	Place::drawName() const;
	void	Place::reset();
	void	Place::set(const int& _r, const Point& _pos, const PType& _t);

public:

	int		Place::r;		//����
	bool	Place::enabled;
	PType	Place::type;	//�����̃^�C�v
	Items	Place::item;
	Point	Place::pos;		//�����̍���̈ʒu

	int		Place::THIS;
};
bool setPlace(const int& _r, const Point& _pos, const PType& _t);
extern Place* selectedPlace;
bool canSetPlace(const int& _r, const Point& _pos, const PType& _t);

class PlacePointer
{
public:
	Place* getPlace() const
	{
		if (place == 0) return NULL;
		else return &places[place - 1];
	}
	void setPlace(const Place* _r)
	{
		if (_r == NULL) place = 0;
		else place = _r->THIS + 1;
	}
protected:
	int	place;
};

extern Chip* temp[1000000];
extern Chip chips[ChipXMax][ChipYMax];
extern int chipX;
extern int chipY;
extern Chip* nowSelectedChip;
extern Chip* newnowSelectedChip;
class Chip : public PlacePointer
{
public:
	void	Chip::reset();
	void	Chip::drawGround();	//�n�ʂ̕`��
	Chip&	Chip::getNearChip(const int& _r);
	Rect	Chip::getDrawRect() const { return Rect(THIS*ChipImageSize, Point(ChipImageSize, ChipImageSize)); }
	bool	Chip::canSetRoad() const { return isLand && getPlace() == NULL; }

public:
	bool	Chip::isRoad;
	bool	Chip::isLand;

	int		Chip::number;	//�ėp		�ʏ펞0�ł��邱�Ƃ�ۏ؂���
	int		Chip::ang;		//�ėpAng	�ʏ펞0�ł��邱�Ƃ�ۏ؂��Ȃ�
	bool	Chip::flag;		//�ėp�t���O�ʏ펞false�ł��邱�Ƃ�ۏ؂���

	Point	Chip::THIS;
};
Chip& getChip(const Point& _pos);
Chip& getChip(const int& _x, const int& _y);
extern Image mapImage;
bool isConnectedByLand(const Point& _posA, const Point& _posB);
bool isConnectedByRoad(const Point& _posA, const Point& _posB);
void setRoadAToB(const Point& _posA, const Point& _posB);
void drawPlannedRoadAToB(const Point& _posA, const Point& _posB);
void resetTemp();

#define UNIT_MAX 10000
class Unit
{
public:
	void reset();

	Items	items;
	int		timerNow;	//�ėp�^�C�}
	int		timerMax;	//�ėp�^�C�}
	Point	pos;		//�������W	Chip�Ɋ�Â�
	Vec2	addPos;		//�ǉ����W�B����������A�ړ�����\��

	int		THIS;
};
extern Unit units[UNIT_MAX];