void dahlia_font_engine_initialize(char * fileAndLocationOfEnglishFontData, uint32_t letterWidth, uint32_t letterHeight){
	unsigned int totalLetters = 26;
	char* letters = 0; while(letters == 0){ letters = (char*)malloc(totalLetters * sizeof(char)); } memset(letters, '\0', totalLetters);
	letters[0] = 'a';
	letters[1] = 'b';
	letters[2] = 'c';
	letters[3] = 'd';
	letters[4] = 'e';
	letters[5] = 'f';
	letters[6] = 'g';
	letters[7] = 'h';
	letters[8] = 'i';
	letters[9] = 'j';
	letters[10] = 'k';
	letters[11] = 'l';
	letters[12] = 'm';
	letters[13] = 'n';
	letters[14] = 'o';
	letters[15] = 'p';
	letters[16] = 'q';
	letters[17] = 'r';
	letters[18] = 's';
	letters[19] = 't';
	letters[20] = 'u';
	letters[21] = 'v';
	letters[22] = 'w';
	letters[23] = 'x';
	letters[24] = 'y';
	letters[25] = 'z';

	letters_as_array_of_dahlia_images = 0; while( letters_as_array_of_dahlia_images == 0 ){ letters_as_array_of_dahlia_images = (struct dahlia_image **)malloc( totalLetters * sizeof(struct dahlia_image) ); }

	unsigned int letterIndex = 0;
	while(letterIndex < totalLetters){
		letters_as_array_of_dahlia_images[letterIndex] = dahlia_image_initialize(letterWidth, letterHeight);

															//prefix("letter") + underscore("_") +letter("a") + file extension(.rgb) + ending indicator("\0")
		uint32_t fileLocationToLetter_stringLength = strlen(fileAndLocationOfEnglishFontData) + 6 + 1 + 1 + 4 + 1;
		char * fileLocationToLetter = 0; while( fileLocationToLetter == 0){ fileLocationToLetter = (char*)malloc(fileLocationToLetter_stringLength * sizeof(char)); } memset(fileLocationToLetter, '\0', fileLocationToLetter_stringLength);
		strncpy(fileLocationToLetter, fileAndLocationOfEnglishFontData, strlen(fileAndLocationOfEnglishFontData));
		strncpy(fileLocationToLetter+strlen(fileLocationToLetter), "letter_", 7);
		strncpy(fileLocationToLetter+strlen(fileLocationToLetter), letters+letterIndex, 1);
		strncpy(fileLocationToLetter+strlen(fileLocationToLetter), ".rgb", 4);
		letters_as_array_of_dahlia_images[letterIndex] = dahlia_image_load_file(fileLocationToLetter);

		//Free
		free(fileLocationToLetter);

		//Next
		letterIndex = letterIndex + 1;
	}

	free(letters);
}
