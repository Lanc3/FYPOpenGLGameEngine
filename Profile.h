#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "rapidjson\rapidjson.h"
#include "rapidjson\filereadstream.h"
#include "rapidjson\reader.h"
#include "rapidjson\filewritestream.h"
#include "rapidjson\document.h"
#include "rapidjson\writer.h"
#include <cstdio>
#include <iostream>
#include <fstream>

using namespace rapidjson;
using namespace std;

class Profile
{
public:
	static Profile * GetInstance();
	
	Profile();
	~Profile();
	void Update();
	void CalculateShipStats();
	void AddExp(int exp);
	void AddKill();
	void Save();
	int GetShipHullAmount();
	int GetShipShieldAmount();
	int GetShipHEngineSpeedAmount();
	int GetPowerPoints();
	int GetShieldAmount();
	int GetArmorAmount();
	int GetHullAmount();
	int GetShortAmount();
	int GetLongAmopunt();
	int GetUltAmount();
	int GetLevel();
	bool GetAchievements(string name);

	void SetShieldAmount(int v);
	void SetArmorAmount(int v);
	void SetHullAmount(int v);
	void SetShortAmount(int v);
	void SetLongAmopunt(int v);
	void SetEngineSpeedAmount(int v);
	void SetPPAmount(int v);
	int GetEnemyCount();

	int GetLongDMG();

	int GetSortDMG();

private:
	void Init();
	int m_nextLevel, m_currentLevel,m_powerPoints,m_SHPoints,m_ARPoints,m_HULPoints,m_SDPoints,m_LDPoints,m_EnginePoints;
	float m_nextLevelExp, m_currentExp;
	FILE* _file;
	static Profile* mInstance;
	int m_killCount;
	int m_damageTaken;
	void CalculateAchevements();
	
	bool MAX_LEVEL = false,TEN_KILLS = false, HUNDREAD_KILLS = false,TEN_THOUSAND_KILL = false, THOUSAND_KILLS = false, MILLION_KILLS = false, MILLION_DMG_TAKEN = false;
	int m_expectedEnemyAmount = 0;
	int m_enemyAmountScale = 5;
	int m_shipShieldAmount = 100, m_shipHullAmount = 100, m_shipShortDMG = 10, m_shipLongDMG = 50, m_shipEngineSpeed = 200;
	int m_shipShortDMGScaleAmount = 5, m_shipLongDMGScaleAmount = 20, m_shipShieldScaleAmount = 10, m_shipHullScaleAmount = 15;
};

