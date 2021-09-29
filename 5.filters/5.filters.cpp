#include "5.filters.hpp"

//--------------------Filter-------------------------------------

template <typename T> cv::Mat Filter::convolve(const cv::Mat &img)
{
    cv::Mat out = cv::Mat::zeros(img.size(), img.type());
    cv::Mat kernel = get_kernel();
    const int ks = kernel.cols;     // kernel size

    for(int i = (ks-1)/2; i < img.rows - (ks-1)/2; i++)
    {
        for(int j = (ks-1)/2; j < img.cols - (ks-1)/2; j++)
        {
            for(int k = 0; k < ks; k++)
            {
                for(int l = 0; l < ks; l++)
                {
                    out.at<T>(i,j)
                        += kernel.at<float>(k,l) * img.at<T>(i + (ks-1)/2-k, j + (ks-1)/2-l);
                }
            }
        }
    }
    return out;
}

//---------------Mean-Filter-------------------------------------

cv::Mat MeanFilter::get_kernel()
{
    size_t size = get_filter_size();
    return cv::Mat::ones(size, size, CV_32FC1) / (size*size);
}

//--------------Horizontal-Sobel-Filter-------------------------

cv::Mat HorizontalSobelFilter::get_kernel()
{
    const size_t size = get_filter_size();
    cv::Mat kernel = cv::Mat::zeros(size, size, CV_32FC1);
    int i, j;
    for(int I = 0; I < size; I++)
    {
        for(int J = 0; J < size; J++)
        {
            i = I - (size-1)/2;
            j = J - (size-1)/2;
            
            if (i==0 && j==0)
                kernel.at<float>(I, J) = 0.0;
            else
                kernel.at<float>(I, J) = (float) j / (i*i + j*j);
        }
    }
    return kernel;
}

cv::Mat HorizontalSobelFilter::preprocess(cv::Mat &img)
{
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
    return img;
}

cv::Mat HorizontalSobelFilter::postprocess(cv::Mat &img)
{
    img = cv::abs(img);
    return img;
}

//--------------Verical-Sobel-Filter-------------------------

cv::Mat VerticalSobelFilter::get_kernel()
{
    const size_t size = get_filter_size();
    cv::Mat kernel = cv::Mat::zeros(size, size, CV_32FC1);
    int i, j;

    for(int I = 0; I < size; I++)
    {
        for(int J = 0; J < size; J++)
        {
            i = I - (size-1)/2;
            j = J - (size-1)/2;

            if (i==0 && j==0)
                kernel.at<float>(I, J) = 0.0;
            else
                kernel.at<float>(I, J) = (float) i / (i*i + j*j);
        }
    }
    return kernel;
}

cv::Mat VerticalSobelFilter::preprocess(cv::Mat &img)
{
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    return gray;
}

cv::Mat VerticalSobelFilter::postprocess(cv::Mat &img)
{
    img = cv::abs(img);
    return img;
}


//----------------Sobel-Filter----------------------------

cv::Mat SobelFilter::get_kernel()
{
    cv::Mat identity = cv::Mat::ones(1, 1, CV_32FC1);
    return identity;
}

cv::Mat SobelFilter::run(const cv::Mat &img)
{
    VerticalSobelFilter vsf(get_filter_size());
    cv::Mat gy = vsf.run(img);
    cv::pow(gy, 2, gy);
    HorizontalSobelFilter hsf(get_filter_size());
    cv::Mat gx = hsf.run(img);
    cv::pow(gx, 2, gx);

    cv::pow(gx+gy, 0.5, gx);
    cv::threshold(gx, gx, 1.0, 1.0, cv::THRESH_TRUNC);
    return gx;
}

//------------Gaussian-Filter--------------------------

cv::Mat GaussianFilter::get_kernel()
{
    const size_t size = get_filter_size();
    cv::Mat kernel = cv::Mat::zeros(size, size, CV_32FC1);
    int i, j;
    float sum = 0;

    for(int I = 0; I < size; I++)
    {
        for(int J = 0; J < size; J++)
        {
            i = I - (size-1)/2;
            j = J - (size-1)/2;
            kernel.at<float>(I, J) = exp(-(i*i+j*j)/(2*sigma*sigma));
            sum += kernel.at<float>(I, J);
        }
    }
    kernel /= sum;
    return kernel;
}


