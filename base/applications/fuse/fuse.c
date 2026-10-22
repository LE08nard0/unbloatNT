/*
 * PROJECT:     unbloatNT - Fusion launcher
 * LICENSE:     GPL-3.0-or-later
 * PURPOSE:     Launch the programs described by a .fuse file.
 *
 * A .fuse file is created by "fusing" two programs together in the shell
 * (drag one onto another and release while holding Shift). It is plain UTF-8
 * text; each non-empty, non-'#' line is a command line to launch. fuse.exe
 * launches the first two such lines, so double-clicking the fused icon starts
 * both programs at once.
 */

#include <windows.h>
#include <shellapi.h>

static VOID LaunchRange(LPCWSTR s, INT len)
{
    WCHAR line[1024];
    INT i = 0;

    while (len > 0 && (*s == L' ' || *s == L'\t')) { s++; len--; }
    while (len > 0 && i < 1023) { line[i++] = *s++; len--; }
    while (i > 0 && (line[i - 1] == L' ' || line[i - 1] == L'\t')) i--;
    line[i] = 0;

    if (i > 0)
        ShellExecuteW(NULL, L"open", line, NULL, NULL, SW_SHOWNORMAL);
}

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPWSTR lpCmdLine, INT nCmdShow)
{
    WCHAR path[MAX_PATH];
    WCHAR text[4096];
    BYTE raw[4096];
    LPCWSTR c = lpCmdLine;
    HANDLE hFile;
    DWORD read = 0;
    INT pi = 0;
    INT wlen;
    INT i, start, launched;
    BOOL quoted;

    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(nCmdShow);

    /* The single argument is the path to the .fuse file (maybe quoted). */
    while (*c == L' ') c++;
    quoted = (*c == L'"');
    if (quoted) c++;
    while (*c && pi < MAX_PATH - 1 && (quoted ? (*c != L'"') : (*c != L' ')))
        path[pi++] = *c++;
    path[pi] = 0;
    if (pi == 0)
        return 1;

    hFile = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ, NULL,
                        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return 1;

    ReadFile(hFile, raw, sizeof(raw) - 1, &read, NULL);
    CloseHandle(hFile);

    wlen = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)raw, (INT)read, text, 4095);
    if (wlen <= 0)
        return 1;
    text[wlen] = 0;

    /* Launch the first two non-empty, non-comment lines. */
    start = 0;
    launched = 0;
    for (i = 0; i <= wlen && launched < 2; i++)
    {
        if (i == wlen || text[i] == L'\n' || text[i] == L'\r')
        {
            INT s = start;
            INT len = i - start;

            while (len > 0 && (text[s] == L' ' || text[s] == L'\t')) { s++; len--; }
            if (len > 0 && text[s] != L'#')
            {
                LaunchRange(&text[s], len);
                launched++;
            }
            start = i + 1;
        }
    }

    return 0;
}
