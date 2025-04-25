/**
 * @file    Log.c
 * @author  Tarık Eren Tosun
 * @date    9 Apr 2025
 * @brief   Logger implementation
 */

#include "Log.h"
#include "../string/String.h"

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

void GetTimestamp(char *buffer, size_t buffer_size) {
    //Check if the system is a Windows system
#ifdef _WIN32
    //Get the system time
    SYSTEMTIME st;
    //Get local time from it
    GetLocalTime(&st);
    //Create formatted string securely
    snprintf(buffer, buffer_size,
             "%02d-%02d-%04d %02d:%02d:%02d:%03d",
             st.wDay, st.wMonth, st.wYear,
             st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
#else
    //Get time as struct
    struct timeval tv;
    //Get time of the dat
    gettimeofday(&tv, NULL);  // Initialize `tv` with current time

    //Setup time info struct
    struct tm time_info;
    //Get local time
    localtime_r(&tv.tv_sec, &time_info);  // Convert seconds to `struct tm`

    // Format date/time into the buffer (e.g., "05-10-2023 14:30:45")
    strftime(buffer, buffer_size, "%d-%m-%Y %H:%M:%S", &time_info);

    // Append milliseconds (tv.tv_usec is microseconds; divide by 1000 for ms)
    const size_t prefix_len = strlen(buffer);

    //Create formatted string
    snprintf(buffer + prefix_len, buffer_size - prefix_len, ":%03ld", tv.tv_usec / 1000);
#endif
}


void Log(const LogLevel level, const char* message) {
    //The logging decorator
    char *decorator = "";

    //Timestamp buffer
    char timestamp[128];

    //Get the timestamp and write to the timestamp buffer
    GetTimestamp(timestamp, sizeof(timestamp));

    //Set the decorator based on the level
    switch (level) {
        case INFO:
            decorator = "\x1b[30;46m[INFO]\x1b[0m";
        break;
        case WARNING:
            decorator = "\x1b[30;43m[WARN]\x1b[0m";
        break;
        case ERROR:
            decorator = "\x1b[30;41m[ERROR]\x1b[0m";
        break;
    }

    //Print
    printf("%s %s: %s", timestamp, decorator, message);
}