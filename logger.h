#pragma once

#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

// For boost filesystem and date time
#include <boost/filesystem.hpp>
#include <boost/exception/all.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <sstream>


// For date & time
#include <iostream>
#include <chrono>
#include <ctime>


void logger_init();


std::string get_timestamp_fname();


boost::filesystem::path get_parent_path();
boost::filesystem::path get_sys_log_path();
boost::filesystem::path get_data_log_path();
boost::filesystem::path get_ums_path();

void logger_enable(std::string log_file_name, std::string strLoggerName);
bool logger_copyDir(boost::filesystem::path const& source, boost::filesystem::path const& destination);

void logger_log_info(std::string info_message);
void logger_log_warn(std::string warn_message);
void logger_log_error(std::string error_message);

