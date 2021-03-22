#pragma once

#include <iostream>
#include<string> 
#include <boost/filesystem.hpp>
#include <boost/exception/all.hpp>

class environment
{
private:
	// 
public:
	// default constructor
	environment();	
	std::string hdc2010_path, bmp280_path, opt3001_path;

	std::string get_path(std::string sysfs_name);
	std::string read_sysfs(std::string sysfs_name);

	std::string temperature();
	std::string humidity();
	std::string ambient_light();
	std::string pressure();

	void collect_data_second(int period_second, int length_minute, bool stop_flag);
};

