#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/extensions/scrnsaver.h>
#include <time.h>

/* Report amount of X server idle time. */
/* Build with- */
/* cc xidle.c -o xidle -lX11 -lXext -lXss */

int main(int argc, char *argv[])
{
    Display *display;
    int event_base, error_base;
    XScreenSaverInfo info;
    float seconds;
    int mins = 3;

    display = XOpenDisplay("");

    if (XScreenSaverQueryExtension(display, &event_base, &error_base))
    {
        fprintf(stdout, "Keepalive started.  Will watch for movement every %d minutes", mins);
        while (1)
        {
            XScreenSaverQueryInfo(display, DefaultRootWindow(display), &info);
            seconds = (float)info.idle / 1000.0f;

            if (seconds > (mins * 60)) {
                // log
                time_t rawtime;
                struct tm *local;
                char buffer[80];
                time(&rawtime);
                local = localtime(&rawtime);

                // get pseudorandom pos x and y
                int x = random() / (RAND_MAX/800);
                int y = random() / (RAND_MAX/600);
                sprintf(buffer, "xdotool mousemove %d %d", x, y);
                // launch app to move mouse
                fprintf(stdout, "Moving mouse %s - %s\n", asctime(local), buffer);
                int status = system(buffer);
                if (status == 0) {
                    status++;
                }
                if(status/256 != 0) {
                    fprintf(stderr, "Error: xdotool reported an error\n");
                }
            }
            // wait a minute before checking again
            sleep(60);
        }
        //printf("%f\n",seconds);
        //return(0);
    }
    else
    {
        fprintf(stderr, "Error: XScreenSaver Extension not present\n");
        return (1);
    }
}
