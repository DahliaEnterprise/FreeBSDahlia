struct dahlia_image * dahlia_image_initialize(uint32_t width, uint32_t height){
	//Initialize Output
	struct dahlia_image * output = 0;

	//Allocate Structure to Output
	while(output == 0){
		output = (struct dahlia_image*)malloc( sizeof(struct dahlia_image) );
	}

	//Define width and height to the structure.
	output->width = width;
	output->height = height;

	//Determine total indexes for color grid and transparency grid.
	uint32_t totalIndexes = width * height;

	//Allocate colorGird
	output->colorGrid = 0;
	while( output->colorGrid == 0 ){ output->colorGrid = (uint32_t*)malloc( totalIndexes * sizeof( uint32_t ) ); }
	
	//Allocate transparencyGrid
	output->transparencyGrid = 0;
	while( output->transparencyGrid == 0){ output->transparencyGrid = (uint32_t*)malloc( totalIndexes * sizeof( uint32_t ) ); }

	//Define totalColorsInGrid
	output->totalColorsInGrid = totalIndexes;

	//Return Output
	return output;
}

uint32_t dahlia_image_getIndex_by_xy(struct dahlia_image * imageToGetIndexFrom, uint32_t x, uint32_t y, char * outOfBounds){
	uint32_t output = 0;

	outOfBounds = 0; while(outOfBounds == 0){ outOfBounds = (char*)malloc(sizeof(char)); } outOfBounds[0] = 'n';

	if(x > imageToGetIndexFrom->width){ outOfBounds[0] = 'y'; }
	else if(x <= 0){ outOfBounds[0] = 'y'; }
	else if(y <= 0){ outOfBounds[0] = 'y';}
	else if(y > imageToGetIndexFrom->height){ outOfBounds[0] = 'y'; }
	
	//Determine the current index by computing the row to go to and then append the amount of x.
	//Compute index
	uint32_t targetIndex = 0;
	if(1 == y){ 
		targetIndex = x;
		//Normalize result.
		targetIndex = (targetIndex - 1);
	}else if(y > 1){ 
		uint32_t totalIndexesContainedInRows = ( y - 1) * imageToGetIndexFrom->width;
		targetIndex = totalIndexesContainedInRows + x;
		//Normalize result.
		targetIndex = targetIndex - 1;
	}

	output = targetIndex;
	return output;
}

void dahlia_image_define_pixel_information(struct dahlia_image * imageToDefinePixel, uint32_t x, uint32_t y, uint32_t rgbColor, uint32_t transparencyValue){
	char * targetIndex_error_outofbounds = 0;
	uint32_t targetIndex = dahlia_image_getIndex_by_xy(imageToDefinePixel, x, y, targetIndex_error_outofbounds);
	//If no errors occured, then fill the color and transparency grid at the specified index.
	if(targetIndex_error_outofbounds == 0){
		//Using the targetIndex, define the rgbColor inside of colorGrid and the transparencyGrid.
		imageToDefinePixel->colorGrid[targetIndex] = rgbColor;
		imageToDefinePixel->transparencyGrid[targetIndex] = transparencyValue;
	}
}

void dahlia_image_define_pixel_information_by_square_area(struct dahlia_image * imageToDefinePixels, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t rgbColor, uint32_t transparencyValue){
	//For every horizontal row, fill the columns, then go to the next row.
	uint32_t iteratorX = x;
	uint32_t iteratorY = y;
	uint32_t totalRowsDefined = 0;
	unsigned int keepFillingSquareArea = 1;
	while(keepFillingSquareArea == 1){
		//Fill row
		uint32_t totalPixelsDefinedInRow = 0;
		unsigned int keepFillingRow = 1;
		while(keepFillingRow == 1){
			dahlia_image_define_pixel_information(imageToDefinePixels, iteratorX, iteratorY, rgbColor, transparencyValue);
			totalPixelsDefinedInRow = totalPixelsDefinedInRow + 1;
			iteratorX = iteratorX + 1;
			if(totalPixelsDefinedInRow == width){
				iteratorX = x;
				keepFillingRow = 0;
			}
		}
		iteratorY = iteratorY + 1;
		totalRowsDefined = totalRowsDefined + 1;
		if(totalRowsDefined == height){
			keepFillingSquareArea = 0;
		}
	}
}

