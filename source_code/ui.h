#ifndef UI_H
#define UI_H

/* ------------------------------------------------------------------
 *  ui.h  -  Colourful terminal helpers for the Super Mall System
 *  Header-only: just #include "ui.h" (no extra .c file to compile).
 * ------------------------------------------------------------------ */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#ifdef _WIN32
#include <windows.h>
#endif

/* ---------- ANSI colours / styles ---------- */
#define C_RESET   "\033[0m"
#define C_BOLD    "\033[1m"
#define C_DIM     "\033[2m"
#define C_RED     "\033[91m"
#define C_GREEN   "\033[92m"
#define C_YELLOW  "\033[93m"
#define C_BLUE    "\033[94m"
#define C_MAGENTA "\033[95m"
#define C_CYAN    "\033[96m"
#define C_WHITE   "\033[97m"
#define C_GRAY    "\033[90m"

#define UI_WIDTH 56   /* inner width of boxes */

/* Call once at program start: enables colours + UTF-8 on Windows */
static inline void ui_init(void)
{
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    SetConsoleOutputCP(65001);
    if (GetConsoleMode(h, &mode))
        SetConsoleMode(h, mode | 0x0004); /* ENABLE_VIRTUAL_TERMINAL_PROCESSING */
#endif
}

static inline void ui_clear(void) { printf("\033[2J\033[H"); }

static inline void ui_repeat(const char *s, int n)
{
    for (int i = 0; i < n; i++) printf("%s", s);
}

/* Visible terminal width of a UTF-8 string (emoji count as 2 columns) */
static inline int ui_width(const char *s)
{
    int w = 0;
    for (; *s; s++) {
        unsigned char c = (unsigned char)*s;
        if ((c & 0xC0) == 0x80) continue;      /* continuation byte */
        w += (c >= 0xF0) ? 2 : 1;               /* 4-byte lead = emoji */
    }
    return w;
}

/* Big boxed title:  ╔════╗ / ║ title ║ / ╚════╝ */
static inline void ui_header(const char *title, const char *color)
{
    int len = ui_width(title);
    int left = (UI_WIDTH - len) / 2;
    int right = UI_WIDTH - len - left;
    printf("\n%s%s╔", C_BOLD, color); ui_repeat("═", UI_WIDTH); printf("╗\n");
    printf("║%*s%s%*s║\n", left, "", title, right, "");
    printf("╚"); ui_repeat("═", UI_WIDTH); printf("╝%s\n", C_RESET);
}

/* Small section title:  ── Title ─────────── */
static inline void ui_section(const char *title, const char *color)
{
    printf("\n%s%s── %s ", C_BOLD, color, title);
    ui_repeat("─", UI_WIDTH - (int)strlen(title) - 2);
    printf("%s\n", C_RESET);
}

static inline void ui_line(void)
{
    printf("%s", C_GRAY); ui_repeat("─", UI_WIDTH + 2); printf("%s\n", C_RESET);
}

/* Menu entry:   [1]  Text */
static inline void ui_item(int num, const char *text, const char *color)
{
    printf("  %s%s[%d]%s  %s\n", C_BOLD, color, num, C_RESET, text);
}

/* Status messages */
static inline void ui_success(const char *fmt, ...)
{
    va_list a; va_start(a, fmt);
    printf("%s%s ✔ %s", C_BOLD, C_GREEN, C_RESET); printf("%s", C_GREEN);
    vprintf(fmt, a); printf("%s", C_RESET); va_end(a);
}
static inline void ui_error(const char *fmt, ...)
{
    va_list a; va_start(a, fmt);
    printf("%s%s ✘ %s", C_BOLD, C_RED, C_RESET); printf("%s", C_RED);
    vprintf(fmt, a); printf("%s", C_RESET); va_end(a);
}
static inline void ui_warn(const char *fmt, ...)
{
    va_list a; va_start(a, fmt);
    printf("%s%s ! %s", C_BOLD, C_YELLOW, C_RESET); printf("%s", C_YELLOW);
    vprintf(fmt, a); printf("%s", C_RESET); va_end(a);
}
static inline void ui_info(const char *fmt, ...)
{
    va_list a; va_start(a, fmt);
    printf("%s%s ℹ %s", C_BOLD, C_CYAN, C_RESET); printf("%s", C_CYAN);
    vprintf(fmt, a); printf("%s", C_RESET); va_end(a);
}

/* Coloured prompt text, e.g.  getValidInt(UI_PROMPT("Enter choice: ")) */
#define UI_PROMPT(text) (C_BOLD C_YELLOW "  ➤ " C_RESET C_WHITE text C_RESET)

#endif
