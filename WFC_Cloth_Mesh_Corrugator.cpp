// WFC_Cloth_Mesh_Corrugator.cpp : Defines the entry point for the application.
//

#include "WFC_Cloth_Mesh_Corrugator.h"

using namespace std;

//****************************************************
// Image IO Stuff
//****************************************************
std::ofstream out_file("result.jpg", std::ios_base::out | std::ios_base::binary); //out stream to save the rasterizer's image to

void write_char(unsigned char byte) {
    out_file << byte;
}

bool save_jpg(bitmap::bitmap& bm, const int width, const int height) {
    // RGB: one byte each for red, green, blue
    const auto bytesPerPixel = 3;
    // allocate memory
    auto image = new unsigned char[width * height * bytesPerPixel];
    // create img
    for (auto y = 0; y < height; y++)
        for (auto x = 0; x < width; x++)
        {
            // memory location of current pixel
            auto offset = (y * width + x) * bytesPerPixel;
            // rgb
            float c[3] = { 1,1,1 }; //white
            if (bm[x][height - y - 1]) {
                c[0] = c[1] = c[2] = 0; //black
            }
            image[offset] = max(0, min(255, (int)floor(c[0] * 256.0)));
            image[offset + 1] = max(0, min(255, (int)floor(c[1] * 256.0)));
            image[offset + 2] = max(0, min(255, (int)floor(c[2] * 256.0)));
        }
    // start JPEG compression
    // note: myOutput is the function defined in line 18, it saves the output in example.jpg
    // optional parameters:
    const bool isRGB = true;  // true = RGB image, else false = grayscale
    const auto quality = 90;    // compression quality: 0 = worst, 100 = best, 80 to 90 are most often used
    const bool downsample = false; // false = save as YCbCr444 JPEG (better quality), true = YCbCr420 (smaller file)
    const char* comment = "Generation Result"; // arbitrary JPEG comment
    auto ok = TooJpeg::writeJpeg(write_char, image, width, height, isRGB, quality, downsample, comment);
    delete[] image;
    // error => exit code 1
    return ok ? 1 : 0;
}

//*********************************
// Entry Point
//*********************************
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

	//generate WFC result
	char width_buf[32];
	char height_buf[32];
    int gen_width = 64;
    int gen_height = 64;
	printf("Enter generate width: ");
	scanf_s("%s", width_buf, 32);
	printf("Enter generate height: ");
	scanf_s("%s", height_buf, 32);
	printf("Generating with dimensions %d x %d ...", gen_width, gen_height);
	
    //actual generation here
    bitmap::bitmap out;
    wfc_core::generate(out, bm, gen_width, gen_height);

	printf("done.\n");

	//write result
	printf("Writing generation results ...");
    save_jpg(bm, width, height);
	printf("done.");

	return 0;
}
