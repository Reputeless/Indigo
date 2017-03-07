#pragma once
#define ITEM_MAX 10

/*
Items�N���X���ۏ؂��邱��
�E����ID��Item�������̏ꏊ�ɑ��݂��Ȃ�
�EItem���͕��ɂȂ�Ȃ�
*/
class Items
{
public:
	int		getNumItem(const int& _id) const
	{
		for (int i = 0; i < ITEM_MAX; i++)
			if (amount[i] != 0 && id[i] == _id)
				return amount[i];
		return 0;
	}
	int		getNumAllItem() const
	{
		int num = 0;
		for (int i = 0; i < ITEM_MAX; i++)
			if (amount[i] != 0)
				num += amount[i];
		return num;
	}
	int		addItem(const int& _id, const int& _amount)		//�l�͏o������
	{
		int max = maxSize - getNumAllItem();
		if (max > _amount) max = _amount;
		if (max == 0) return 0;

		for (int i = 0; i < ITEM_MAX; i++)
		{
			if (amount[i] != 0 && id[i] == _id)
			{
				amount[i] += max;
				return max;
			}
		}
		for (int i = 0; i < ITEM_MAX; i++)
		{
			if (amount[i] == 0)
			{
				id[i] = _id;
				amount[i] = max;
				return max;
			}
		}
		return 0;
	}
	int		pullItem(const int& _id, const int& _amount)	//�l�͏o������
	{
		int max = getNumItem(_id);
		if (max > _amount) max = _amount;
		if (max == 0) return 0;

		for (int i = 0; i < ITEM_MAX; i++)
		{
			if (amount[i] != 0 && id[i] == _id)
			{
				amount[i] -= max;
				return max;
			}
		}
		return 0;
	}

	void reset(const int& _maxSize = 0)
	{
		for (auto& a : amount) a = 0;
		for (auto& i : id) i = 0;
		maxSize = _maxSize;
	}
private:
	int		amount[ITEM_MAX];
	int		id[ITEM_MAX];
	int		maxSize;	//�ۑ��ł���ő�e��
};