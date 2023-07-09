#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <stdio.h>
#include<stdarg.h>
#include<string.h>
#include<time.h>

#define LOG_FILE "session.log"

void log_msg(const char* level, const char* msg, va_list args);
void init_logger();
void close_logger();
void print_info(const char* msg, ...);
void print_warning(const char* msg, ...);
void print_error(const char* msg, ...);
void print_fatal_error(const char* msg, ...);

#endif // LOGGER_H_INCLUDED
