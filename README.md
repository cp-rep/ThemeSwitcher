# ThemeSwitcher

## What is ThemeSwitcher?
ThemeSwitcher is a C++ GUI based program using the Ncurses library for
people who want a more unified way of switching their color schemes 
for Linux Operating systems. The file locations and color settings
are saved locally for easier future switches.

## How does ThemeSwitcher Work?
ThemeSwitcher works by reading and writing to file paths containing
configuration files for the corresponding Linux program.  The user 
can input the name of the color theme that a program recognizes and
will replace necessary code for the theme to apply.

## Project Motivation
I have been an Arch user for the better part of ten years, primarly
as my coding environment, and had never taken time to make it 
visually appealing. I recently moved to a Tiling Window Manager(Qtile)
from Fluxbox and was very impressed with the amount of visual
customization it provided. I then started doing some research into 
color themes and found that many Linux tools, such as Terminal Emulators, 
also can use color themes and many of can use the "same" theme. So 
ThemeSwitcher came from the motivation of wanting an easier way to 
manage and apply themes across these applications that support it as well
as having already built an NCurses windowing framework in a different
project.
