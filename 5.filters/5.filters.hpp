#include <opencv2/opencv.hpp>
#include <math.h>

class Filter
{
    private:
        size_t filter_size;

        template <typename T> cv::Mat convolve(const cv::Mat &img);
        virtual cv::Mat get_kernel() = 0;
        virtual cv::Mat preprocess(cv::Mat &img) {return img;}
        virtual cv::Mat postprocess(cv::Mat &img) {return img;}

    public:
        Filter(size_t size):
            filter_size(size)
        {}
        size_t get_filter_size() {return filter_size;}
        virtual cv::Mat run(const cv::Mat &input)
        {
            cv::Mat img = input.clone();
            img = preprocess(img);

            if (img.channels() == 3)
            {
                img = convolve<cv::Vec3f>(img);
            }
            else if (img.channels() == 1)
            {
                img = convolve<float>(img);
            }
            else
            {
                throw std::runtime_error("Wrong number of channels in input image");
            }
            img = postprocess(img);
            return img;
        }

};

class MeanFilter : public Filter
{
    private:
        cv::Mat get_kernel();
    public:
        MeanFilter(size_t size):
            Filter(size)
        {}
};

class HorizontalSobelFilter : public Filter
{
    private:
        cv::Mat get_kernel();
        cv::Mat preprocess(cv::Mat &img);
        cv::Mat postprocess(cv::Mat &img);
    public:
        HorizontalSobelFilter(size_t size):
            Filter(size)
        {}
};

class VerticalSobelFilter : public Filter
{
    private:
        cv::Mat get_kernel();
        cv::Mat preprocess(cv::Mat &img);
        cv::Mat postprocess(cv::Mat &img);
    public:
        VerticalSobelFilter(size_t size):
            Filter(size)
        {}
};

class SobelFilter : public Filter
{
    private:
        cv::Mat get_kernel();
        cv::Mat run(const cv::Mat &img);
    public:
        SobelFilter(size_t size):
            Filter(size)
        {}
};

class GaussianFilter : public Filter
{
    private:
        const float sigma = 1.0;
        cv::Mat get_kernel();
    public:
        GaussianFilter(size_t size):
            Filter(size)
        {}
};

