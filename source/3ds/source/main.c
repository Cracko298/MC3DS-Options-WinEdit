#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <citro3d.h>
#include <signal.h>
#include <unistd.h>
#include <3ds.h>

void cleanup() {
    socExit();
    gfxExit();
    cfguExit();
    aptExit();
    srvExit();
    gspExit();
}

void flush_buffers() {
    gfxFlushBuffers();
    gfxSwapBuffers();
    gspWaitForVBlank();
}

void initialize_gfx() {
    srvInit();
    aptInit();
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
}

void end_diag() {
    printf("\nNote: The Text Above might not accurately\n");
    printf("show what file(s) where modified/converted.\n");
    printf("\nConverted All Possible Attribute Files.\n");
    fflush(stdout);
    printf("Press the 'start' key to exit the application...\n");
    fflush(stdout);
}

void error_dir(const char *folder_dir) {
    printf("\nError Relating to Creation/Detection: %s\n",folder_dir);
}

void process_file(const char *file_path) {

    initialize_gfx();
    flush_buffers();

    FILE *file = fopen(file_path, "rb+");
    if (file == NULL) {
        perror("\nError opening file.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(file_size);
    fread(buffer, 1, file_size, file);

    if (memcmp(buffer, "\xD8\x05\x00\x00\x6D\x70", 6) == 0 || memcmp(buffer, "\xD8\x05\x20\x20\x6D\x70", 6) == 0) {

        for (int i = 0; i < file_size; i++) {
            if (buffer[i] == 0x20) {
                buffer[i] = 0x00;
            }
        }

        fseek(file, 0, SEEK_SET);
        fwrite(buffer, 1, file_size, file);
        fflush(file);

        fflush(stdout);
        printf("\nConverted File:\n");
        printf(file_path);
        printf("\n");
        printf("\n");
        fflush(stdout);

        flush_buffers();

    }

    fclose(file);
    free(buffer);
}

int main() {
    int checksum = 0;
    atexit(cleanup);
    initialize_gfx();
    consoleClear();
    flush_buffers();

    const char *targetDirectory = "/mc3ds_files/options_edit";
    const char *baseDirectory = "/mc3ds_files";

    struct stat dirStats;
    if (stat(baseDirectory, &dirStats) != 0) {
        if (mkdir(baseDirectory, 0777) != 0) {
            error_dir(baseDirectory);
            return 1;
        }
    }

    struct stat dirStat;
    if (stat(targetDirectory, &dirStat) != 0) {
        if (mkdir(targetDirectory, 0777) != 0) {
            error_dir(baseDirectory);
            return 1;
        }
        checksum++;
        svcSleepThread(200000000);
        printf("Directory created:\n");
        printf(targetDirectory);
        printf("\n");
        fflush(stdout);
    }

    DIR *dir = opendir(targetDirectory);
    if (dir == NULL) {
        error_dir(targetDirectory);
        return 1;
    }

    if (checksum == 1) {
        svcSleepThread(650000000);
        printf("\nCannot Convert Files in a Newly Created Dir.\n");
        fflush(stdout);
        printf("Press the 'start' key to exit the application...\n");
        fflush(stdout);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            const char *filename = entry->d_name;
            if (strstr(filename, "options") != NULL && strstr(filename, ".txt") != NULL) {
                char file_path[512];
                snprintf(file_path, sizeof(file_path), "%s/%s", targetDirectory, filename);
                process_file(file_path);
            }
        }
    }

    end_diag();
    flush_buffers();
    closedir(dir);

    while (aptMainLoop()) {
        hidScanInput();

        if (hidKeysDown() & KEY_START) {
            break;
        }

        flush_buffers();
    }

    return 0;
}
