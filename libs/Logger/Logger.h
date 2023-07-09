#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <stdio.h>
#include<stdarg.h>
#include<string.h>
#include<time.h>

#define LOG_FILE "session.log"
FILE* logfile = NULL; // Globaali tiedosto-osoitin, joka osoittaa logitiedostoon

void log_msg(const char* level, const char* msg, va_list args)
{
    char out[512];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    strftime(out, sizeof(out), "[%Y-%m-%d:%H:%M:%S]", &tm);
    strcat(out, level);
    vsprintf(out + strlen(out), msg, args);

    fprintf(logfile, "%s\n", out);
    fprintf(stdout, "%s\n", out); // Voit poistaa tämän rivin, jos et halua tulostaa viestejä konsoliin
}

void init_logger()
{
    logfile = fopen(LOG_FILE, "a");
    if (logfile == NULL)
    {
        fprintf(stderr, "Could not open logfile: %s\n", LOG_FILE);
        exit(1);
    }
}

void close_logger()
{
    fclose(logfile);
}

void print_info(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    log_msg("[INFO] ", msg, args);
    va_end(args);
}

void print_warning(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    log_msg("[WARNING] ", msg, args);
    va_end(args);
}

void print_error(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    log_msg("[ERROR] ", msg, args);
    va_end(args);
}

void print_fatal_error(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    log_msg("[FATAL ERROR] ", msg, args);
    va_end(args);
    close_logger();
    exit(1);
}

#endif // LOGGER_H_INCLUDED
