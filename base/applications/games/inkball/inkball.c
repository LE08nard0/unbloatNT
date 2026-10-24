/*
 * PROJECT:     unbloatNT - InkBall
 * LICENSE:     GPL-3.0-or-later
 * PURPOSE:     A fresh, clean-room implementation of the classic InkBall game.
 *
 * Guide the falling coloured balls into the hole of the same colour by drawing
 * ink lines they bounce off. A ball in a matching hole scores; a wrong hole or
 * a ball lost off an edge costs a life. No Microsoft code was used.
 */

#include <windows.h>
#include <stdlib.h>
#include <math.h>

#define IDT_TICK      1
#define MAXBALLS      24
#define MAXINK        128
#define BALL_R        11
#define HOLE_R        20
#define INK_LIFE      140

typedef struct { float x, y, vx, vy; int color; int alive; } BALL;
typedef struct { int x, y, color; } HOLE;
typedef struct { POINT a, b; int life; } INK;

static BALL  g_ball[MAXBALLS];
static HOLE  g_hole[4];
static INK   g_ink[MAXINK];
static int   g_nink;
static int   g_score;
static int   g_lives;
static int   g_cw, g_ch;
static int   g_spawn;
static BOOL  g_drawing;
static POINT g_last;

static const COLORREF g_pal[4] =
{
    RGB(228, 70, 70), RGB(72, 128, 224), RGB(72, 184, 96), RGB(232, 200, 72)
};

static float Frand(void)
{
    return (float)rand() / (float)RAND_MAX;
}

static void Layout(void)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        g_hole[i].x = (g_cw * (i * 2 + 1)) / 8;
        g_hole[i].y = g_ch - 46;
        g_hole[i].color = i;
    }
}

static void NewGame(void)
{
    int i;
    for (i = 0; i < MAXBALLS; i++) g_ball[i].alive = 0;
    g_nink = 0;
    g_score = 0;
    g_lives = 3;
    g_spawn = 0;
}

static void Spawn(void)
{
    int i;
    float ang;
    for (i = 0; i < MAXBALLS; i++)
    {
        if (!g_ball[i].alive)
        {
            ang = (Frand() * 2.0f - 1.0f) * 0.5f;
            g_ball[i].x = g_cw * 0.5f;
            g_ball[i].y = 36.0f;
            g_ball[i].vx = (float)sin(ang) * 2.4f;
            g_ball[i].vy = 1.8f + Frand();
            g_ball[i].color = rand() & 3;
            g_ball[i].alive = 1;
            return;
        }
    }
}

/* Bounce ball b off the ink segment a-c, if it is touching it. */
static void Deflect(BALL *b, POINT a, POINT c)
{
    float ax = (float)a.x, ay = (float)a.y;
    float dx = (float)(c.x - a.x), dy = (float)(c.y - a.y);
    float len2 = dx * dx + dy * dy;
    float t, px, py, nx, ny, d, vdot;

    if (len2 < 1.0f) return;
    t = ((b->x - ax) * dx + (b->y - ay) * dy) / len2;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    px = ax + t * dx;
    py = ay + t * dy;
    nx = b->x - px;
    ny = b->y - py;
    d = (float)sqrt(nx * nx + ny * ny);
    if (d < (float)BALL_R && d > 0.001f)
    {
        nx /= d; ny /= d;
        vdot = b->vx * nx + b->vy * ny;
        if (vdot < 0.0f)
        {
            b->vx -= 2.0f * vdot * nx;
            b->vy -= 2.0f * vdot * ny;
        }
        b->x = px + nx * (float)BALL_R;
        b->y = py + ny * (float)BALL_R;
    }
}

static void Tick(HWND hwnd)
{
    int i, j, w;

    /* spawn a new ball every so often */
    if (++g_spawn > 55)
    {
        g_spawn = 0;
        Spawn();
    }

    for (i = 0; i < MAXBALLS; i++)
    {
        if (!g_ball[i].alive) continue;

        g_ball[i].x += g_ball[i].vx;
        g_ball[i].y += g_ball[i].vy;

        /* walls: bounce off left/right/top */
        if (g_ball[i].x < BALL_R)       { g_ball[i].x = (float)BALL_R; g_ball[i].vx = -g_ball[i].vx; }
        if (g_ball[i].x > g_cw - BALL_R){ g_ball[i].x = (float)(g_cw - BALL_R); g_ball[i].vx = -g_ball[i].vx; }
        if (g_ball[i].y < BALL_R)       { g_ball[i].y = (float)BALL_R; g_ball[i].vy = -g_ball[i].vy; }

        /* ink segments */
        for (j = 0; j < g_nink; j++)
            Deflect(&g_ball[i], g_ink[j].a, g_ink[j].b);

        /* holes */
        for (j = 0; j < 4; j++)
        {
            float hx = (float)(g_hole[j].x - g_ball[i].x);
            float hy = (float)(g_hole[j].y - g_ball[i].y);
            if (hx * hx + hy * hy < (float)(HOLE_R * HOLE_R))
            {
                if (g_hole[j].color == g_ball[i].color) g_score += 10;
                else if (--g_lives <= 0) { NewGame(); Layout(); }
                g_ball[i].alive = 0;
                break;
            }
        }

        /* lost off an edge (below the holes) */
        if (g_ball[i].alive && g_ball[i].y > g_ch + BALL_R)
        {
            g_ball[i].alive = 0;
            if (--g_lives <= 0) { NewGame(); Layout(); }
        }
    }

    /* age ink, drop dead segments */
    w = 0;
    for (j = 0; j < g_nink; j++)
    {
        if (--g_ink[j].life > 0)
            g_ink[w++] = g_ink[j];
    }
    g_nink = w;

    InvalidateRect(hwnd, NULL, FALSE);
}

