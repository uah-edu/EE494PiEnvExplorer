#include "main.h"

#define RUNNING 1
#define STOPPING 0

#define SYSTEM_INIT 1
#define SYSTEM_START 2
#define SYSTEM_END 10

void system_init();
void system_ending();

bool system_running_flag = RUNNING;
int system_stage = SYSTEM_INIT;


LED LED1(LED1_PIN);
BUTTON SW1(SW1_PIN);
ums env_ums;
environment env_sensor;
CoreConfiguration ccf;

int main() {
	/* INIT SYSTEM
	*  LED blinks (T=200ms) -> initializing system...
	*  Create a folder "/DATA/CycleLog_Timestamp" with two file "system.csv" and "data.csv"
	*  Initialize the UMS
	*  Sleep system for 3 second
	*  LED is OFF -> system is successfully initialized.
	* */
	logger_init();
	logger_enable(get_sys_log_path().string(), "file_logger");
	logger_log_info("PiEnvExplore: Welcome!");

	std::atomic<bool> stop_init_blink_flag(false);
	std::thread LED_init_thread{ [&stop_init_blink_flag] {
		while (!stop_init_blink_flag)
		{
			LED1.BLINK_MS(200);
		}
	} };

	system_init();
	stop_init_blink_flag = true;
	LED_init_thread.join(); // main waits for t to finish
	LED1.OFF();
	

	/* RUNNING SYSTEM
	*  Press SW1 to start the cycle
	*  LED turns on, indicating the cycle is running
	*  Switch to logging to /DATA/data.csv
	*  ... Logging data to /DATA/data.csv
	*  ... Logging data to /DATA/data.csv
	*  Cycle will end by pressing SW1 or reaching timeout 
	*  LED turns on, indicating the cycle is finished
	* */
	while (!SW1.IS_PRESSED());
	LED1.ON();
	logger_log_info("Sensor starts collecting data...");
	
	env_sensor.collect_data_second(ccf.CyclePeriod_Second, ccf.CycleTotal_Minutes, false);
	env_sensor.collect_data_second(10, 1, false);
	logger_log_info("Sensor finishes collecting data...");


	/* ENDING SYSTEM
	*  LED blinks (T=1s) -> ending system...
	*  if LED is OFF -> system fails to end.
	*  if LED is ON  -> system successes to end.
	* */
	std::atomic<bool> stop_end_blink_flag(false);
	std::thread LED_end_thread{ [&stop_end_blink_flag] {
		while (!stop_end_blink_flag)
		{
			LED1.BLINK_MS(100);
		}
	} };

	system_ending();
	stop_end_blink_flag = true;
	LED_end_thread.join(); // main waits for t to finish
	LED1.OFF();
	return 0;
}


/* Initialize the system
*/
void system_init() {
	logger_log_info("Init system...");
	logger_log_info("Parent path is:" + get_parent_path().string());
	logger_log_info("UMS path is:" + get_ums_path().string());
	logger_log_info("SysLog path is:" + get_sys_log_path().string());
	logger_log_info("DataLog path is:" + get_data_log_path().string());


	// Initialize the UMS
	if (env_ums.init()) {
		sleep(2);
	}
	logger_log_info("Init system successfully!");
	ccf.CCF_Read();
	std::string tempStr = "Sequence Settings: record every " +
		std::to_string(ccf.CyclePeriod_Second) +
		" seconds for " +
		std::to_string(ccf.CycleTotal_Minutes);
	logger_log_info(tempStr);
}


/* Ending the system
*/
void system_ending() {
	logger_log_info("End system...");
	logger_log_info("End system successfully!");

	// Copy Cycle to UMS
	if (logger_copyDir(get_parent_path(), get_ums_path())) {
		std::cout << "Successed to copy Cycle to UMS" << std::endl;
	}
	else {
		std::cout << "Failed to copy Cycle to UMS" << std::endl;
	}

	// Unmount the UMS
	if (env_ums._unmount()) {
		/*logger_log_info("UMS is unmounted!");
		logger_log_info("Cycle ends!");*/
		std::cout << "Unmounted UMS" << std::endl;
	}
	
}


