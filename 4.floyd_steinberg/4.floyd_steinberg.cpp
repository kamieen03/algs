#include "4.floyd_steinberg.hpp"

void FloydSteinberg::print_usage(char *prog_name)
{
    std::cerr << "Usage: " << prog_name << " image_path\n";
    std::cerr << "\timage_path - path to the input image" << std::endl;
}




FloydSteinberg::ParameterSet FloydSteinberg::parse_parameters(int argc, char *argv[])
{
    if (argc != 2)
    {
        FloydSteinberg::print_usage(argv[0]);
        throw std::runtime_error("Wrong number of arguments");
    }

    try
    {
        cv::Mat X = cv::imread(argv[1]);
        cv::Mat gray;
        cv::cvtColor(X, gray, cv::COLOR_BGR2GRAY);
        cv::Mat float_gray;
        gray.convertTo(float_gray, CV_32FC1, 1.0/255);
        ParameterSet ps;
        ps.image = float_gray;
        return ps;
    }
    catch(std::exception& e)
    {
        FloydSteinberg::print_usage(argv[0]);
        throw std::runtime_error("Image not found");
    }

}


float FloydSteinberg::round(const float &x)
{
    return (x < 0.5 ? 0.0 : 1.0);
}

cv::Mat FloydSteinberg::run()
{
    output = input.clone();
    for(size_t y = 0; y < input.rows; y++)
    {
        for(size_t x = 0; x < input.cols; x++)
        {
           float old_val = output.at<float>(y,x); 
           float new_val = round(old_val);
           output.at<float>(y,x) = new_val;
           float error = old_val - new_val;
           output.at<float>(y, x+1) += error * 7.0 / 16;
           output.at<float>(y+1, x-1) += error * 3.0 / 16;
           output.at<float>(y+1, x) += error * 5.0 / 16;
           output.at<float>(y+1, x+1) += error * 1.0 / 16;
        }
    }
    return output;
}

int main(int argc, char *argv[])
{
    try
    {
        auto ps = FloydSteinberg::parse_parameters(argc, argv);
        FloydSteinberg fs(ps);
        fs.run();
        cv::namedWindow("Input");
        cv::imshow("Input", fs.getInput());
        cv::namedWindow("Output");
        cv::imshow("Output", fs.getOutput());
        while (cv::waitKey(0) != 27)
            ;
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

