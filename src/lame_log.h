/**
 * @file lame_log.h
 * @author Phil Schatzmann
 * @brief Simple Logging
 * @version 0.1
 * @date 2021-08-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

// User Settings: Activate/Deactivate logging
#ifndef LAME_LOGGING_ACTIVE
#define LAME_LOGGING_ACTIVE true
#endif
#ifndef LAME_LOG_LEVEL
#define LAME_LOG_LEVEL Warning
#endif

// Logging Implementation
#if LAME_LOGGING_ACTIVE == true
static char log_buffer[512];
enum LogLevel {Debug, Info, Warning, Error};
static LogLevel minLogLevel = LAME_LOG_LEVEL;
// We print the log based on the log level
#define LOG(level,...) { if(level>=minLogLevel) { int l = snprintf(log_buffer,512, __VA_ARGS__);  Serial.write(log_buffer,l); Serial.println(); } }
#else
// Remove all log statments from the code
#define LOG(Debug, ...) 
#endif
