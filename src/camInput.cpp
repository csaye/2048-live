#include "camInput.h"

// #include "opencv2/core/utility.hpp"
// #include "opencv2/video/tracking.hpp"
// #include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

cv::Mat image;

cv::Point origin;
cv::Rect selection;

bool selectObject = false;
int trackObject = 0;

CamInput::CamInput(Game *game_, int cameraNum, int fps_)
{
    game = game_;
    fps = fps_;
    startProcess(cameraNum);
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

void CamInput::startProcess(int cameraNum)
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

        char ch = (char)cv::waitKey(2000 / fps);
        if (ch == 27) break;
        else if (ch == 'c') trackObject = 0;
        else if (ch == 'p') paused = !paused;
        else if (ch == 'w') game->shiftBoard(Game::Direction::up);
        else if (ch == 'a') game->shiftBoard(Game::Direction::left);
        else if (ch == 's') game->shiftBoard(Game::Direction::down);
        else if (ch == 'd') game->shiftBoard(Game::Direction::right);
    }
}