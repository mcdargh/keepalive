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

    display = XOpenDisplay("");

    if (XScreenSaverQueryExtension(display, &event_base, &error_base))
    {
        while (1)
        {
            XScreenSaverQueryInfo(display, DefaultRootWindow(display), &info);
            seconds = (float)info.idle / 1000.0f;

            if (seconds > (4 * 60)) {
                // log
                time_t rawtime;
                struct tm *local;
                char buffer[80];
                time(&rawtime);
                local = localtime(&rawtime);

                // launch app to move mouse
                fprintf(stdout, "Moving mouse %s", asctime(local));
                int status = system("xdotool mousemove 750 200");
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
