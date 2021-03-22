#pragma once

#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/exception/all.hpp>

#include "logger.h"

#define UMS_DEV "/dev/sda1"
#define UMS_MOUNT_POINT "/DATA/UMS"
#define UMS_TYPE "vfat"

enum ums_mount_status { not_recognized, recognized, unmounted, mounted };

class ums
{
private:
	//
public:
	// Default constructor
	ums();
	bool init();
	bool isRecognized();
	bool _mount();
	bool _unmount();
	ums_mount_status status = not_recognized;
	std::string ums_mount_point_str = UMS_MOUNT_POINT;;
};

