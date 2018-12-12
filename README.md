# Arduino Twitter Library
https://github.com/JChristensen/Twitter  
README file  
Jack Christensen  
Dec 2018  

## Background
This is a copy of NeoCat's v1.3.0 library that I made to fix an issue.

For the original documentation, see [here](http://arduino-tweet.appspot.com/) and [here](http://playground.arduino.cc/Code/TwitterLibrary).

In early Dec 2018, it was noticed that the web site was returning HTTP 403 errors. Upon experimentation, it was discovered that the addition of a "Host" header to the HTTP post allowed things to work again. That fix is in the current version of the library.

## License

Twitter Library for Arduino is distributed under MIT license.