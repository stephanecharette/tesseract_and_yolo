#include <DarkHelp.hpp>


/* Load a neural network to detect not only the street signs, but read the
 * individual characters on those signs.
 */

int main(int argc, char * argv[])
{
	try
	{
		// see:  https://www.ccoderun.ca/darkhelp/api/API.html
		DarkHelp::NN nn(
			"../nn/streetsigns.cfg"		,
			"../nn/streetsigns.weights"	,
			"../nn/streetsigns.names"	);

		nn.config.threshold						= 0.4;
		nn.config.annotation_auto_hide_labels	= false;
		nn.config.annotation_include_duration	= false;
		nn.config.sort_predictions				= DarkHelp::ESort::kUnsorted;

		for (int idx = 1; idx < argc; idx ++)
		{
			const std::string fn = argv[idx];
			std::cout << "loading " << fn << std::endl;
			cv::Mat mat = cv::imread(fn);

			auto results = nn.predict(mat);

			std::cout << results << std::endl;

			cv::imshow("mat", nn.annotate());
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
