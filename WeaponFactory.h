#pragma once
#include "Weapon.h"
#include <vector>
#include <iostream>
using namespace std;

enum class WeaponType { SHORT,LONG,ULT, NULL_WEAPON };

class WeaponFactory
{
public:
	static WeaponFactory * getInstance();
	Weapon getNewWeapon(WeaponType weapon);
	void addWeapon(WeaponType type, Weapon weapon);
	void createWeapons(BulletFactory * bulletFactory);
	float const pi = std::acos(-1);
private:
	std::vector<Weapon> weapons;
	std::vector<WeaponType> weaponTypes;
	BulletFactory * m_bulletFactory;
	float const S_DMG = 50;
	float const S_RANGE = 700;
	float const S_FOV = PI / 18;
	float S_FIRE_RATE = 25;

	float L_DMG = 100;
	float L_RANGE = 1700;
	float L_FOV = PI / 36;
	float L_FIRE_RATE = 2;
	/*
	float const U_DMG;
	float const U_RANGE;
	float const U_FOV;
	float const U_FIRE_RATE;*/
protected:
	WeaponFactory();
	static WeaponFactory * instance;
};
