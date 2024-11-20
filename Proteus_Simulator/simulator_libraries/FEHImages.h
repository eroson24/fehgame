#include <stdlib.h>
#include <FEHLCD.h>
#include <fstream>
#include <iostream>
#include <tigr.h>

#ifndef FEHIMAGES_H
#define FEHIMAGES_H

/// @brief Class for loading and drawing images
class FEHImage
{
	public:
		/// @brief Create a blank image object
		FEHImage() {}

		/// @brief Create an image object from a file
		/// @param filename The name of the file to open
		FEHImage(const char * filename) { Open(filename); }

		/// @brief Open an image file
		/// @param filename The name of the file to open. Must end in .png or (legacy) .pic 
		void Open(const char * filename);

		/// @brief Draw the image at the specified location
		/// @param x X coordinate of upper left corner of image
		/// @param y Y coordinate of upper left corner of image
		void Draw(int x, int y);

		/// @brief (LEGACY) Close the image file
		/// @deprecated This function is no longer necessary, do not use
		void Close() {}
	private:

		/// @brief Open a .pic file
		void OpenPic(const char *);

		Tigr *tigr;
};

#endif
