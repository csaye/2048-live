#include "camInput.h"
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

cv::Mat image;
cv::Point origin;
cv::Rect selection;

const int triggerWidth = 600;
const int triggerHeight = 400;
bool resetTrigger = false;
bool selectObject = false;
int trackObject = 0;
int vMin = 10, vMax = 256, sMin = 30;

cv::VideoCapture capture;
cv::Rect trackWindow;
cv::Rect triggerBox;

bool paused = false;
int hSize = 16;
float hRanges[] = {0, 180};
const float* phRanges = hRanges;

cv::Mat frame, hsv, hue, mask, hist, backProj;
cv::Mat histImg = cv::Mat::zeros(200, 320, CV_8UC3);

CamInput::CamInput(Game *game_, int cameraNum)
{
    game = game_;
    startProcess(cameraNum);
}

void CamInput::startProcess(int cameraNum)
{
    capture.open(cameraNum);
    cv::namedWindow("DirectionDetector", 0);
    cv::setMouseCallback("DirectionDetector", onMouse, 0);
}

void CamInput::calculateDirection(cv::Point point)
{
    if (triggerBox.contains(point) && resetTrigger) resetTrigger = false;
    if (!resetTrigger && !triggerBox.contains(point))
    {
        resetTrigger = true;

        float minX = triggerBox.x;
        float minY = triggerBox.y;
        float maxX = triggerBox.x + triggerBox.width;
        float maxY = triggerBox.y + triggerBox.height;

        if (point.x < minX) game->shiftBoard(Game::Direction::left);
        else if (point.x > maxX) game->shiftBoard(Game::Direction::right);
        else if (point.y < minY) game->shiftBoard(Game::Direction::up);
        else if (point.y > maxY) game->shiftBoard(Game::Direction::down);
    }
}

void CamInput::onMouse(int event, int x, int y, int, void*)
{
    if (selectObject)
    {
        selection.x = MIN(x, origin.x);
        selection.y = MIN(y, origin.y);

        selection.width = std::abs(x - origin.x);
        selection.height = std::abs(y - origin.y);

        selection &= cv::Rect(0, 0, image.cols, image.rows);
    }

    switch (event)
    {
        case cv::EVENT_LBUTTONDOWN:
            origin = cv::Point(x, y);
            selection = cv::Rect(x, y, 0, 0);
            selectObject = true;
            break;
        case cv::EVENT_LBUTTONUP:
            selectObject = false;
            if (selection.width > 0 && selection.height > 0) trackObject = -1;
            break;
    }
}

void CamInput::clear()
{
    trackObject = 0;
}

void CamInput::pause()
{
    paused = !paused;
}

void CamInput::process()
{
    if (!paused)
    {
        capture >> frame;
        if (frame.empty()) return;
    }

    frame.copyTo(image);

    if (!paused)
    {
        cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

        if (trackObject)
        {
            cv::inRange(hsv, cv::Scalar(0, sMin, MIN(vMin, vMax)), cv::Scalar(180, 256, MAX(vMin, vMax)), mask);
            int ch[] = {0, 0};
            hue.create(hsv.size(), hsv.depth());
            cv::mixChannels(&hsv, 1, &hue, 1, ch, 1);

            if (trackObject < 0)
            {
                cv::Mat roi(hue, selection), maskroi(mask, selection);
                cv::calcHist(&roi, 1, 0, maskroi, hist, 1, &hSize, &phRanges);
                normalize(hist, hist, 0, 255, cv::NORM_MINMAX);

                trackWindow = selection;
                trackObject = 1;
                histImg = cv::Scalar::all(0);
                int binW = histImg.cols / hSize;

                cv::Mat buf(1, hSize, CV_8UC3);
                for (int i = 0; i < hSize; i++)
                {
                    buf.at<cv::Vec3b>(i) = cv::Vec3b(cv::saturate_cast<uchar>(i * 180.0 / hSize), 255, 255);
                }
                cv::cvtColor(buf, buf, cv::COLOR_HSV2BGR);
            }

            cv::calcBackProject(&hue, 1, 0, hist, backProj, &phRanges);
            backProj &= mask;
            cv::RotatedRect trackBox = cv::CamShift(backProj, trackWindow, cv::TermCriteria(cv::TermCriteria::EPS | cv::TermCriteria::COUNT, 10, 1));

            if (trackWindow.area() <= 1)
            {
                int cols = backProj.cols;
                int rows = backProj.rows;
                int r = (MIN(cols, rows)) / 6;

                trackWindow = cv::Rect(trackWindow.x - r, trackWindow.y - r, trackWindow.x + r, trackWindow.y + r) & cv::Rect(0, 0, cols, rows);
            }
            
            triggerBox = cv::getWindowImageRect("DirectionDetector");
            triggerBox.x = triggerWidth / 2;
            triggerBox.y = triggerHeight / 2;
            triggerBox.width -= triggerWidth;
            triggerBox.height -= triggerHeight;

            cv::rectangle(image, triggerBox, cv::Scalar(0, 255, 0), 1, cv::LINE_AA);

            cv::ellipse(image, trackBox, cv::Scalar(0, 0, 255), 3, cv::LINE_AA);

            calculateDirection(trackBox.center);
        }
    }
    else if (trackObject < 0) paused = false;

    if (selectObject && selection.width > 0 && selection.height > 0)
    {
        cv::Mat roi(image, selection);
        cv::bitwise_not(roi, roi);
    }

    imshow("DirectionDetector", image);
}