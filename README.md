## Updater Tool for Qt 

### Introduction
A cross platform app updater tool for Qt

As a base started with fervor. Lots will change soon. This is not just fork but inspired project instead.

Full blown app updater tool for atleast 3 platforms i.e. Win, Mac and Linux

Let's see what I can do. Stay tuned. :)


### Components

A seperate updater app would be best instead of adding in app itself.

* Updater : Seperate executable.
* Updater's handler : Connecting app and updater. Launch updater whenever required. 


### Why?
* No lock on files (Dlls and including main exe)
* Easier to handle 
* Saves compile time
* My personal choice :)

### Drawbacks ..May be ;) 
* To update updater itself requires same problem. 

### But we have solution to this
* Using two apps we can solve it easily like one can replace other in update process without much problem.
