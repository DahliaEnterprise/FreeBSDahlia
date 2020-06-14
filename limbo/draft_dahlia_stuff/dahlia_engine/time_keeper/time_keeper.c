void timekeeper_initialize(){
	timekeeper_currentTime_nanoseconds = 0;
}

void timekeeper_update(){
	//Ask system for current timestamp.
	timespec_get(&timeKeeper, TIME_UTC);

	//Convert seconds to "nanosecond" space.
		//Initialize and zero.
		timekeeper_currentTime_nanoseconds = 0;

		//Handle current time seconds.
		signed long int timespec_currentTime_seconds = timeKeeper.tv_sec;

		//Convert current time seconds to nanoseconds.
		timekeeper_currentTime_nanoseconds = (uint64_t)timespec_currentTime_seconds + (uint64_t)timespec_currentTime_seconds;
			//Seconds to milisecond format.
			timekeeper_currentTime_nanoseconds = timekeeper_currentTime_nanoseconds * 1000;
			//Miliseconds to nanoseconds format.
			timekeeper_currentTime_nanoseconds = timekeeper_currentTime_nanoseconds * 1000000;

		//Add the nanoseconds to the seconds in nanosecond "space".
		timekeeper_currentTime_nanoseconds = timekeeper_currentTime_nanoseconds +  (uint32_t)timeKeeper.tv_nsec;
}
