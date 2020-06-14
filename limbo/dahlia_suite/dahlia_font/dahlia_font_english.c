void dahlia_font_english_letter_initialize(){
	//Allocate memory for letter index map.
	dahlia_font_english_letter_index = 0; while( dahlia_font_english_letter_index == 0 ){ dahlia_font_english_letter_index = (char*)malloc( 26 * sizeof(char) ); }
	
	//Map index numbers to letters.
	dahlia_font_english_letter_index[0] = 'a';
	dahlia_font_english_letter_index[1] = 'b';
	dahlia_font_english_letter_index[2] = 'c';
	dahlia_font_english_letter_index[3] = 'd';
	dahlia_font_english_letter_index[4] = 'e';
	dahlia_font_english_letter_index[5] = 'f';
	dahlia_font_english_letter_index[6] = 'g';
	dahlia_font_english_letter_index[7] = 'h';
	dahlia_font_english_letter_index[8] = 'i';
	dahlia_font_english_letter_index[9] = 'j';
	dahlia_font_english_letter_index[10] = 'k';
	dahlia_font_english_letter_index[11] = 'l';
	dahlia_font_english_letter_index[12]= 'm';
	dahlia_font_english_letter_index[13] = 'n';
	dahlia_font_english_letter_index[14] = 'o';
	dahlia_font_english_letter_index[15] = 'p';
	dahlia_font_english_letter_index[16] = 'q';
	dahlia_font_english_letter_index[17] = 'r';
	dahlia_font_english_letter_index[18] = 's';
	dahlia_font_english_letter_index[19] = 't';
	dahlia_font_english_letter_index[20] = 'u';
	dahlia_font_english_letter_index[21] = 'v';
	dahlia_font_english_letter_index[22] = 'w';
	dahlia_font_english_letter_index[23] = 'x';
	dahlia_font_english_letter_index[24] = 'y';
	dahlia_font_english_letter_index[25] = 'z';

	//Allocate memory for array images.
	dahlia_font_english_images = 0; while( dahlia_font_english_images == 0){ dahlia_font_english_images = (struct dahlia_image**)malloc(26 * sizeof(struct dahlia_image)); }
	
	//loop through each letter index and load that image.
	char letterImages_fileLocationAndName[] = "/home/shanebetz/dahlia_suite/dahlia_font/dahlia_alphabet_english/letter_a.dahlia_rgba";
	uint8_t letterReplacementIndex = 72;
	uint8_t currentIndex = 0;
	while(currentIndex < 26){
		//Update file location string.
		letterImages_fileLocationAndName[letterReplacementIndex] = dahlia_font_english_letter_index[currentIndex];

		//Load image into array of images memory.
		dahlia_font_english_images[currentIndex] = dahlia_image_load_file(letterImages_fileLocationAndName);

		//Next
		currentIndex = currentIndex + 1;
	}
}


uint8_t dahlia_font_english_get_index_by_letter(char* letter){
	uint8_t output = 0;

	uint8_t currentIndex = 0;
	while(currentIndex < 26){
		if(strncmp(letter, &dahlia_font_english_letter_index[currentIndex], 1) == 0){
			output = currentIndex;
			//Stop search
			currentIndex = 26;
		}

		//Next
		currentIndex = currentIndex + 1;
	}	

	return output;
}





