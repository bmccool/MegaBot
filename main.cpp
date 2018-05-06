#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/video/background_segm.hpp>
#include <string>
#include <stdio.h>

#include "CT_window_manager.hpp"
#include "CS_time.hpp"
#include "FCEUX.hpp"

#define MIN_LINE_LENGTH 10
#define MAX_LINE_GAP 5
#define THRESHOLD_VAR 35
#define SHIFT_AMOUNT 7
#define FOREGROUND_THRESHOLD 40

#include <stdlib.h>

#define LOGURU_IMPLEMENTATION 1
#define LOGURU_WITH_STREAMS 1
#include "loguru.hpp"

// Local Function Prototypes
//void main_detect(VideoCapture & capture);
//void main_box_test(VideoCapture & capture);
//void main_boxes_test(VideoCapture & capture);

int main(int argc, char* argv[])
{
    // Initialize Loguru
    loguru::init(argc, argv);
    loguru::add_file("Full.log", loguru::Append, loguru::Verbosity_MAX);

    LOG_F(INFO, "Instantiating Fceux Class");
    std::string rom = "roms/mm2.nes";
    Fceux fceux(rom);

    for(auto i = 0; i < 10; i++){
       sleep_for_milliseconds(1000);
       fceux.press_and_release("d");
    }

    LOG_F(INFO, "DONE");
    return 0;
}

