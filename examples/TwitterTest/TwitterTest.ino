// Sketch to test Twitter library.
// Includes a timestamp from an RTC to make each tweet unique (Twitter won't post duplicates).
// Press the button to send a tweet.
//
// J.Christensen 12Dec2018

#include <Ethernet.h>
#include <JC_Button.h>      // https://github.com/JChristensen/JC_Button
#include <MCP79412RTC.h>    // http://github.com/JChristensen/MCP79412RTC
#include <Streaming.h>      // http://arduiniana.org/libraries/streaming/
#include <SPI.h>
#include <TimeLib.h>        // https://www.pjrc.com/teensy/td_libs_DS1307RTC.html
#include <Twitter.h>        // https://arduino-tweet.appspot.com/
#include <Wire.h>           // https://www.arduino.cc/en/Reference/Wire

void formatTime(char *buf, time_t t);

Button btn(8);

// Ethernet Shield Settings
byte mac[] = { 2, 0, 0, 0, 0, 42 };

// Your Token to Tweet (get it from http://arduino-tweet.appspot.com/)
Twitter twitter("YOUR-TOKEN-HERE");

void setup()
{
    Serial.begin(115200);
    btn.begin();
    delay(1000);
    Serial << F( "\n" __FILE__ " " __DATE__ " " __TIME__ "\n" );
    // start Ethernet, display IP
    if ( !Ethernet.begin(mac) )     // use DHCP
    {
        Serial << F("DHCP fail\n");
        Serial.flush();
        while (1);
    }
    Serial << F("Ethernet started ") << Ethernet.localIP() << endl;
}

void loop()
{
    btn.read();

    if (btn.wasReleased())
    {
        char msg[40];
        strcpy(msg, "Testing: ");
        formatTime(msg + strlen(msg), RTC.get());
        Serial << endl << msg << endl;

        Serial << F("connecting...\n");
        if (twitter.post(msg))
        {
            // Specify &Serial to output received response to Serial.
            // If no output is required, you can just omit the argument, e.g.
            // int status = twitter.wait();
            int status = twitter.wait(&Serial);
            if (status == 200)
            {
                Serial << F("\nsuccess!\n");
            }
            else
            {
                Serial << F("\nfailed: code ") << status << endl;
            }
        }
        else
        {
            Serial << F("\nconnection failed.\n");
        }
    }
}

// format a time_t value, return the formatted string in buf (must be at least 24 bytes)
void formatTime(char *buf, time_t t)
{
    char m[4];    // temporary storage for month string (DateStrings.cpp uses shared buffer)
    strcpy(m, monthShortStr(month(t)));
    sprintf(buf, "%.2d:%.2d:%.2d %s %.2d %s %d",
        hour(t), minute(t), second(t), dayShortStr(weekday(t)), day(t), m, year(t));
}
