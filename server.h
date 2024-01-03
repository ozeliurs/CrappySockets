//
// Created by Maxime BILLY on 03/01/2024.
//

#ifndef CRAPPYSOCKETS_SERVER_H
#define CRAPPYSOCKETS_SERVER_H

int startserver(int port);
int stopserver();

/* read message sent by client */
int getmsg(char msg_read[1024]);

#endif //CRAPPYSOCKETS_SERVER_H
