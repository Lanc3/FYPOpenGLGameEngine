#include "Profile.h"

Profile* Profile::mInstance = nullptr;

Profile* Profile::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = new Profile();
		mInstance->Init();
	}
	return mInstance;
}
Profile::Profile() {}
void Profile::Init()
{
	
	_file = new FILE();
	fopen_s(&_file, "ProfileData/Profile.json", "rb");
	char readBuffer[65536];
	rapidjson::FileReadStream _is(_file, readBuffer, sizeof(readBuffer));
	rapidjson::Document _document;
	_document.ParseStream(_is);
	fclose(_file);
	
	m_currentExp = _document["currentExp"].GetFloat();
	m_currentLevel = _document["currentLevel"].GetInt();
	m_nextLevel = _document["nextLevel"].GetInt();
	m_powerPoints = _document["powerPoints"].GetInt();
	m_SHPoints = _document["SHPoints"].GetInt();
	m_ARPoints = _document["ARPoints"].GetInt();
	m_HULPoints = _document["HULPoints"].GetInt();
	m_SDPoints = _document["SDPoints"].GetInt();
	m_LDPoints = _document["LDPoints"].GetInt();
	m_EnginePoints = _document["ULTPoints"].GetInt();
	m_killCount = _document["KillCount"].GetInt();

	Update();
	Save();
	fopen_s(&_file, "ProfileData/Profile.json", "rb");
	_document.ParseStream(_is);
	fclose(_file);
	m_nextLevelExp = _document["nextLevelExp"].GetFloat();
	Save();
}

void Profile::CalculateAchevements()
{
	if (m_killCount >= 10)
	{
		TEN_KILLS = true;
	}
	if (m_killCount >= 100)
	{
		HUNDREAD_KILLS = true;
	}
	if (m_killCount >= 1000)
	{
		THOUSAND_KILLS = true;
	}
	if (m_killCount >= 100000)
	{
		TEN_THOUSAND_KILL = true;
	}
	if (m_killCount >= 100000)
	{
		MILLION_KILLS = true;
	}
	
}

int Profile::GetEnemyCount()
{
	return m_expectedEnemyAmount;
}

int Profile::GetLongDMG()
{
	return m_shipLongDMG;
}

int Profile::GetSortDMG()
{
	return m_shipShortDMG;
}


Profile::~Profile()
{
	delete mInstance;
	mInstance = nullptr;
}

void Profile::Update()
{
	m_nextLevel = m_currentLevel + 1;
	int points = floor(m_nextLevel + 300 * pow(2, m_nextLevel / 7.0f));
	m_nextLevelExp = floor(points / 4);

	if (m_currentExp >= m_nextLevelExp)
	{
		m_currentLevel++;
		m_powerPoints += 3;
	}
	CalculateAchevements();
	CalculateShipStats();
}
void Profile::CalculateShipStats()
{
	m_shipShieldAmount = 90 + (m_shipShieldScaleAmount * m_SHPoints);
	m_shipHullAmount = 90 + (m_shipHullScaleAmount * m_HULPoints);
	m_shipLongDMG = 30 + (m_shipLongDMGScaleAmount * m_LDPoints);
	m_shipShortDMG = 5 + (m_shipShortDMGScaleAmount * m_SDPoints);
	m_shipEngineSpeed = 10 + (5 * m_EnginePoints);
	m_expectedEnemyAmount = m_currentLevel * m_enemyAmountScale;
}
void Profile::AddExp(int exp)
{
	m_currentExp += exp;
	//save to file
	Save();
}

void Profile::AddKill()
{
	m_killCount++;
}

void Profile::Save()
{
	std::ofstream myfile;
	myfile.open("ProfileData/Profile.json");
	std::string s = "{ \"currentExp\":" + to_string(m_currentExp) +
		",\n \"nextLevelExp\":" + to_string(m_nextLevelExp) +
		",\n \"currentLevel\" : " + to_string(m_currentLevel) +
		",\n \"nextLevel\" :" + to_string(m_nextLevel) +
		",\n \"powerPoints\" : " + to_string(m_powerPoints) +
		",\n \"SHPoints\" :" + to_string(m_SHPoints) +
		",\n \"ARPoints\" : " + to_string(m_ARPoints) +
		",\n \"HULPoints\" : " + to_string(m_HULPoints) +
		",\n \"SDPoints\" : " + to_string(m_SDPoints) +
		",\n \"LDPoints\" :" + to_string(m_LDPoints) +
		",\n \"ULTPoints\" : " + to_string(m_EnginePoints) +
		",\n \"KillCount\" : " + to_string(m_killCount) +
		"\n }";
	myfile << s;
	myfile.close();
}

int Profile::GetShipHullAmount()
{
	return m_shipHullAmount;
}
int Profile::GetShipShieldAmount()
{
	return m_shipShieldAmount;
}
int Profile::GetShipHEngineSpeedAmount()
{
	return m_shipEngineSpeed;
}

int Profile::GetPowerPoints()
{
	return m_powerPoints;
}

int Profile::GetShieldAmount()
{
	return m_SHPoints;
}

int Profile::GetArmorAmount()
{
	return m_ARPoints;
}

int Profile::GetHullAmount()
{
	return m_HULPoints;
}

int Profile::GetShortAmount()
{
	return m_SDPoints;
}

int Profile::GetLongAmopunt()
{
	return m_LDPoints;
}

int Profile::GetUltAmount()
{
	return m_EnginePoints;
}

int Profile::GetLevel()
{
	return m_currentLevel;
}

bool Profile::GetAchievements(string name)
{
	if (name == "10Kills")
	{
		return TEN_KILLS;
	}
	else if (name == "100Kills")
	{
		return HUNDREAD_KILLS;
	}
	else if (name == "1KKills")
	{
		return THOUSAND_KILLS;
	}
	else if (name == "1MKills")
	{
		return MILLION_KILLS;
	}
	else if (name == "maxLevel")
	{
		return MAX_LEVEL;
	}
	else
		return false;
}

void Profile::SetShieldAmount(int v)
{
	m_SHPoints = v;
}

void Profile::SetArmorAmount(int v)
{
	m_ARPoints = v;
}

void Profile::SetHullAmount(int v)
{
	m_HULPoints = v;
}

void Profile::SetShortAmount(int v)
{
	m_SDPoints = v;
}

void Profile::SetLongAmopunt(int v)
{
	m_LDPoints = v;
}

void Profile::SetEngineSpeedAmount(int v)
{
	m_EnginePoints = v;
}

void Profile::SetPPAmount(int v)
{
	m_powerPoints = v;
}
