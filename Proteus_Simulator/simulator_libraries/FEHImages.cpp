/// @file FEHImages.cpp
/// @brief Support for image loading and drawing
/// @note Supports both the legacy '.pic' proprietary image format and the more common '.png' format
/// @note All future image loading should be done with .png files
/// @author Adam Exley


#include<FEHImages.h>
#include "FEHUtility.h"

void FEHImage::Open(const char *filename)
{
	// Check file extension, if it is a .pic file, use OpenPic
	if (strstr(filename, ".pic") != NULL || strstr(filename, ".PIC") != NULL)
	{
		// Here for legacy compatibility
		OpenPic(filename);
	}
	else if (strstr(filename, ".png") != NULL || strstr(filename, ".PNG") != NULL)
	{
		// Load image from file
		tigr = tigrLoadImage(filename);
	}
	else
	{
		std::cout << CONSOLE_ERR("File [" << CONSOLE_BLUE(filename) << "] is not a valid image file! Please use a "<< CONSOLE_GREEN(".png")<< " file\n");
		return;
	}


	// Check for images that are too large
	if (tigr->w > LCD_WIDTH || tigr->h > LCD_HEIGHT)
	{
		std::cout << CONSOLE_ERR("Image [" << CONSOLE_BLUE(filename) << "] is too large! Please use an image smaller than " << CONSOLE_GREEN(LCD_WIDTH) << "x" << CONSOLE_GREEN(LCD_HEIGHT) << "\n");
	}


}


// Legacy function to load .pic files
// Filename is file output by MATLAB to draw. Should end in *FEH.pic
void FEHImage::OpenPic(const char *filename)
{
	int w, h;

	// Create file stream
	std::ifstream pic;
	pic.open(filename);

	//MATLAB outputs picture files in a rows by cols format
	//User interface is completely in an x,y format
	if (pic.is_open())
	{
		pic >> h >> w;
	}
	else 
		std::cout << "File: " << filename << " did not open!\n";


	tigr = tigrBitmap(w, h);

	
	unsigned int tmp_c;

	// Read image from data file
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w && !pic.eof(); j++)
		{
			pic >> tmp_c;

			(*tigr).pix[(i * w) + j] = LCD.FEH2Tigr(tmp_c);
		}
	}

	pic.close();
}

//x,y are top left location of where to draw picture
void FEHImage::Draw(int x, int y)
{
	// Draw image to LCD
	tigrBlitAlpha(LCD.screen, tigr, x, y, 0, 0, tigr->w, tigr->h,1.0);
}

