#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>
#include "lwip/api.h"

#include "led_tasks.h"

const static char http_html_hdr[] =
    "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
const static char http_index_hml_s[] = "<!DOCTYPE html>"
"<html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>ESP32</title>"
"<link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css\"></head><body>"
"<div class=\"container\"><div class=\"row\"><div class=\"col\"><h1>LED MODE:</h1>";
const static char http_index_hml_b[] = "<a class=\"btn btn-primary btn-lg btn-block\" href=\"%s\" role=\"button\">%s</a><br/>";
const static char http_index_hml_bd[] = "<a class=\"btn btn-primary btn-lg btn-block disabled\" href=\"%s\" role=\"button\">%s</a><br/>";
const static char http_index_hml_e[] = "</div></div></div></body></html>";

static char html_format_buffer[100];

static void
http_server_netconn_serve(struct netconn *conn)
{
  struct netbuf *inbuf;
  char *buf;
  u16_t buflen;
  err_t err;

  /* Read the data from the port, blocking if nothing yet there.
   We assume the request (the part we care about) is in one netbuf */
  err = netconn_recv(conn, &inbuf);

  if (err == ERR_OK) {
    netbuf_data(inbuf, (void**)&buf, &buflen);

    // strncpy(_mBuffer, buf, buflen);

    /* Is this an HTTP GET command? (only check the first 5 chars, since
    there are other formats for GET, and we're keeping it very simple )*/
    printf("buffer = %s \n", buf);
    if (buflen>=5 &&
        buf[0]=='G' &&
        buf[1]=='E' &&
        buf[2]=='T' &&
        buf[3]==' ' &&
        buf[4]=='/' ) {
          printf("buf[5] = %c\n", buf[5]);
      /* Send the HTML header
             * subtract 1 from the size, since we dont send the \0 in the string
             * NETCONN_NOCOPY: our data is const static, so no need to copy it
       */
	   
	  if(buf[5]=='0') {
        switchScene(0);
      } else if(buf[5]=='1') {
        switchScene(1);
      } else if(buf[5]=='2') {
        switchScene(2);
      } else if(buf[5]=='3') {
        switchScene(3);
      }

	  int mode = getScene();
	  
      netconn_write(conn, http_html_hdr, sizeof(http_html_hdr)-1, NETCONN_NOCOPY);
	  netconn_write(conn, http_index_hml_s, sizeof(http_index_hml_s)-1, NETCONN_NOCOPY);
	  // OFF
	  if (mode == 3) {
		  sprintf(html_format_buffer, http_index_hml_bd, "/3", "OFF");
	  } else {
		  sprintf(html_format_buffer, http_index_hml_b, "/3", "OFF");
	  }
	  netconn_write(conn, html_format_buffer, strlen(html_format_buffer), NETCONN_NOCOPY);
	  // Main light
	  if (mode == 2) {
		  sprintf(html_format_buffer, http_index_hml_bd, "/2", "Main light");
	  } else {
		  sprintf(html_format_buffer, http_index_hml_b, "/2", "Main light");
	  }
	  netconn_write(conn, html_format_buffer, strlen(html_format_buffer), NETCONN_NOCOPY);
	  // Artnet
	  if (mode == 1) {
		  sprintf(html_format_buffer, http_index_hml_bd, "/1", "Artnet");
	  } else {
		  sprintf(html_format_buffer, http_index_hml_b, "/1", "Artnet");
	  }
	  netconn_write(conn, html_format_buffer, strlen(html_format_buffer), NETCONN_NOCOPY);
	  // Test
	  if (mode == 0) {
		  sprintf(html_format_buffer, http_index_hml_bd, "/0", "Test");
	  } else {
		  sprintf(html_format_buffer, http_index_hml_b, "/0", "Test");
	  }
	  netconn_write(conn, html_format_buffer, strlen(html_format_buffer), NETCONN_NOCOPY);
	  
	  
	  
	  netconn_write(conn, http_index_hml_e, sizeof(http_index_hml_e)-1, NETCONN_NOCOPY);
    }

  }
  /* Close the connection (server closes in HTTP) */
  netconn_close(conn);

  /* Delete the buffer (netconn_recv gives us ownership,
   so we have to make sure to deallocate the buffer) */
  netbuf_delete(inbuf);
}

void http_server(void *pvParameters)
{
  struct netconn *conn, *newconn;
  err_t err;
  conn = netconn_new(NETCONN_TCP);
  netconn_bind(conn, NULL, 80);
  netconn_listen(conn);
  do {
     err = netconn_accept(conn, &newconn);
     if (err == ERR_OK) {
       http_server_netconn_serve(newconn);
       netconn_delete(newconn);
     }
   } while(err == ERR_OK);
   netconn_close(conn);
   netconn_delete(conn);
}