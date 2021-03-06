#include <tesseract/baseapi.h>
#include <opencv2/opencv.hpp>


/* Use Tesseract to read text from a perfect black-and-white image.
 * This should function perfectly, as Tesseract was made for exactly
 * this kind of situation.
 */

int main(int argc, char * argv[])
{
	try
	{
		std::unique_ptr<tesseract::TessBaseAPI> tess(new tesseract::TessBaseAPI());
		tess->Init(nullptr, "eng");

		// see the different options available for page segmentation
#if 1
		// if what you are reading is a single block of text
		tess->SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
#else
		// if you want to extract any and all possible text from an image
		tess->SetPageSegMode(tesseract::PSM_SPARSE_TEXT);
#endif

		for (int idx = 1; idx < argc; idx ++)
		{
			const std::string fn = argv[idx];
			std::cout << "loading " << fn << std::endl;
			cv::Mat mat = cv::imread(fn);
			tess->SetImage(mat.data, mat.cols, mat.rows, mat.channels(), mat.step1());
			tess->SetSourceResolution(70);

			std::unique_ptr<char[]> txt(tess->GetUTF8Text());
			if (not txt) throw std::invalid_argument("failed to detect any text");
			const std::string str = txt.get();

			std::cout << str << std::endl;

			cv::imshow("mat", mat);
			const auto key = cv::waitKey();
			if (key == 27)
			{
				break;
			}
		}
	}
	catch (const std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
