#include "bright.h"


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
