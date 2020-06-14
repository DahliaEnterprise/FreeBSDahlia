uint64_t nanosecondresolution_timekeeper_getCurrentTime(){
	//Ask system for current timestamp.
	timespec_get(&nanosecondresolution_timekeeper, TIME_UTC);

	//Convert seconds to "nanosecond" space.
		//Initialize and zero.
		uint64_t timekeeper_currentTime_nanoseconds = 0;

		//Handle current time seconds.
		signed long int timespec_currentTime_seconds = nanosecondresolution_timekeeper.tv_sec;

		//Convert current time seconds to nanoseconds.
		timekeeper_currentTime_nanoseconds = (uint64_t)timespec_currentTime_seconds;
			//Seconds to milisecond format.
			timekeeper_currentTime_nanoseconds = timekeeper_currentTime_nanoseconds * 1000;
			//Miliseconds to nanoseconds format.
			timekeeper_currentTime_nanoseconds = timekeeper_currentTime_nanoseconds * 1000000;

		//Add the nanoseconds to the seconds in nanosecond "space".
		timekeeper_currentTime_nanoseconds = timekeeper_currentTime_nanoseconds +  (uint64_t)nanosecondresolution_timekeeper.tv_nsec;

	uint64_t output = 0;
	output = timekeeper_currentTime_nanoseconds;
	return output;
}
