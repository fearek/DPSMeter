#pragma once
#include "pch.h"
#include ".\Third Party\FlatBuffers\include\SW_HISTORY_.h"
#include ".\Damage Meter\History.h"

using namespace SoulMeterFBS::History;

#define SAVEDATA SWSaveData::getInstance()

#ifdef _DEBUG
#define DEBUG_SAVEDATA_SAVE 0
#define DEBUG_SAVEDATA_DELETE 0
#endif

// XOR( [Loop [[History Size]-[History Data]]  ] )
class SWSaveData : public Singleton<SWSaveData> {

private:
	const uint32_t _saveVersion = 1;
	const std::string _oriSaveFileName = "SoulMeter.dat";
	std::string _saveFileName;
	std::fstream _saveFile;

	bool _fileNotExist = false;
	bool _inited = false;

	bool Load();
	void Crypt(unsigned char* src, unsigned char* dest, int64_t len);

	void ReadSaveData(int64_t& offset);

	void WriteData(unsigned char* buf, int64_t size, std::fstream* pFS = nullptr);
	void ReadData(unsigned char* buf, int64_t size, int64_t offset);
	int64_t GetNextSaveDataLength(int64_t& offset);

	std::mutex _mutex;

public:
	~SWSaveData();

	DWORD Init(std::string fileName = "");
	int64_t GetCurrentLength();
	void Save(flatbuffers::FlatBufferBuilder& fbb);
	void Delete(int64_t index, int64_t clearCount = -1);
	void Clone(std::string filename);
	void Reset();

	void GetLock()
	{
		_mutex.lock();
	}
	void FreeLock()
	{
		_mutex.unlock();
	}

	const std::string CurrentSaveDataPath()
	{
		return _saveFileName;
	}
};