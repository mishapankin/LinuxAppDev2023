#include <ncurses.h>
#include <stdio.h>
#include <string.h>

enum
{
    DX = 1
};

// lorem ipsum dolor sit amet consectetur adipiscing elit sed do eiusmod tempor incididunt ut labore et dolore magna aliqua ut enim ad minim veniam quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur excepteur sint occaecat cupidatat non proident sunt in culpa qui officia deserunt mollit anim id est laborum

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Cannot open file: %s\n", filename);
        return 1;
    }

    WINDOW *win;
    int c = 0;
    int line_num = 1;

    initscr();
    noecho();
    cbreak();
    printw("%s", filename);
    refresh();

    if (LINES < 3 * DX || COLS < 3 * DX)
    {
        endwin();
        printf("Window is too small\n");
        return 1;
    }

    const int VIEW_LINES = LINES - 2 * DX - 2;
    const int VIEW_COLS = COLS - 2 * DX - 2;

    win = newwin(VIEW_LINES + 2, VIEW_COLS + 2, DX, DX);
    keypad(win, TRUE);
    scrollok(win, TRUE);
    box(win, 0, 0);
    wmove(win, 1, 0);

    const int buff_size = VIEW_COLS - 5;

    bool line_start = true;
    char line[buff_size];
    for (int i = 0; i < VIEW_LINES; ++i)
    {
        fgets(line, buff_size, file);

        if (line_start)
        {
            wprintw(win, "%5d: ", line_num);
            line_start = false;
        }
        else
        {
            wprintw(win, "       ");
        }
        wprintw(win, "%s", line);
        wrefresh(win);

        if (!(strlen(line) == buff_size - 1 && line[buff_size - 1] != '\n'))
        {
            line_start = true;
            line_num += 1;
        }
    }
    box(win, 0, 0);

    while ((c = wgetch(win)) != 27 && c != 'q')
    {
        if (c == ' ')
        {
            if (!feof(file) && c == ' ')
            {
                fgets(line, VIEW_COLS, file);
                wprintw(win, "%5d: %s", line_num, line);
                wrefresh(win);
                line_num += 1;
                box(win, 0, 0);
            }
        }
    }

    endwin();
    fclose(file);
}