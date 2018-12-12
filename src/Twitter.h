/*
  Twitter.cpp - Arduino library to Post messages to Twitter using OAuth.
  Copyright (c) NeoCat 2010-2011. All right reserved.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

// ver1.2.0 - Use <Udp.h> to support IDE 0019 or later
// ver1.3.0 - Support IDE 1.0
// ver1.3.1 - Add "Host:" header.

#ifndef TWITTER_H_INCLUDED
#define TWITTER_H_INCLUDED

#include <inttypes.h>
#include <avr/pgmspace.h>
#include <SPI.h>
#include <Ethernet.h>

class Twitter
{
private:
    uint8_t parseStatus;
    int statusCode;
    const char *token;
    EthernetClient client;
public:
    Twitter(const char *user_and_passwd);

    bool post(const char *msg);
    bool checkStatus(Print *debug = NULL);
    int  wait(Print *debug = NULL);
    int  status(void) { return statusCode; }
};

#endif
