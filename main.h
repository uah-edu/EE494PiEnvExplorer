#include <iostream>
#include <thread>
#include <atomic>

#include "gpio.h"
#include "logger.h"
#include "ums.h"
#include "environment.h"
#include "CoreConfiguration.h"

//#define BOOST_LOG_DYN_LINK 1
//
//#include <boost/log/core.hpp>
//#include <boost/log/trivial.hpp>
//#include <boost/log/expressions.hpp>
//#include <boost/log/sinks/text_file_backend.hpp>
//#include <boost/log/utility/setup/file.hpp>
//#include <boost/log/utility/setup/common_attributes.hpp>
//#include <boost/log/sources/severity_logger.hpp>
//#include <boost/log/sources/record_ostream.hpp>
//#include <boost/log/sources/severity_feature.hpp>
