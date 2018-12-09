#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

// File paths, change before compilation if other folders/files.
#define INTELDIR "intel_backlight/"
#define BACKLIGHTDIR "/sys/class/backlight/"INTELDIR
#define BRIGHTNESSFILE BACKLIGHTDIR"brightness"
#define MAXBRIGHTNESS BACKLIGHTDIR"max_brightness"

// Permission bits equivalent to 644
#define PERMISSIONBITS S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH


/**
 * Function for opening a file containing only a numerical value.
 *
 * The function assumes that the file contains only one line, which should be
 * a positive numerical value. Otherwise the function fails and returns -1.
 *
 *
 * The function assumes that the file contains only one line, which should be
 * a positive numerical value. Otherwise the function fails and returns -1.
 * @param filepath path to file to be read
 * @return         the value in the file, -1 otherwise
 */
int get_file_value(char *filepath);

/**
 * Function for changing the actual brightness of the Intel backlight files.
 *
 * @param perc the percentage increase of the brightness
 * @return     0 if success, -1 otherwise
 */
int change_brightness(int perc);

/**
 * Main function for taking in arguments.
 *
 * Should have exactly one input argument which should be a numerical number
 * representing the percentage increase/decrease wanted.
 */
int main(int argc, char *argv[]);
