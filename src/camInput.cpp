#include "camInput.h"

// #include "opencv2/core/utility.hpp"
// #include "opencv2/video/tracking.hpp"
// #include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

cv::Mat image;

CamInput::CamInput(Game *game_)
{
    game = game_;
}

void CamInput::calculateDirection(float x, float y)
{
    // game->shiftBoard(Game::Direction::up);
    // game->shiftBoard(Game::Direction::down);
    // game->shiftBoard(Game::Direction::left);
    // game->shiftBoard(Game::Direction::right);
}

void CamInput::onMouse(int event, int x, int y, int, void*)
{

}

void CamInput::process(int cameraNum)
{
    cv::VideoCapture capture;
    cv::Rect trackWindow;

    capture.open(cameraNum);

    bool paused = false;
    bool running = true;

    cv::Mat frame;

    cv::namedWindow("DirectionDetector", 0);
    cv::setMouseCallback("DirectionDetector", onMouse, 0);

    while (running)
    {
        if (!paused)
        {
            capture >> frame;
            if (frame.empty()) break;
        }

        frame.copyTo(image);

        imshow("DirectionDetector", image);
    }
}