void dahlia_image_save_file(const char* fileLocationAndName, struct dahlia_image * imageToSave){
	FILE* imageFileHandle = 0;
	imageFileHandle = fopen(fileLocationAndName, "w");
	if(imageFileHandle != 0){
		//Ensure a start of file happens.
		fseek(imageFileHandle, 0, SEEK_SET);

		//Create header as string.
			//Create Total indexes in grid as string.
			uint32_t totalDigits_of_totalIndexesInGrid = dahlia_total_digits_within_unsigned_integer_thirtytwo(imageToSave->totalColorsInGrid);
			uint32_t totalIndexesInGrid_as_string_memorysize = totalDigits_of_totalIndexesInGrid + 1;
			char* totalIndexesInGrid_as_string = 0; while(totalIndexesInGrid_as_string == 0){ totalIndexesInGrid_as_string = (char*)malloc( totalIndexesInGrid_as_string_memorysize * sizeof(char) ); }
			totalIndexesInGrid_as_string[totalDigits_of_totalIndexesInGrid] = '\0';		
			snprintf(totalIndexesInGrid_as_string, (totalDigits_of_totalIndexesInGrid+1), "%u", imageToSave->totalColorsInGrid);
			
			//Create width as string
			uint32_t totalDigits_of_width = dahlia_total_digits_within_unsigned_integer_thirtytwo(imageToSave->width);
			uint32_t totalDigits_of_width_string_memorysize = totalDigits_of_width + 1;
			char* width_as_string = 0; while(width_as_string == 0){ width_as_string = (char*)malloc( totalDigits_of_width_string_memorysize * sizeof(char) ); }
			width_as_string[totalDigits_of_width] = '\0';
			snprintf(width_as_string, (totalDigits_of_width+1), "%u", imageToSave->width);

			//Create height as string
			uint32_t totalDigits_of_height = dahlia_total_digits_within_unsigned_integer_thirtytwo(imageToSave->height);
			uint32_t totalDigits_of_height_string_memorysize = totalDigits_of_height + 1;
			char* height_as_string = 0; while(height_as_string == 0){ height_as_string = (char*)malloc( totalDigits_of_height_string_memorysize * sizeof(char) ); }
			height_as_string[totalDigits_of_height] = '\0';
			snprintf(height_as_string, (totalDigits_of_height+1), "%u", imageToSave->height);
			
			//Create combine header elements into a whole string header format.
				//Determine Header String Length.
					//Total Indexes In Grid String Lenght + Delimiter String Length + Width String Length + Delimiter String Lenght + Height String Length
					//totalDigits_of_totalIndexesInGrid + 1  + totalDigits_of_width + 1 + totalDigits_of_height
					uint32_t header_string_length = totalDigits_of_totalIndexesInGrid + 1 + totalDigits_of_width + 1 + totalDigits_of_height;
					uint32_t header_memorysize = header_string_length + 1;
				//Create allocate memory for header as string.
				char* header_as_string = 0; while(header_as_string == 0){ header_as_string = (char*)malloc( header_memorysize * sizeof(char) ); }
				header_as_string[header_string_length] = '\0';

				//Do create header, combine header elements into a whole string header format.
					uint32_t header_as_string_writeIndex = 0;

					//Append total indexes to header.
					strncpy(header_as_string, totalIndexesInGrid_as_string, totalDigits_of_totalIndexesInGrid);
					header_as_string_writeIndex = totalDigits_of_totalIndexesInGrid;

					//Append delimiter.
					strncpy(header_as_string+header_as_string_writeIndex, ",", 1);
					header_as_string_writeIndex = header_as_string_writeIndex + 1;

					//Append width to header.
					strncpy(header_as_string+header_as_string_writeIndex, width_as_string, totalDigits_of_width);
					header_as_string_writeIndex = header_as_string_writeIndex + totalDigits_of_width;

					//Append delimiter.
					strncpy(header_as_string+header_as_string_writeIndex, ",", 1);
					header_as_string_writeIndex = header_as_string_writeIndex + 1;

					//Append height to header.
					strncpy(header_as_string+header_as_string_writeIndex, height_as_string, totalDigits_of_height);
					header_as_string_writeIndex = header_as_string_writeIndex + totalDigits_of_height;

		//Write header string to file.
		fwrite(header_as_string, header_string_length, sizeof(char), imageFileHandle);

			//Free header as string
			free(header_as_string);
			//Free elements that were copied to header string.
			free(totalIndexesInGrid_as_string);
			free(width_as_string);
			free(height_as_string);

		//For each transparency index, write to file as string.
			//Allocate reuseable memory for transparency value as string.		
			uint32_t maxValue_transparencyValue = 0xFFFFFFFF;
			uint32_t totalDigits_of_maxTransparencyValue = dahlia_total_digits_within_unsigned_integer_thirtytwo(maxValue_transparencyValue);
			uint32_t totalStringLength_of_maxTransparencyValue = totalDigits_of_maxTransparencyValue + 1;
			char* transparencyValue_as_string = 0; while( transparencyValue_as_string == 0 ){ transparencyValue_as_string = (char*)malloc( totalStringLength_of_maxTransparencyValue * sizeof(char) ); }
			
			//Do loop through transparency index and write each value as string format to file.
			uint32_t transparencyCurrentIndex = 0;
			uint8_t keepWritingTransparencyValue = 1;
			while(keepWritingTransparencyValue == 1){
				//Clear string
				memset(transparencyValue_as_string, '\0', totalStringLength_of_maxTransparencyValue);

				//Get handle of transparency value
				uint32_t transparencyValue = imageToSave->transparencyGrid[transparencyCurrentIndex];

				if(transparencyValue > 0){
					//Convert number to string.
						//Get total digits of this transparency value.
						uint32_t totalDigits_of_transparencyValue = dahlia_total_digits_within_unsigned_integer_thirtytwo(transparencyValue);						
						uint32_t totalStringLength_of_transparencyValue = totalDigits_of_transparencyValue + 1;

						//Do convert from number to string format.
						snprintf(transparencyValue_as_string, totalStringLength_of_transparencyValue, "%u", transparencyValue);

						//Write to File
							//Write delimiter
							fwrite(",", 1, sizeof(char), imageFileHandle);

							//Write transparency value as string to file.
							fwrite(transparencyValue_as_string, totalDigits_of_transparencyValue, sizeof(char), imageFileHandle);
							
				}else if(transparencyValue == 0){
					//Define zero as the string.
					transparencyValue_as_string[0] = '0';

					//Write to File.
						//Write delimiter
						fwrite(",", 1, sizeof(char), imageFileHandle);

						//Write transparency value as string to file.
						fwrite(transparencyValue_as_string, 1, sizeof(char), imageFileHandle);
				}

				//Next.
				transparencyCurrentIndex = transparencyCurrentIndex + 1;
				if(transparencyCurrentIndex >= imageToSave->totalColorsInGrid){
					keepWritingTransparencyValue = 0;
				}
			}

			//Free
			free(transparencyValue_as_string);

	//For each color index, write to file as string.
			//Allocate reuseable memory for color value as string.		
			uint32_t maxValue_colorValue = 0xFFFFFFFF;
			uint32_t totalDigits_of_maxColorValue = dahlia_total_digits_within_unsigned_integer_thirtytwo(maxValue_colorValue);
			uint32_t totalStringLength_of_maxColorValue = totalDigits_of_maxColorValue + 1;
			char* colorValue_as_string = 0; while( colorValue_as_string == 0 ){ colorValue_as_string = (char*)malloc( totalStringLength_of_maxColorValue * sizeof(char) ); }
			
			//Do loop through color index and write each value as string format to file.
			uint32_t colorCurrentIndex = 0;
			uint8_t keepWritingColorValue = 1;
			while(keepWritingColorValue == 1){
				//Clear string
				memset(colorValue_as_string, '\0', totalStringLength_of_maxTransparencyValue);

				//Get handle of color value
				uint32_t colorValue = imageToSave->colorGrid[colorCurrentIndex];

				if(colorValue > 0){
					//Convert number to string.
						//Get total digits of this color value.
						uint32_t totalDigits_of_colorValue = dahlia_total_digits_within_unsigned_integer_thirtytwo(colorValue);						
						uint32_t totalStringLength_of_colorValue = totalDigits_of_colorValue + 1;

						//Do convert from number to string format.
						snprintf(colorValue_as_string, totalStringLength_of_colorValue, "%u", colorValue);

						//Write to File
							//Write delimiter
							fwrite(",", 1, sizeof(char), imageFileHandle);

							//Write color value as string to file.
							fwrite(colorValue_as_string, totalDigits_of_colorValue, sizeof(char), imageFileHandle);
							

				}else if(colorValue == 0){
					//Define zero as the string.
					colorValue_as_string[0] = '0';

					//Write to File.
						//Write delimiter
						fwrite(",", 1, sizeof(char), imageFileHandle);

						//Write color value as string to file.
						fwrite(colorValue_as_string, 1, sizeof(char), imageFileHandle);
				}

				//Next.
				colorCurrentIndex = colorCurrentIndex + 1;
				if(colorCurrentIndex >= imageToSave->totalColorsInGrid){
					keepWritingColorValue = 0;
				}
			}

			//Free
			free(colorValue_as_string);
		
		//Flush, then close file.
		fflush(imageFileHandle);
		fclose(imageFileHandle);	
	
	}else if(imageFileHandle == 0){
		printf("FAILED TO SAVE FILE\n");
	}
}


