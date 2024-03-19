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
  _SAVEDFILESWINSAVED,
  _SAVEDFILESWINTHEMES,
  _SAVEDTHEMESSAVEDWIN,
  _PROGRAMSWINSAVED,

  // TEXT WIN
  _TEXTWIN
};

// _HELPWIN DIMENSION CONSTS
const unsigned int _HELPWINSTARTY = 2;
const unsigned int _HELPWINSTARTCOLS = 60;
const unsigned int _HELPWINMINLINES = 10;
const unsigned int _HELPWINMINCOLS = 40;

// _PROGRAMSWIN DIMENSION CONSTS
const unsigned int _PROGRAMSWINSTARTCOLS = 60;//
const unsigned int _PROGRAMSWINMINLINES = 10;//
const unsigned int _PROGRAMSWINMINCOLS = 40;

// _PROMPTWIN DIMENSION CONSTS
const unsigned int _PROMPTWINSTARTY = 2;
const unsigned int _PROMPTWINSTARTX = 3;
const unsigned int _PROMPTWINMINLINES = 6;
const unsigned int _PROMPTWINMAXLINES = 6;
const unsigned int _PROMPTWINMINCOLS = 60;
const unsigned int _PROMPTWINMAXCOLS = 120;

// _SAVEDFILESWIN DIMENSION CONSTS
const unsigned int _SAVEDFILESWINSTARTY = _PROMPTWINSTARTY + _PROMPTWINMAXLINES + 1;
const unsigned int _SAVEDFILESWINSTARTX = 3;
const unsigned int _SAVEDFILESWINMINLINES = 12;
const unsigned int _SAVEDFILESWINMAXLINES = 30;
const unsigned int _SAVEDFILESWINMINCOLS = 60;
const unsigned int _SAVEDFILESWINMAXCOLS = 120;

// _SAVEDTHEMESWIN DIMENSION CONSTS
const unsigned int _SAVEDTHEMESWINSTARTY = 2;
const unsigned int _SAVEDTHEMESWINSTARTX = 3;
const unsigned int _SAVEDTHEMESWINMINLINES = 10;
const unsigned int _SAVEDTHEMESWINMINCOLS = 60;

// _TEXTWIN DIMENSION CONSTS
const unsigned int _TEXTWINSTARTY = 0;
const unsigned int _TEXTWINSTARTX = 0;
const unsigned int _TEXTWINLINES = 1;
const unsigned int _TEXTWINCOLS = 60;

#endif // _CURSESWINCONSTS_HPP
