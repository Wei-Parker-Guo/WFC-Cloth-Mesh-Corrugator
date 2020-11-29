// WFC_Cloth_Mesh_Corrugator.cpp : Defines the entry point for the application.
//

#include "WFC_Cloth_Mesh_Corrugator.h"

using namespace std;

int main()
{
	//take sample image directory
	char img_f_buf[64];
	printf("Enter sample corrugation layout img: ");
	scanf_s("%s", img_f_buf, 64);
	printf("Reading from %s ...", img_f_buf);

	//read sample image
	//code snippet referenced and edited from https://stackoverflow.com/questions/2076475/reading-an-image-file-in-c-c
	int width, height, bpp;
	uint8_t* rgb_image = stbi_load(img_f_buf, &width, &height, &bpp, 3);
	//convert to bitmap
	bitmap::bitmap bm;
	bitmap::stb_image_to_bitmap(bm, rgb_image, width, height, 3);
	printf("done.\n");

	return 0;
}
