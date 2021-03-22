#include "CoreConfiguration.h"


CoreConfiguration::CoreConfiguration() {

}

/* Default set to record every 3 second for one minute
*/
void CoreConfiguration::CCF_Read() {
	boost::property_tree::ptree ccf_reader;
	if (boost::filesystem::exists(UMS_CCF_FILE)) {
		// Use UMS's CCF file
		boost::property_tree::json_parser::read_json(UMS_CCF_FILE, ccf_reader);
		CyclePeriod_Second = ccf_reader.get("UserCycleSettings.Period", DEFAULT_CYCLE_PERIOD_SECOND);
		CycleTotal_Minutes = ccf_reader.get("UserCycleSettings.Total", DEFAULT_CYCLE_TOTAL_MINUTE);
	}
	else {
		// Use default setting
		CyclePeriod_Second = 3;
		CycleTotal_Minutes = 1;
	}
}