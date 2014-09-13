#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"


// left rotation
// ref. http://stackoverflow.com/questions/21550903/rotate-pixel-array-90-degrees-in-c
void rotateCW90(unsigned char *pSrcBuf, unsigned char *pDstBuf, const unsigned int width, const unsigned int height)
{
    for (int y = 0, destinationColumn = height - 1; y < height; ++y, --destinationColumn)
    {
        int offset = y * width;

        for (int x = 0; x < width; x++)
        {
            for (int i = 0; i < 3; i++) { // RGB
                pDstBuf[(x * height + destinationColumn) * 3 + i] = pSrcBuf[(offset + x) * 3 + i];
            }
        }
    }
}

// right rotation
void rotateCCW90(unsigned char *pSrcBuf, unsigned char *pDstBuf, const unsigned int width, const unsigned int height)
{
    for (int y = 0, destinationColumn = 0; y < height; ++y, ++destinationColumn)
    {
        int offset = y * width;

        for (int x = 0; x < width; x++)
        {
            for (int i = 0; i < 3; i++) { // RGB
                pDstBuf[((width - x - 1) * height + destinationColumn) * 3 + i] = pSrcBuf[(offset + x) * 3 + i];
            }
        }
    }
}

void flipX(unsigned char *pSrcBuf, unsigned char *pDstBuf, const unsigned int width, const unsigned int height) {
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            for(int i = 0; i < 3; i++) { // RGB
                int offset = y * width;
                pDstBuf[((height - 1 - y) * width + x) * 3 + i] = pSrcBuf[(offset + x) * 3 + i];
            }
        }
    }
}

void flipY(unsigned char *pSrcBuf, unsigned char *pDstBuf, const unsigned int width, const unsigned int height)
{
    for(int y=0; y<height; y++) {
        for(int x = 0; x < width; x++) {
            for(int i = 0; i < 3; i++) { // RGB
                int offset = y * width;
                pDstBuf[(offset + (width - 1 - x)) * 3 + i] = pSrcBuf[(offset + x) * 3 + i];
            }
        }
    }
}

int main() {
    const int W = 443;
    const int H = 233;

    
    cv::Mat src;// = cv::Mat::zeros(W, H, CV_8UC3);
//    cv::Mat dst = cv::Mat::zeros(H, W, CV_8UC3);
    cv::Mat dst = cv::Mat::zeros(W, H, CV_8UC3); // for 90 rotation image. X:Y -> Y:X

    src = cv::imread("test.png");

    rotateCW90(src.data, dst.data, W, H);
//    rotateCCW90(src.data, dst.data, W, H);
//      flipX(src.data, dst.data, W, H);
//      flipY(src.data, dst.data, W, H);

    cv::imshow("src", src);
    cv::imshow("dst", dst);
    
    cv::waitKey(0);
    
    return 0;
}

