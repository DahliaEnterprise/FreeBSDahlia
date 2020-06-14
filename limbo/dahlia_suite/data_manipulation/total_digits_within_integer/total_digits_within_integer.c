uint32_t dahlia_total_digits_within_unsigned_integer_thirtytwo(uint32_t integerToCountDigitsFrom){
	uint32_t output = 0;

	uint32_t totalDigits = 0;
	uint64_t placeHolderIterator = 1;
	unsigned int keepCounting = 1;
	while(keepCounting == 1){
		if(placeHolderIterator < integerToCountDigitsFrom){
		
			//Next.
			totalDigits = totalDigits + 1;
			placeHolderIterator = placeHolderIterator * 10;
		}else if(placeHolderIterator >= integerToCountDigitsFrom){
			//Stop counting.
			keepCounting = 0;
		}
	}
	output = totalDigits;

	return output;
}