static void Paint(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc, mem;
    HBITMAP bmp, oldbmp;
    HBRUSH br;
    HPEN pen, oldpen;
    RECT rc;
    int i;
    WCHAR info[64];

    hdc = BeginPaint(hwnd, &ps);
    GetClientRect(hwnd, &rc);

    mem = CreateCompatibleDC(hdc);
    bmp = CreateCompatibleBitmap(hdc, g_cw, g_ch);
    oldbmp = (HBITMAP)SelectObject(mem, bmp);

    /* background */
    br = CreateSolidBrush(RGB(24, 28, 40));
    FillRect(mem, &rc, br);
    DeleteObject(br);

    /* holes: coloured ring */
    for (i = 0; i < 4; i++)
    {
        br = CreateSolidBrush(g_pal[g_hole[i].color]);
        pen = CreatePen(PS_SOLID, 3, RGB(240, 240, 240));
        oldpen = (HPEN)SelectObject(mem, pen);
        SelectObject(mem, br);
        Ellipse(mem, g_hole[i].x - HOLE_R, g_hole[i].y - HOLE_R,
                     g_hole[i].x + HOLE_R, g_hole[i].y + HOLE_R);
        br = (HBRUSH)CreateSolidBrush(RGB(10, 12, 18));
        SelectObject(mem, br);
        Ellipse(mem, g_hole[i].x - 7, g_hole[i].y - 7, g_hole[i].x + 7, g_hole[i].y + 7);
        SelectObject(mem, oldpen);
        DeleteObject(pen);
        DeleteObject(br);
    }

    /* ink */
    pen = CreatePen(PS_SOLID, 3, RGB(235, 235, 245));
    oldpen = (HPEN)SelectObject(mem, pen);
    for (i = 0; i < g_nink; i++)
    {
        MoveToEx(mem, g_ink[i].a.x, g_ink[i].a.y, NULL);
        LineTo(mem, g_ink[i].b.x, g_ink[i].b.y);
    }
    SelectObject(mem, oldpen);
    DeleteObject(pen);

    /* balls */
    for (i = 0; i < MAXBALLS; i++)
    {
        int bx, by;
        if (!g_ball[i].alive) continue;
        bx = (int)g_ball[i].x;
        by = (int)g_ball[i].y;
        br = CreateSolidBrush(g_pal[g_ball[i].color]);
        SelectObject(mem, br);
        SelectObject(mem, GetStockObject(NULL_PEN));
        Ellipse(mem, bx - BALL_R, by - BALL_R, bx + BALL_R, by + BALL_R);
        DeleteObject(br);
    }

    /* score / lives */
    SetBkMode(mem, TRANSPARENT);
    SetTextColor(mem, RGB(235, 235, 245));
    wsprintfW(info, L"Score: %d    Lives: %d", g_score, g_lives);
    TextOutW(mem, 10, 8, info, lstrlenW(info));

    BitBlt(hdc, 0, 0, g_cw, g_ch, mem, 0, 0, SRCCOPY);

    SelectObject(mem, oldbmp);
    DeleteObject(bmp);
    DeleteDC(mem);
    EndPaint(hwnd, &ps);
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_CREATE:
        NewGame();
        SetTimer(hwnd, IDT_TICK, 30, NULL);
        return 0;

    case WM_SIZE:
        g_cw = LOWORD(lp);
        g_ch = HIWORD(lp);
        Layout();
        return 0;

    case WM_TIMER:
        Tick(hwnd);
        return 0;

    case WM_LBUTTONDOWN:
        g_drawing = TRUE;
        g_last.x = LOWORD(lp);
        g_last.y = HIWORD(lp);
        SetCapture(hwnd);
        return 0;

    case WM_MOUSEMOVE:
        if (g_drawing && g_nink < MAXINK)
        {
            POINT p;
            p.x = LOWORD(lp);
            p.y = HIWORD(lp);
            g_ink[g_nink].a = g_last;
            g_ink[g_nink].b = p;
            g_ink[g_nink].life = INK_LIFE;
            g_nink++;
            g_last = p;
        }
        return 0;

    case WM_LBUTTONUP:
        g_drawing = FALSE;
        ReleaseCapture();
        return 0;

    case WM_ERASEBKGND:
        return 1;

    case WM_DESTROY:
        KillTimer(hwnd, IDT_TICK);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPWSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSW wc;
    HWND hwnd;
    MSG msg;

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    srand(GetTickCount());

    ZeroMemory(&wc, sizeof(wc));
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursorW(NULL, (LPCWSTR)IDC_CROSS);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"InkBallWnd";
    RegisterClassW(&wc);

    hwnd = CreateWindowExW(0, L"InkBallWnd", L"InkBall",
                           WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                           520, 520, NULL, NULL, hInstance, NULL);
    if (!hwnd) return 1;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return (int)msg.wParam;
}
