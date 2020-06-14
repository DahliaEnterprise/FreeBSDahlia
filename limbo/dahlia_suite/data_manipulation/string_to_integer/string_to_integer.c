uint32_t dahlia_string_to_unsigned_integer_thirtytwo(char* stringToConvert){
	uint32_t output = 0;

	/** Stage One, Extract one string character and append it to an array of integers. **/
	//Create an empty array of integers.
	uint32_t * integers = (uint32_t*)malloc(strlen(stringToConvert) * sizeof(uint32_t)); 
	//Zero the empty array of integers.
	for(uint32_t a = 0; a < strlen(stringToConvert); a++){ integers[a] = 0; }
	//Extract one character, detect which single integer it is and put the numerical equivalent as a uint32_t datatype in the empty array of integers.
	uint32_t stringIndex = 0;
	unsigned int keepConverting = 1;
	while(keepConverting == 1){
		if(strncmp(stringToConvert+stringIndex, "0", 1) == 0){ integers[stringIndex] = 0; }else
		if(strncmp(stringToConvert+stringIndex, "1", 1) == 0){ integers[stringIndex] = 1; }else
		if(strncmp(stringToConvert+stringIndex, "2", 1) == 0){ integers[stringIndex] = 2;}else
		if(strncmp(stringToConvert+stringIndex, "3", 1) == 0){ integers[stringIndex] = 3;}else
		if(strncmp(stringToConvert+stringIndex, "4", 1) == 0){ integers[stringIndex] = 4;}else
		if(strncmp(stringToConvert+stringIndex, "5", 1) == 0){ integers[stringIndex] = 5;}else
		if(strncmp(stringToConvert+stringIndex, "6", 1) == 0){ integers[stringIndex] = 6;}else
		if(strncmp(stringToConvert+stringIndex, "7", 1) == 0){ integers[stringIndex] = 7;}else
		if(strncmp(stringToConvert+stringIndex, "8", 1) == 0){ integers[stringIndex] = 8;}else
		if(strncmp(stringToConvert+stringIndex, "9", 1) == 0){ integers[stringIndex] = 9;}

		//Next character in string.
		stringIndex = stringIndex + 1;
		if(stringIndex >= strlen(stringToConvert)){ keepConverting = 0; }
	}

	//Stage Two, From the lowest integer place (ones) to the largest integer place (hundreds - for example), increment each respective integer place.
	uint32_t integerToOutput = 0;	
	uint32_t integersIndex = strlen(stringToConvert)-1;
	uint32_t placeHolderMultiplier = 1;
	keepConverting = 0;
	while(keepConverting < strlen(stringToConvert)){
		uint32_t computedInteger = integers[integersIndex] * placeHolderMultiplier;
		integerToOutput = computedInteger + integerToOutput;

		//Next.		
		placeHolderMultiplier = placeHolderMultiplier * 10;
		integersIndex = integersIndex - 1;
		keepConverting = keepConverting + 1;
	}
	
	//Return result
	output = integerToOutput;
	return output;
}
