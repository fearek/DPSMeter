#pragma once
#include "pch.h"

#include <vector>
#include <unordered_map>
#include ".\FlatBuffers\include\STRUCT_.h"

#define FLATBUFFERUTIL FlatBufferUtil::getInstance()

using namespace SoulMeterFBS::History;

class FlatBufferUtil : public Singleton<FlatBufferUtil> {

public:

	void tIntDoubleListConverter(flatbuffers::FlatBufferBuilder& fbb, std::vector<flatbuffers::Offset<_tIntDoubleList>>& vIntdouble, std::unordered_map<uint32_t, std::vector<double>>& m)
	{
		for (auto itr = m.begin(); itr != m.end(); itr++) 
		{
			auto fcvS = fbb.CreateVector(itr->second);

			_tIntDoubleListBuilder tidlb(fbb);

			tidlb.add__f(itr->first);
			tidlb.add__s(fcvS);
			
			vIntdouble.push_back(tidlb.Finish());
		}
	}

	void tIntdoubleListReverser(const _tIntDoubleList* tIntdoubleList, std::unordered_map<uint32_t, std::vector<double>>& m)
	{
		std::vector<double> vTmp;

		for (auto itr = tIntdoubleList->_s()->begin(); itr != tIntdoubleList->_s()->end(); itr++)
			vTmp.push_back(*itr);

		m[tIntdoubleList->_f()] = vTmp;
	}

	void fbvdoubleReverser(const flatbuffers::Vector<double>* fbvdouble, std::vector<double>& vdouble)
	{
		for (auto itr = fbvdouble->begin(); itr != fbvdouble->end(); itr++)
			vdouble.push_back(*itr);
	}
};