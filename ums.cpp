#include "ums.h"


ums::ums()
{
	
	// Empty default constructor
}

bool ums::init()
{
	if (ums::isRecognized()) {
		if (ums::_mount()) {
			logger_log_info("UMS is mounted.");
		}
		else {
			logger_log_error("Failed to mount UMS.");
		}
	}
	else {
		logger_log_error("Failed to recognize UMS.");
	}
	return (status == mounted);
}

bool ums::isRecognized() 
{
	std::string log_buff;
	try {
		if (boost::filesystem::exists(boost::filesystem::path(UMS_DEV))) {
			status = recognized;
		}
		else {
			status = not_recognized;
		}
		return (status == recognized);
	}
	catch (boost::exception& e) {
		logger_log_error("Error recognizing UMS " + boost::diagnostic_information(e));
	}
	catch (std::exception& e) {
		logger_log_error("Error recognizing UMS " + std::string(e.what()));
	}
	return true;
}

bool ums::_mount()
{
	char cmd[256];
	try {
		if (isRecognized()) {
			status = unmounted;
			sprintf(cmd, "mountpoint -q %s", UMS_MOUNT_POINT);
			if (0 == system(cmd)) {
				// Already mounted
				status = mounted;
			}
			else {
				// Not already mounted, try to mount
				sprintf(cmd, "mount %s %s", UMS_DEV, UMS_MOUNT_POINT);
				if (0 == system(cmd)) {
					// If successfully mounted
					status = mounted;
					sleep(2);
				}
			}
		}
	}
	catch (boost::exception& e) {
		logger_log_error("Error mounting UMS" + boost::diagnostic_information(e));
	}
	catch (std::exception& e) {
		logger_log_error("Error mounting UMS" + std::string(e.what()));
	}
	return (status == mounted);
}


bool ums::_unmount()
{
	char cmd[256];
	try {
		sprintf(cmd, "mountpoint -q %s", UMS_MOUNT_POINT);
		if (0 == system(cmd)) {
			// If mounted, unmount
			status = mounted;
			sprintf(cmd, "umount %s", UMS_MOUNT_POINT);
			if (0 == system(cmd)) {
				// If successfully mounted
				status = unmounted;
			}
		}
		else {
			// Not mounted
			status = unmounted;
		}

		return (status == unmounted);
	}
	catch (boost::exception& e) {
		logger_log_error("Error unmounting UMS" + boost::diagnostic_information(e));
	}
	catch (std::exception& e) {
		logger_log_error("Error unmounting UMS" + std::string(e.what()));
	}
	return (status == unmounted);
}

