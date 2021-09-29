#include "5.filtering.hpp"

const std::map<std::string, std::function<std::unique_ptr<Filter>(int)>>
Filtering::filter_name_to_filter
{
    {"mean",  filter_maker<MeanFilter>},
    {"gauss", filter_maker<GaussianFilter>},
    {"vsobel", filter_maker<VerticalSobelFilter>},
    {"hsobel", filter_maker<HorizontalSobelFilter>},
    {"sobel", filter_maker<SobelFilter>}
};


void Filtering::print_usage(char *prog_name)
{
    std::cerr << "Usage: " << prog_name << " image_path filter_name filter_size\n" ;
    std::cerr << "\timage_path - path to the input image\n";
    std::cerr << "\tfilter_name - (mean|gauss|sobel|hsobel|vsobel)\n";
    std::cerr << "\tfilter_size - integer" << std::endl;
}

Filtering::ParameterSet Filtering::parse_parameters(int argc, char *argv[])
{
    if (argc < 3 || argc > 4)
    {
        Filtering::print_usage(argv[0]);
        throw std::runtime_error("Wrong number of arguments");
    }

    cv::Mat img = cv::imread(argv[1]);
    cv::Mat float_img;
    img.convertTo(float_img, CV_32FC3, 1.0/255);
    std::string filter_name = argv[2];
    size_t filter_size = argc==4 ? std::stoi(argv[3]) : 3;

    ParameterSet ps;
    ps.image = float_img;
    ps.filter_name = filter_name;
    ps.filter_size = filter_size;
    return ps;
}

cv::Mat Filtering::run()
{
    std::unique_ptr<Filter> f = filter_name_to_filter.at(filter_name)(filter_size);
    output = f->run(input); 
    return output;
}

int main(int argc, char *argv[])
{
    try
    {
        auto ps = Filtering::parse_parameters(argc, argv);
        Filtering fs(ps);
        cv::Mat output = fs.run();
        cv::namedWindow("Input");
        cv::imshow("Input", fs.getInput());
        cv::namedWindow("Output");
        cv::imshow("Output", fs.getOutput());
        while (cv::waitKey(0) != 27);
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

