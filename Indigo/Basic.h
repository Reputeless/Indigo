#pragma once
#include<Siv3D.hpp>
#include"Items.h"

class Chip;
class Unit;
class Place;
class PPointer;

#define RoadColor Palette::Khaki
#define PlainsColor Palette::Green
#define OceanColor Palette::Blue
#define ChipImageSize	64	//�`�b�v�摜�̑傫��
#define RoadWidth		45.2
#define ChipXMax 2048	//�`�b�v�̕ۏ؂���ő�l
#define ChipYMax 2048	//�`�b�v�̕ۏ؂���ő�l

//�O���[�o���֐�
void updateAll();
void drawAll();
void InitAll();
bool SetVillage(const Point& _pos);
extern bool setupByPOMS();
enum IMode
{
	None,
	DestroyPlaceMode,
	DestroyRoadMode,
	MakingVillageMode,
	MakingHouseMode,
	SettingRoadMode,
	UnitFallDownMode,
};
extern IMode iMode;
extern Vec2 mousePosAsGlobalVec2;
extern Place makingHouseP;
extern Chip* previousSelectedChip;
extern Unit* selectedUnit;
extern bool mouseOverInterface;
extern Texture mapTexture;

//�O���[�o���^�C�}
extern double sec;

//Interface
void UpdateInterface();	//draw�����˂�

struct PlaceData
{
	PlaceData(const int& _type)
	{
		CSVReader reader(L"Data/PlaceData.csv");
		name = reader.getOr<String>(_type, 1, String());
		size = reader.getOr<Point>(_type, 2, Point(0, 0));
		entraceY = reader.getOr<int>(_type, 3, 0);
		color = reader.getOr<Color>(_type, 4, Color(0, 0, 0, 255));
		capacityMax = reader.getOr<int>(_type, 5, 0);
	}
	String	name;
	Point	size;
	int		entraceY;
	Color	color;
	int		capacityMax;
};
extern Array<PlaceData> placeData;

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
	void	Place::drawFrame(const int& _type = 0) const;	//�����A_type==1�Ȃ�ΐԕ\��
	void	Place::drawName(const int& _type = 0) const;
	void	Place::reset();
	void	Place::set(const int& _r, const Point& _pos, const PType& _t);
	int		Place::getCapacityMax() const;
public:

	int		Place::capacity;
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

class PPointer
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
class Chip : public PPointer
{
public:
	void	Chip::reset();
	void	Chip::drawGround();
	void	Chip::drawRoad(const Color& _color, const double& _width);
	Chip&	Chip::getNearChip(const int& _r);
	Rect	Chip::getDrawRect() const { return Rect(THIS*ChipImageSize, Point(ChipImageSize, ChipImageSize)); }
	bool	Chip::canSetRoad() const { return isLand && (getPlace() == NULL || isRoad); }
	Vec2	Chip::getGlobalPos() const { return Vec2(THIS*ChipImageSize).movedBy(ChipImageSize / 2, ChipImageSize / 2); }
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

#define UnitMax 10000
#define UnitRootMax 100
class Unit
{
public:
	void	Unit::reset();
	bool	Unit::set(const Vec2& _globalPos);
	void	Unit::drawBody() const;
	void	Unit::update(const int& _actionPoint);
	bool	Unit::searchAndSetHome();
	bool	Unit::searchAndSetWorkplace();
	bool	Unit::goTo(const Point& _pos);
	Vec2	Unit::getRealPos() const;
public:
	Point	Unit::tarPos;
	PPointer Unit::home;
	PPointer Unit::workplace;
	PPointer Unit::targetPlace;
	int		Unit::rootNow;
	int		Unit::rootMax;
	double	Unit::rootTimer[UnitRootMax];
	Vec2	Unit::rootAng[UnitRootMax];
	bool	Unit::enabled;
	String	Unit::message;
	Items	Unit::items;
	bool	Unit::isInPlace;
	bool	Unit::isMoving;
	double	Unit::movingSpeed;
	Vec2	Unit::movingAng;
	int		Unit::timerNow;	//�ėp�^�C�}
	int		Unit::timerMax;	//�ėp�^�C�}
	Point	Unit::pos;		//�������W	Chip�Ɋ�Â�
	Vec2	Unit::addPos;		//�ǉ����W�B����������A�ړ�����\��

	int		Unit::THIS;
};
extern Unit units[UnitMax];