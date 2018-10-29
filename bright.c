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
int get_file_value(char *filepath) {
    // Open the file.
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: cannot open input file!");
        return -1;
    }

    // Scan the file, fail if not the proper format.
    int val;
    if (fscanf(fp, "%u", &val) != 1) {
        fprintf(stderr, "Error: file did not contain correct value!");
        return -1;
    }

    fclose(fp);
    return val;
}

/**
 * Function for changing the actual brightness of the Intel backlight files.
 *
 * @param perc the percentage increase of the brightness
 * @return     0 if success, -1 otherwise
 */
int change_brightness(int perc) {
    int curr = get_file_value(BRIGHTNESSFILE);
    if (curr == -1) return -1;

    int max = get_file_value(MAXBRIGHTNESS);
    if (max == -1) return -1;

    // Calculate new percentage for brightness.
    int curr_perc = 100 * curr / max;
    int new_perc = curr_perc + perc;
    int new_brightness = max * new_perc / 100;

    // Bounds check of new brightness.
    new_brightness = new_brightness < 0 ? 0 : new_brightness;
    new_brightness = new_brightness > max ? max : new_brightness;

    FILE *fp = fopen(BRIGHTNESSFILE, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: could not open brigthness file for writing.");
        return -1;
    }
    fprintf(fp, "%d\n", new_brightness);
    fclose(fp);

    // Change the permissions of the brightness file to 644.
    // It is owned by root and is in the group root.
    if (chmod(BRIGHTNESSFILE, PERMISSIONBITS)) {
        fprintf(stderr, "Error: could not change file permissions.");
        return -1;
    }

    return 0;
}

/**
 * Main function for taking in arguments.
 *
 * Should have exactly one input argument which should be a numerical number
 * representing the percentage increase/decrease wanted.
 */
int main(int argc, char *argv[]) {
    // Parse arguments.
    if (argc > 2) {
        fprintf(stderr, "Error: too many arguments supplied.");
        return -1;
    } else if (argc == 1) {
        fprintf(stderr, "Error: one argument expected.");
        return -1;
    }

    // Error if input is not a numerical value.
    int inp;
    if (sscanf(argv[1], "%i", &inp) != 1) {
        fprintf(stderr, "Error: argument not an integer.");
        return -1;
    }

    // Return -1 if something went wrong.
    if (change_brightness(inp)) {
        return -1;
    }

    return 0;
}
