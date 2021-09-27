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
        cv::Mat img = cv::imread(argv[1]);
        cv::Mat float_img;
        img.convertTo(float_img, CV_32FC3, 1.0/255);
        ParameterSet ps;
        ps.image = float_img;
        return ps;
    }
    catch(std::exception& e)
    {
        FloydSteinberg::print_usage(argv[0]);
        throw std::runtime_error("Image not found");
    }
}


cv::Vec3f FloydSteinberg::round(const cv::Vec3f &x)
{
    cv::Vec3f y = x;
    y[0] = y[0] < 0.5 ? 0.0 : 1.0;
    y[1] = y[1] < 0.5 ? 0.0 : 1.0;
    y[2] = y[2] < 0.5 ? 0.0 : 1.0;
    return y;
}

cv::Mat FloydSteinberg::run()
{
    output = input.clone();
    for(size_t y = 0; y < input.rows-1; y++)
    {
        for(size_t x = 1; x < input.cols-1; x++)
        {
            cv::Vec3f old_val = output.at<cv::Vec3f>(y, x); 
            cv::Vec3f new_val = round(old_val);
            output.at<cv::Vec3f>(y, x) = new_val;
            cv::Vec3f error = old_val - new_val;
            output.at<cv::Vec3f>(y, x+1) += error * 7.0 / 16;
            output.at<cv::Vec3f>(y+1, x-1) += error * 3.0 / 16;
            output.at<cv::Vec3f>(y+1, x) += error * 5.0 / 16;
            output.at<cv::Vec3f>(y+1, x+1) += error * 1.0 / 16;
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
        while (cv::waitKey(0) != 27);
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

