#include <DarkHelp.hpp>


/* Similar to the previous example, but sort the results.
 * This way the street names can be re-constructed.
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

			std::sort(results.begin(), results.end(),
					[](const DarkHelp::PredictionResult & lhs, const DarkHelp::PredictionResult & rhs)
					{
						/* The neural network classes look like this:
						 *
						 *		0 stop sign
						 *		1 yield sign
						 *		2 street name
						 *		3 speed limit
						 *		4 back of stop sign
						 *		5 A
						 *		6 B
						 *		7 C
						 *		...etc...
						 *
						 * So in this lambda, we'll sort classes 0-4 first, and then all other classes get
						 * sorted by the X coordinate so they appear left-to-right.  This of course only
						 * works with a single row of text.  Otherwise, more logic will be required to split
						 * the results into rows based on the Y coordinate.
						 */
						if (lhs.best_class < 5)	return true;
						if (rhs.best_class < 5) return false;
						return lhs.rect.x < rhs.rect.x;
					});

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
