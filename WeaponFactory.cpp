#include "WeaponFactory.h"

WeaponFactory * WeaponFactory::instance = nullptr;

void WeaponFactory::createWeapons(BulletFactory * bulletFactory)
{
	weaponTypes.clear();
	weapons.clear();
	this->addWeapon(WeaponType::SHORT, Weapon(S_FOV, S_RANGE, S_DMG, S_FIRE_RATE, BulletType::SHORT, bulletFactory));
	this->addWeapon(WeaponType::LONG, Weapon(L_FOV, L_RANGE, L_DMG, L_FIRE_RATE, BulletType::LONG, bulletFactory));
}

void WeaponFactory::addWeapon(WeaponType type, Weapon weapon)
{
	weaponTypes.push_back(type);
	weapons.push_back(weapon);
}

WeaponFactory::WeaponFactory()
{}

WeaponFactory * WeaponFactory::getInstance()
{
	if (instance == nullptr)
	{
		instance = new WeaponFactory();
	}
	return instance;
}

Weapon WeaponFactory::getNewWeapon(WeaponType weapon)
{
	for (int i = 0; i < weaponTypes.size(); i++)
	{
		if (weaponTypes[i] == weapon)
		{
			cout << i << endl;
			return weapons[i];
		}
	}
	return Weapon();
}