#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <event.h>
#include <evhttp.h>

#define RELOAD_TIMEOUT 5
#define DEFAULT_FILE "sample.html"

char *filedata;
time_t lasttime = 0;
char filename[80];
int counter = 0;

void load_file();

void read_file()
{
    int size = 0;
    char *data;
    struct stat buf;

    stat(filename,&buf);

    if (buf.st_mtime > lasttime)
    {
        if (counter++)
          fprintf(stderr,"Reloading file: %s",filename);
        else
          fprintf(stderr,"Loading file: %s",filename);

        FILE *f = fopen(filename, "rb");
        if (f == NULL)
        {
            fprintf(stderr,"Couldn't open file\n");
            exit(1);
        }

        fseek(f, 0, SEEK_END);
        size = ftell(f);
        fseek(f, 0, SEEK_SET);
        data = (char *)malloc(size+1);
        fread(data, sizeof(char), size, f);
        filedata = (char *)malloc(size+1);
        strcpy(filedata,data);
        fclose(f);

        fprintf(stderr," (%d bytes)\n",size);
        lasttime = buf.st_mtime;
    }
}

void timeout_cb(int fd, short event, void *arg)
{
    load_file();
}

//void load_file(int fd, short event, void *arg)
void load_file()
{
    struct event *loadfile_event;
    struct timeval tv;

    read_file();

    tv.tv_sec = RELOAD_TIMEOUT;
    tv.tv_usec = 0;

    loadfile_event = (struct event*)malloc(sizeof(struct event));

    evtimer_set(loadfile_event, timeout_cb, loadfile_event);

    evtimer_add(loadfile_event, &tv);
}

void generic_request_handler(struct evhttp_request *req, void *arg)
{
    struct evbuffer *evb = evbuffer_new();

    evbuffer_add_printf(evb, "%s",filedata);
    evhttp_send_reply(req, HTTP_OK, "Client", evb);
    evbuffer_free(evb);
}

int main(int argc, char *argv[])
{
    short          http_port = 8081;
    const char    *http_addr = "172.18.124.180";
    struct evhttp *http_server = NULL;

    if (argc > 1)
    {
        strcpy(filename,argv[1]);
        printf("Using %s\n",filename);
    }
    else
    {
        strcpy(filename, DEFAULT_FILE);
    }

    event_init();

    load_file();

    http_server = evhttp_start(http_addr, http_port);
    evhttp_set_gencb(http_server, generic_request_handler, NULL);

    fprintf(stderr, "Server started on port %d\n", http_port);
    event_dispatch();
}
