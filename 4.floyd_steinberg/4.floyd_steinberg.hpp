#include <iostream>
//#include <fstream>
#include <string>
#include <exception>
//#include <vector>
//#include <algorithm>
//#include <numeric>
#include <opencv2/opencv.hpp>
#include "0.Algorithm.hpp"

class FloydSteinberg: public Algorithm<cv::Mat>
{
    private:
        cv::Mat input;
        cv::Mat output;

        inline float round(const float &x);

    public:
        struct ParameterSet
        {
            cv::Mat image;
        };
        FloydSteinberg(const ParameterSet &ps):
            input(ps.image)
        {}
        static ParameterSet parse_parameters(int argc, char *argv[]);
        static void print_usage(char *prog_name);
        cv::Mat run();
        cv::Mat getInput() {return input.clone();}
        cv::Mat getOutput() {return output.clone();}

};

