#pragma once
#include <iostream> 
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "boost/filesystem.hpp"
#include <boost/exception/all.hpp>

#define UMS_CCF_FILE "/DATA/UMS/CoreConfiguration.json"
#define DEFAULT_CYCLE_USER_RUN_FLAG false
#define DEFAULT_CYCLE_PERIOD_SECOND 3
#define DEFAULT_CYCLE_TOTAL_MINUTE 1

class CoreConfiguration
{
private:
	// Empty 
public:
	CoreConfiguration();
	void CCF_Read();
	int CyclePeriod_Second;
	int CycleTotal_Minutes;
};

