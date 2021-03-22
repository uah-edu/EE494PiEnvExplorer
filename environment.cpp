#include "environment.h"
#include "logger.h"

/* Default constructor for GPIO
*/
environment::environment()
{
	// Get path to all sensor
	hdc2010_path = environment::get_path("hdc20x0");
	bmp280_path = environment::get_path("bmp280");
	opt3001_path = environment::get_path("opt3001");
}


/* Get path of sensor based on its name
*/
std::string environment::get_path(std::string sysfs_name)
{
	//std::string search_path = "/sys/bus/iio/devices/";
	boost::filesystem::path search_path("/sys/bus/iio/devices/");
	//boost::filesystem::directory_iterator it{ search_path };
	boost::filesystem::directory_iterator end_iter;
	for (boost::filesystem::directory_iterator dir_itr(search_path); dir_itr != end_iter; ++dir_itr) {
		try {
			if (boost::filesystem::is_directory(dir_itr->status())) {
				boost::filesystem::path fname_path (dir_itr->path().string() + "/name");
				
				std::ifstream ifs(fname_path.string());
				std::string search_name;
				std::getline(ifs, search_name);
				ifs.close();
				if (0 == sysfs_name.compare(search_name)) {
					return dir_itr->path().string();
				}
			}
		}
		catch (boost::exception& e) {
			std::cout << "Error getting path to environment sensor: " << boost::diagnostic_information(e);
		}
		catch (std::exception& e) {
			std::cout << "Error getting path to environment sensor: " << e.what();
		}
	}
}

/* Get path of sensor based on its name
*/
std::string environment::read_sysfs(std::string path)
{
	try {
		std::ifstream ifs(path);
		std::string data;
		std::getline(ifs, data);
		return data;
	}
	catch (std::exception& e) {
		std::cout << "Error reading sensor file: " << e.what();
	}
}

std::string environment::temperature()
{
	return read_sysfs(hdc2010_path + "/in_temp_input");
}

std::string environment::humidity()
{
	return read_sysfs(hdc2010_path + "/in_humidityrelative_input");
}

std::string environment::ambient_light()
{
	return read_sysfs(opt3001_path + "/in_illuminance_input");
}

std::string environment::pressure()
{
	return read_sysfs(bmp280_path + "/in_pressure_input");
}


void environment::collect_data_second(int period_second, int length_minute, bool stop_flag) {
	std::string data_set;

	logger_enable(get_data_log_path().string(), "file_logger");
	for (int i = 0; (i < 60 * length_minute / period_second) && (!stop_flag); i++) {
		data_set = temperature() + ", " + humidity() + ", " + ambient_light() + ", " + pressure();
		logger_log_info(data_set);
		sleep(period_second);
	}
	logger_enable(get_sys_log_path().string(), "file_logger");
}