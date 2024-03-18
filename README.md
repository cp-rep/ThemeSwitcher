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
also use themes and can apply the "same" color palettes. ThemeSwitcher
came from this main motivation of wanting an easier way to manage and apply 
color themes across Linux applications that support them. Secondly, I have
already built an NCurses windowing framework in a different project that
would accelerate the development process.
