uint32_t data_consume_assist_consume_untill_delimiter(char* dataToConsume, char* delimiter, uint32_t indexToStartConsumptionAt){
	uint32_t output = 0;

	uint32_t iterator = indexToStartConsumptionAt;
	uint32_t indexDelimiterFoundAt = indexToStartConsumptionAt;
	uint32_t stopConsumingIndex = strlen(dataToConsume);
	unsigned int keepConsuming = 1;
	while(keepConsuming == 1){
		//Stop consuming if end of string has been reached.
		if(iterator >= stopConsumingIndex){
			keepConsuming = 0;
		}else{
			//Determine if the delimiter has been found.
			if(strncmp(dataToConsume+iterator, delimiter, 1) == 0){
				indexDelimiterFoundAt = iterator;
				keepConsuming = 0;
			}else if(strncmp(dataToConsume+iterator, delimiter, 1) != 0){
				iterator = iterator + 1;
			}
		}
	}

	output = iterator;
	return output;
}
