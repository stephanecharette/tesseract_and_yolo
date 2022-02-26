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
		tess->SetVariable("user_defined_dpi", "70");

		for (int idx = 1; idx < argc; idx ++)
		{
			const std::string fn = argv[idx];
			std::cout << "loading " << fn << std::endl;
			cv::Mat mat = cv::imread(fn);
			tess->SetImage(mat.data, mat.cols, mat.rows, mat.channels(), mat.step1());

			const auto * txt = tess->GetUTF8Text();
			if (txt == nullptr) throw std::invalid_argument("failed to detect any text");
			const std::string str = txt;
			delete [] txt;

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
