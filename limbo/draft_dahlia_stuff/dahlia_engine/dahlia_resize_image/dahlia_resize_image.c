struct dahlia_image * dahlia_resize_image(struct dahlia_image * imageToResize, uint32_t newWidth, uint32_t newHeight){
	struct dahlia_image * output = 0;
	struct dahlia_image * resizedImage = dahlia_image_initialize(newWidth, newHeight);

	//Shinking both width and height?
	if(newWidth <= imageToResize->width){
		if(newHeight <= imageToResize->height){
			//Do Shinking both width and height.
			
			//For every original horizontal pixels is one resizedImage horizontal pixel.
			uint32_t totalHorizontalPixels_of_original_size_over_oneHorizontalPixel_of_resizedImage =(uint32_t) ((double)((double)imageToResize->width / (double)newWidth));

			//For every original vertical pixels is one resizedImage vertical pixel.
			uint32_t totalVerticalPixels_of_original_size_over_oneVerticalPixel_of_resizedImage =(uint32_t) ((double)((double)imageToResize->height / (double)newHeight));

			//Loop through each resizedImage pixel and get the respective original image(imageToResize).
			uint32_t resizedImage_x = 1;
			uint32_t resizedImage_y = 1;
			uint32_t imageToResize_startX = 1;
			uint32_t imageToResize_startY = 1;

			uint32_t keepResizing = 1;
			while( keepResizing == 1 ){
				//Determine ranges for square area to collect individual colors within the imageToResize.
				uint32_t imageToResize_endX = imageToResize_startX + totalHorizontalPixels_of_original_size_over_oneHorizontalPixel_of_resizedImage;
				uint32_t imageToResize_endY = imageToResize_startY + totalVerticalPixels_of_original_size_over_oneVerticalPixel_of_resizedImage;
				
				//Get all colors within the square area to collect individual colors within the imageToResize.
				uint32_t collectX = imageToResize_startX;
				uint32_t collectY = imageToResize_startY;		
				uint32_t totalColorsToCollect = totalHorizontalPixels_of_original_size_over_oneHorizontalPixel_of_resizedImage * totalVerticalPixels_of_original_size_over_oneVerticalPixel_of_resizedImage;				
				uint32_t totalColorsCollected = 0;
				uint32_t * colorsCollected = 0; while( colorsCollected == 0 ){ colorsCollected = (uint32_t*)malloc(totalColorsToCollect * sizeof(uint32_t)); } for(uint32_t a = 0; a < totalColorsToCollect; a++){ colorsCollected[a] = 0; }
				uint32_t * transparencyCollected = 0; while( transparencyCollected == 0 ){ transparencyCollected = (uint32_t*)malloc(totalColorsToCollect * sizeof(uint32_t)); } for(uint32_t a = 0; a < totalColorsToCollect; a++){ transparencyCollected[a] = 0; }

				while(totalColorsCollected < totalColorsToCollect){
					//Get index of target collect X and collect Y.
					uint32_t  indexOfTarget = dahlia_image_getIndex_by_xy(imageToResize, collectX, collectY);

					//Get color value.
					uint32_t colorOfTarget = imageToResize->colorGrid[indexOfTarget];

					//Get transparency value.
					uint32_t transparencyOfTarget = imageToResize->transparencyGrid[indexOfTarget];
					
					//Append color to colorsCollected.
					colorsCollected[totalColorsCollected] = colorOfTarget;
					
					//Append transparency value to transparencyCollected
					transparencyCollected[totalColorsCollected] = transparencyOfTarget;

					//Next.
					totalColorsCollected = totalColorsCollected + 1;
					collectX = collectX + 1;
					if(collectX > imageToResize_endX){
						collectX = imageToResize_startX;
						collectY = collectY + 1;
					}
				}

				//Blend Collected Colors Together
				/** PICK NEAREST NEIGHBOR FOR NOW (first in colorsCollected) **/
				uint32_t indexOfResizedImage = dahlia_image_getIndex_by_xy(resizedImage, resizedImage_x, resizedImage_y);
				uint32_t colorForResizedImageIndex = colorsCollected[0];
				uint32_t transparencyForResizedImageIndex = transparencyCollected[0];
				//Do set color to resizedImage
				resizedImage->colorGrid[indexOfResizedImage] = colorForResizedImageIndex;
				resizedImage->transparencyGrid[indexOfResizedImage] = transparencyForResizedImageIndex;

				//Next, move to next square (do not overlap previously collected color quadrants).
					//Iterator resizedImage target.
					resizedImage_x = resizedImage_x + 1;
					if(resizedImage_x > resizedImage->width){
						resizedImage_x = 1;
						resizedImage_y = resizedImage_y + 1;
					}

					//Detect if finished.
					if(resizedImage_y > resizedImage->height){
						keepResizing = 0;
					}

					//Iterator imageToResize.
					if(keepResizing == 1){
						imageToResize_startX = imageToResize_endX + 1;
						if(imageToResize_startX > imageToResize->width){
							imageToResize_startX = 1;
							imageToResize_startY = imageToResize_endY + 1;
						}
					}

				//Free
				free(colorsCollected);
				free(transparencyCollected);
			}
		}
	}

	output = resizedImage;

	return output;
}
