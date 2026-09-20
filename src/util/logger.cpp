#include "logger.h"

#include <cerrno>
#include <sys/stat.h>
#include <ctime>

#include <fcntl.h>
#include <unistd.h>

static int g_log_fd = -1;

#include <cstdarg>
#include <cstdio>
#include <cstring>

#if defined (LH_LOG_TO_REMOTE_SERVER)
const char* path = "/game/cstrike/guns_recoil_logs";
#else
const char* path = "guns_recoil_logs";
#endif

void LH_LogInit()
{
    if (mkdir(path, 0755) < 0 && errno != EEXIST)
    {
        fprintf(
            stderr,
            "[GunsRecoil] mkdir failed: %s\n",
            strerror(errno)
        );
        return;
    }

    char log_file_path[512];
    snprintf(log_file_path, sizeof(log_file_path), "%s/guns_recoil.log", path);

    g_log_fd = open(
        log_file_path,
        O_WRONLY | O_CREAT | O_APPEND,
        0644
    );

    if (g_log_fd < 0)
    {
        fprintf(
            stderr,
            "[GunsRecoil] open log failed: %s\n",
            strerror(errno)
        );
        return;
    }
}

void LH_LogShutdown()
{
    if (g_log_fd >= 0)
    {
        close(g_log_fd);
        g_log_fd = -1;
    }
}

void LH_Log(const char *level, const char *format, ...)
{
    char message[1024];

    va_list args;
    va_start(args, format);
    vsnprintf(message, sizeof(message), format, args);
    va_end(args);
    if (g_log_fd < 0)
        return;

    time_t now = time(nullptr);
    tm local_time{};

    localtime_r(&now, &local_time);

    char timestamp[32];

    strftime(
        timestamp, 
        sizeof(timestamp),
        "%H:%M:%S",
        &local_time
    );
    
    char output[1200];

    int lenght = snprintf(
        output,
        sizeof(output),
        "[%s] [%s] %s\n",
        timestamp,
        level,
        message
    );
    
    if (lenght > 0)
        write(g_log_fd, output, lenght);
}
