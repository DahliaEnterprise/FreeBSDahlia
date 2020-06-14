struct dahlia_image{
	uint32_t *transparencyGrid;
	uint32_t * colorGrid;
	uint32_t totalColorsInGrid;
	uint32_t width;
	uint32_t height;
};

struct dahlia_image * dahlia_image_initialize(uint32_t width, uint32_t height);
uint32_t dahlia_image_getIndex_by_xy(struct dahlia_image * imageToGetIndexFrom, uint32_t x, uint32_t y);
void dahlia_image_define_pixel_information(struct dahlia_image * imageToDefinePixel,  uint32_t x, uint32_t y, uint32_t rgbColor, uint32_t transparencyValue);
void dahlia_image_define_pixel_information_by_square_area(struct dahlia_image * imageToDefinePixels, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t rgbColor, uint32_t transparencyValue);

void dahlia_image_save_file(const char* fileLocationAndName, struct dahlia_image * imageToSave);

struct dahlia_image * dahlia_image_load_file(const char* fileLocationAndName);
