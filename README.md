based on answer on stackoverflow:
https://stackoverflow.com/questions/11887679/how-does-x11-xscreensaver-know-how-long-ive-been-idle-xprintidle-unhelpful

TO BUILD:
	gcc idle.c -o idle -lX11 -lXext -lXss


//  need libxss-dev and build-essentials intalled
