#include "logger.h"

std::string timestamp_str = get_timestamp_fname();

boost::filesystem::path parent_path;
boost::filesystem::path system_log_path;
boost::filesystem::path data_log_path;
boost::filesystem::path ums_path = boost::filesystem::path("/DATA/UMS/CycleLog_" + timestamp_str);
/* logger init
*  Create a parent directory: /DATA/CycleLog_Timestamp with two file 
*									system.csv 
*									data.csv 
*/
void logger_init() {
	parent_path = "/DATA/CycleLog_" + timestamp_str;
	system_log_path = parent_path / "system.csv";
	data_log_path = parent_path / "data.csv";
	// Create a parent directory
	try {
		if (!boost::filesystem::exists(parent_path)) {
			boost::filesystem::create_directory(parent_path);
		}

		// Create a system.csv file in the parent directory
		std::ofstream system_log_ofs(system_log_path.generic_string());
		system_log_ofs.close();

		// Create a data.csv file in the parent directory
		std::ofstream data_log_ofs(data_log_path.generic_string());
		//data_log_ofs << "Date, Time, Temperature(C), Huminity(%), Ambient Light(lux), Pressure(Pa)\n";
		data_log_ofs.close();
	}
	catch (boost::exception& e) {
		std::cout << "Error initializing logger library: " << boost::diagnostic_information(e);
	}
	catch (std::exception& e) {
		std::cout << "Error initializing logger library: " << e.what();
	}
}


/* logger enable
*  Enable logging to log_file_name
*/
void logger_enable(std::string log_file_name, std::string strLoggerName = "file_logger") {
	if (0 == get_data_log_path().string().compare(log_file_name)) {
		auto defaultLogger = spdlog::get(strLoggerName);
		if (defaultLogger != nullptr) {
			spdlog::drop(strLoggerName);
		}

		std::vector<spdlog::sink_ptr> sinks;
		sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_file_name));
		auto logger = std::make_shared<spdlog::logger>(strLoggerName,
			std::begin(sinks),
			std::end(sinks));
		spdlog::register_logger(logger);
		spdlog::set_level(spdlog::level::trace);
		spdlog::set_default_logger(logger);
		spdlog::set_pattern("%Y-%m-%d, %T, %v");
		spdlog::flush_every(std::chrono::seconds(3));
	}
	else {
		auto defaultLogger = spdlog::get(strLoggerName);
		if (defaultLogger != nullptr) {
			spdlog::drop(strLoggerName);
		}

		std::vector<spdlog::sink_ptr> sinks;
		sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_file_name));
		auto logger = std::make_shared<spdlog::logger>(strLoggerName,
			std::begin(sinks),
			std::end(sinks));
		spdlog::register_logger(logger);
		spdlog::set_level(spdlog::level::trace);
		spdlog::set_default_logger(logger);
		spdlog::set_pattern("%Y-%m-%d, %T, %l, \t%v");
		spdlog::flush_every(std::chrono::seconds(3));
	}
}



/* logger_copyDir()
*  Recursively copy directory
*/
bool logger_copyDir(boost::filesystem::path const &source, boost::filesystem::path const&destination) {
	// Check whether the function call is valid
	try {
		if (!boost::filesystem::exists(source) || !boost::filesystem::is_directory(source)) {
			std::cerr << "Source directory " << source.string()
				<< " does not exist or is not a directory." << '\n';
			return false;
		}
		if (boost::filesystem::exists(destination)) {
			std::cerr << "Destination directory " << destination.string()
				<< " already exists." << '\n'
				;
			return false;
		}
		// Create the destination directory
		if (!boost::filesystem::create_directory(destination)) {
			std::cerr << "Unable to create destination directory"
				<< destination.string() << '\n';
			return false;
		}
	}
	catch (boost::filesystem::filesystem_error const& e) {
		std::cerr << e.what() << '\n';
		return false;
	}
	
	// Iterate through the source directory
	for (boost::filesystem::directory_iterator file(source); file != boost::filesystem::directory_iterator(); ++file) {
		try {
			boost::filesystem::path current(file->path());
			if (boost::filesystem::is_directory(current)) {
				// Found directory: Recursion
				if (!logger_copyDir(current, destination / current.filename())) {
					return false;
				}
			}
			else {
				// Found file: Copy
				boost::filesystem::copy_file(current,destination / current.filename());
			}
		}
		catch (boost::filesystem::filesystem_error const& e) {
			std::cerr << e.what() << '\n';
		}
	}
	return true;
}



void logger_log_info(std::string info_message) {
	spdlog::info(info_message);
}

void logger_log_warn(std::string warn_message) {
	spdlog::warn(warn_message);
}

void logger_log_error(std::string error_message) {
	spdlog::error(error_message);
}



/* get_timestamp_fname()
*  format YYYYMMDD_HHMMSS
*/
std::string get_timestamp_fname() {
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	char timestamp[30];
	std::strftime(timestamp, 30, "%Y%m%d_%H%M%S", std::localtime(&now));
	return std::string(timestamp);
}


boost::filesystem::path get_parent_path() {
	return parent_path;
}

boost::filesystem::path get_sys_log_path() {
	return system_log_path;
}

boost::filesystem::path get_data_log_path() {
	return data_log_path;
}

boost::filesystem::path get_ums_path() {
	return ums_path;
}