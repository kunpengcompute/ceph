#ifndef HI_CORE_UTIL_H
#define HI_CORE_UTIL_H

#include <cstdint>
#include <map>
#include <vector>
#include <set>
#include <boost/tuple/tuple.hpp>

int HiInit(const std::string &paramFilePath, const std::string &osdNum);

void HiFinish();

bool HiSetWriteSection(const uint64_t offset, const uint64_t len, const uint64_t csize, uint64_t &headStart,
    uint64_t &headLength);

bool HiRebuildToread(const std::map<uint64_t, uint64_t> &writeSet, uint64_t csize,
     std::map<uint64_t, uint64_t> &toRead);

struct HiEcInfo{
	size_t dataCnt;
	size_t chunkCnt;
	const std::vector<int> &cMapping;
	uint64_t cSize;
	uint64_t sWidth;

	HiEcInfo (size_t k, size_t km, const std::vector<int> &chunkMapping, uint64_t chunkSize, uint64_t striprWidth)
		: dataCnt(k), chunkCnt(km), cMapping(chunkMapping), cSize(chunkSize), sWidth(stripeWidth)
	{}

};

void HiGetRelatedShards(const std::pair<uint64_t,uint64_t> &rRange,const HiEcInfo &ecInfo,std::set<int> &out);

void HiGetShardsRangeToRead(const std::pair<uint64_t,uint64_t> &rRange,const HiEcInfo &ecInfo,
			std::map<int , std::set<pair<uint64_t, uint64_t>>> &wants);

void HiGetWriteToShards(const std::map<uint64_t,uint64_t> &toWriteChunkAlign,const HiEcInfo &ecInfo,
		std::set<int> &wantToWrite);

void HiGetReconstructShards(const unsigned int start,const unsigned int count,const uint64_t len,
	       	const HiEcInfo &ecInfo,std::vector<int> &shardID);

void HiReconstructPrepare(const HiEcInfo &ecInfo, const std::pair<uint64_t,uint64_t> &rRange,
		std::vector<boost::tuple<unsigned int , unsigned int , unsigned int>> &cInfo);

#endif











