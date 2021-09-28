#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <opencv2/opencv.hpp>
#include "0.Algorithm.hpp"
#include "5.filters.hpp"

class Filtering: public Algorithm<cv::Mat>
{
    private:
        static const std::map<std::string, std::function<std::unique_ptr<Filter>(int)>>
            filter_name_to_filter;
        template <typename T> static std::unique_ptr<Filter> filter_maker(size_t size)
        {
            return std::unique_ptr<Filter>(new T(size));
        }

        cv::Mat input;
        std::string filter_name;
        size_t filter_size;
        cv::Mat output;

    public:
        struct ParameterSet
        {
            cv::Mat image;
            std::string filter_name;
            size_t filter_size;
        };
        Filtering(const ParameterSet &ps):
            input(ps.image),
            filter_name(ps.filter_name),
            filter_size(ps.filter_size)
        {}
        static ParameterSet parse_parameters(int argc, char *argv[]);
        static void print_usage(char *prog_name);
        cv::Mat run();
        cv::Mat getInput() {return input.clone();}
        cv::Mat getOutput() {return output.clone();}

};

