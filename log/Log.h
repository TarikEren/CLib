/**
 * @file    Log.h
 * @author  Tarık Eren Tosun
 * @date    9 Apr 2025
 * @brief   Basic logging with timestamps
 */

#ifndef LOG_H
#define LOG_H

// Platform detection
#ifdef _WIN32
    #include <windows.h>
#elif defined(__unix__) || defined(__linux__) || defined(__APPLE__)
    #include <time.h>
#else
    #error "Unsupported OS"
#endif

typedef enum log_level {
    INFO,
    WARNING,
    ERROR
}LogLevel;

/**
 * @brief               Gets the current time in timestamp format
 * @param buffer        Buffer to write to
 * @param buffer_size   The size of the buffer
 */
void GetTimestamp(char *buffer, size_t buffer_size);

/**
 * @brief               Generic logging function
 * @param level         The log level
 * @param message       Message to be printed out
 */
void Log(LogLevel level, const char* message);

#endif
