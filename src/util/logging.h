#pragma once
#include "flanterm.h"
#include "limine.h"

typedef enum {
	DEBUG,
	OK,
	INFO,
	WARNING,
	ERROR
} LogLevel;

#define MIN_LOG_LEVEL DEBUG

void logMsg(const char* message, LogLevel logLevel, struct flanterm_context *ft_ctx);
void debug(const char* message, struct flanterm_context *ft_ctx);
void ok(const char* message, struct flanterm_context *ft_ctx);
void info(const char* message, struct flanterm_context *ft_ctx);
void warn(const char* message, struct flanterm_context *ft_ctx);
void error(const char* message, struct flanterm_context *ft_ctx);

struct flanterm_context* init_console(struct limine_framebuffer *framebuffer);