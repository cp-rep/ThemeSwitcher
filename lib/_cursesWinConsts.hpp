/*
  _cursesWinConsts.hpp
 */
#ifndef _CURSESWINCONSTS_HPP
#define _CURSESWINCONSTS_HPP

// color pair values
enum CursesColors {
  none,
  _WHITE_TEXT,
  _BLACK_TEXT
};

// window index constants
enum _WINS {
  // STDSCR
  _MAINWIN,

  // MAIN WINS
  _PROMPTWIN,
  _SAVEDFILESWIN,
  _SAVEDTHEMESWIN,
  _HELPWIN,
  _PROGRAMSWIN,

  // SECONDARY WINS
  _LARROWSAVEDFILESWIN,
  _RARROWSAVEDFILESWIN,
  _LARROWSAVEDTHEMESWIN,
  _RARROWSAVEDTHEMESWIN
};

// _HELPWIN
const unsigned int _HELPWINSTARTY = 2;
const unsigned int _HELPWINSTARTX = 0;
const unsigned int _HELPWINMINCOLS = 50;
const unsigned int _HELPWINMAXCOLS = 60;
const unsigned int _HELPWINMINLINES = 4;
const unsigned int _HELPWINMAXLINES = 40;
const unsigned int _HELPWINCOLOFFSET = 3;
const unsigned int _HELPWINLINEOFFSET = 2;

// _PROGRAMSWIN DIMENSIONS
const unsigned int _PROGRAMSWINSTARTCOLS = 60;//
const unsigned int _PROGRAMSWINMINLINES = 10;//
const unsigned int _PROGRAMSWINMINCOLS = 40;

// _PROMPTWIN DIMENSIONS
const unsigned int _PROMPTWINSTARTY = 2;
const unsigned int _PROMPTWINSTARTX = 3;
const unsigned int _PROMPTWINMINLINES = 6;
const unsigned int _PROMPTWINMAXLINES = 6;
const unsigned int _PROMPTWINCOLOFFSET = 9;
const unsigned int _PROMPTWINLINEOFFSET = 2;
const unsigned int _PROMPTWINMINCOLS = 60;
const unsigned int _PROMPTWINMAXCOLS = 140;

// _SAVEDFILESWIN DIMENSIONS
const unsigned int _SAVEDFILESWINSTARTY = _PROMPTWINSTARTY + _PROMPTWINMAXLINES + 1;
const unsigned int _SAVEDFILESWINSTARTX = 3;
const unsigned int _SAVEDFILESWINMINLINES = 10;
const unsigned int _SAVEDFILESWINMAXLINES = 24;
const unsigned int _SAVEDFILESWINMINCOLS = 60;
const unsigned int _SAVEDFILESWINMAXCOLS = 140;
const unsigned int _SFWINMINLINEOFFSET = 2;
const unsigned int _SFWINMAXLINEOFFSET = 4;
const unsigned int _SFWINMINCOLOFFSET = 3;
const unsigned int _SFWINMAXCOLOFFSET = 3;

// SAVED FILE STRING WIN OFFSETS
const unsigned int _SFSWINMINLINEOFFSET = 4;
const unsigned int _SFSWINMAXLINEOFFSET = 2;
const unsigned int _SFSWINMINCOLOFFSET = 7;
const unsigned int _SFSWINMAXCOLOFFSET = 3;

// _SAVEDFILESWIN DIMENSIONS
const unsigned int _SAVEDTHEMESWINSTARTY = _PROMPTWINSTARTY + _PROMPTWINMAXLINES + 1;
const unsigned int _SAVEDTHEMESWINSTARTX = 3;
const unsigned int _SAVEDTHEMESWINMINLINES = 10;
const unsigned int _SAVEDTHEMESWINMAXLINES = 24;
const unsigned int _SAVEDTHEMESWINMINCOLS = 60;
const unsigned int _SAVEDTHEMESWINMAXCOLS = 140;
const unsigned int _STWINMINLINEOFFSET = 2;
const unsigned int _STWINMAXLINEOFFSET = 4;
const unsigned int _STWINMINCOLOFFSET = 3;
const unsigned int _STWINMAXCOLOFFSET = 3;

#endif // _CURSESWINCONSTS_HPP