struct dahlia_image * dahlia_image_load_file(const char* fileLocationAndName){
	struct dahlia_image * output = 0;

	FILE* imageFileHandle = 0;
	imageFileHandle = fopen(fileLocationAndName, "r");
	if(imageFileHandle != 0){
		//Determine total number of characters of file.
		fseek(imageFileHandle, 0, SEEK_END);
		long int totalNumberOfCharacters = ftell(imageFileHandle);
		fseek(imageFileHandle, 0, SEEK_SET);

		//Allocate wholeFileContent
		uint32_t wholeFileContent_string_length = (uint32_t)totalNumberOfCharacters + (uint32_t)1;
		char* wholeFileContent = 0; while(wholeFileContent == 0){ wholeFileContent = (char*)malloc( wholeFileContent_string_length * sizeof(char) ); }
		wholeFileContent[wholeFileContent_string_length] = '\0';
		
		//Read long term storage file.
		fread(wholeFileContent, totalNumberOfCharacters, sizeof(char), imageFileHandle);

		//Flush and Close file handle
		fflush(imageFileHandle);
		fclose(imageFileHandle);

		//Interpret loaded file into a dahlia image.
			//Initialize index tracking.
			uint32_t beginIndex = 0;
			uint32_t endIndex = 0;
			
			//Extract Header
				//Extract number of total indexes in grid.
					//Define endIndex
					endIndex = data_consume_assist_consume_untill_delimiter(wholeFileContent, ",", beginIndex);
					//Define string length of total indexes in grid.
					uint32_t totalIndexesInGrid_string_length = endIndex - beginIndex;
					uint32_t totalIndexesInGrid_memorysize = totalIndexesInGrid_string_length + 1;
					//Do extraction from wholeFileContent to totalIndexesInGrid as string.
					char* totalIndexesInGrid_as_string = 0; while(totalIndexesInGrid_as_string == 0){ totalIndexesInGrid_as_string = (char*)malloc( totalIndexesInGrid_memorysize * sizeof(char) ); }
					totalIndexesInGrid_as_string[totalIndexesInGrid_string_length] = '\0';
					strncpy(totalIndexesInGrid_as_string, wholeFileContent, totalIndexesInGrid_string_length);
					//Convert totalIndexesInGrid as string to unsigned thirtytwo integer.
					uint32_t totalIndexesInGrid = dahlia_string_to_unsigned_integer_thirtytwo(totalIndexesInGrid_as_string);
					//Free
					free(totalIndexesInGrid_as_string);

				//Extract number of width.
					//Define beginIndex
					beginIndex = endIndex + 1;
					//Define endIndex
					endIndex = data_consume_assist_consume_untill_delimiter(wholeFileContent, ",", beginIndex);
					//Define string length of width.
					uint32_t width_string_length = endIndex - beginIndex;
					uint32_t width_memorysize = width_string_length + 1;
					//Do extraction from wholeFileContent to width as string.
					char* width_as_string = 0; while(width_as_string == 0){ width_as_string = (char*)malloc(width_memorysize * sizeof(char)); }
					width_as_string[width_string_length] = '\0';
					strncpy(width_as_string, wholeFileContent+beginIndex, width_string_length);
					//Convert width as string to unsigned thirtytwo integer.
					uint32_t width = dahlia_string_to_unsigned_integer_thirtytwo(width_as_string);
					//Free
					free(width_as_string);

				//Extract number of height
					//Define beginIndex
					beginIndex = endIndex + 1;
					//Define endIndex
					endIndex = data_consume_assist_consume_untill_delimiter(wholeFileContent, ",", beginIndex);
					//Define string length of height.
					uint32_t height_string_length = endIndex - beginIndex;
					uint32_t height_memorysize = width_string_length + 1;
					//Do extraction from wholeFileContent to height as string.
					char* height_as_string = 0; while(height_as_string == 0){ height_as_string = (char*)malloc(height_memorysize * sizeof(char)); }
					height_as_string[height_string_length] = '\0';
					strncpy(height_as_string, wholeFileContent+beginIndex, height_string_length);
					//Convert width as string to unsigned thirtytwo integer.
					uint32_t height = dahlia_string_to_unsigned_integer_thirtytwo(height_as_string);
					//Free
					free(height_as_string);

			//Initialize dahlia_image structure
			output = dahlia_image_initialize(width, height);

			//Extract Transparency Values.
				//Initialize variables to extract transparency values.
				uint32_t currentTransparencyValueIndex = 0;
				uint32_t totalTransparencyValues = totalIndexesInGrid;
				uint8_t keepExtractingTransparencyValues = 1;

				//Allocate reuseable memory to extract transparency value.
				uint32_t transparencyValue_maxValue = 0xFFFFFFFF;
				uint32_t totalDigits_of_maxTransparencyValue = dahlia_total_digits_within_unsigned_integer_thirtytwo(transparencyValue_maxValue);
				uint32_t stringLength_of_maxTransparencyValue = totalDigits_of_maxTransparencyValue + 1;
				char* transparencyValue_as_string = 0; while(transparencyValue_as_string == 0){ transparencyValue_as_string = (char*)malloc( stringLength_of_maxTransparencyValue * sizeof(char) ); }

				//Start extracting transparency values.
				while(keepExtractingTransparencyValues == 1){

					//Clear string
					memset(transparencyValue_as_string, '\0', stringLength_of_maxTransparencyValue);

					//Define beginIndex
					beginIndex = endIndex + 1;

					//Define endIndex
					endIndex = data_consume_assist_consume_untill_delimiter(wholeFileContent, ",", beginIndex);
					
					//transparency value string length
					uint32_t transparencyValue_string_length = endIndex - beginIndex;

					//Extract transparency value as string.
					strncpy(transparencyValue_as_string, wholeFileContent+beginIndex, transparencyValue_string_length);

					//Convert transparency value string to unsigned thirtytwo integer.
					uint32_t transparencyValue = dahlia_string_to_unsigned_integer_thirtytwo(transparencyValue_as_string);
					
					//Mend dahlia_image structure.
					output->transparencyGrid[currentTransparencyValueIndex] = transparencyValue;

					//Next
					currentTransparencyValueIndex = currentTransparencyValueIndex + 1;
					if(currentTransparencyValueIndex >= totalIndexesInGrid){
						keepExtractingTransparencyValues = 0;
					}
				}
				//Free
				free(transparencyValue_as_string);

			//Extract Color Values.
				//Initialize variables to extract color values.
				uint32_t currentColorValueIndex = 0;
				uint32_t totalColorValues = totalIndexesInGrid;
				uint8_t keepExtractingColorValues = 1;

				//Allocate reuseable memory to extract color value.
				uint32_t colorValue_maxValue = 0xFFFFFFFF;
				uint32_t totalDigits_of_maxColorValue = dahlia_total_digits_within_unsigned_integer_thirtytwo(colorValue_maxValue);
				uint32_t stringLength_of_maxColorValue = totalDigits_of_maxColorValue + 1;
				char* colorValue_as_string = 0; while(colorValue_as_string == 0){ colorValue_as_string = (char*)malloc( stringLength_of_maxColorValue * sizeof(char) ); }

				//Start extracting color values.
				while(keepExtractingColorValues == 1){
					//Clear string
					memset(colorValue_as_string, '\0', stringLength_of_maxColorValue);

					//Define beginIndex
					beginIndex = endIndex + 1;

					//Define endIndex
					endIndex = data_consume_assist_consume_untill_delimiter(wholeFileContent, ",", beginIndex);
					
					//color value string length
					uint32_t colorValue_string_length = endIndex - beginIndex;

					//Extract color value as string.
					strncpy(colorValue_as_string, wholeFileContent+beginIndex, colorValue_string_length);

					//Convert color value string to unsigned thirtytwo integer.
					uint32_t colorValue = dahlia_string_to_unsigned_integer_thirtytwo(colorValue_as_string);
					
					//Mend dahlia_image structure.
					output->colorGrid[currentColorValueIndex] = colorValue;

					//Next
					currentColorValueIndex = currentColorValueIndex + 1;
					if(currentColorValueIndex >= totalIndexesInGrid){
						keepExtractingColorValues = 0;
					}
				}

				//Free
				free(colorValue_as_string);
		//Free
		free(wholeFileContent);

	}else{ 
		printf("failed to open file\n");
	}

	return output;
}

