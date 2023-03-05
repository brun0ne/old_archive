#pragma once
class Stats
{
public:
	Stats(int HP, int strengh, int defence);

	int HP = 100;
	int strengh = 5;
	int defence = 5;

	~Stats() = default;
};

