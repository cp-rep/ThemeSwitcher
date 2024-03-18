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
  // stdscr
  _MAINWIN,

  // main wins
  _HELPWIN,
  _PROGRAMSWIN,
  _PROMPTWIN,
  _SAVEDFILESWIN,
  _SAVEDTHEMESWIN,

  // secondary wins
  _SAVEDFILESWINSAVED,
  _SAVEDFILESWINTHEMES,
  _SAVEDTHEMESSAVEDWIN,
  _PROGRAMSWINSAVED,

  // text win
  _TEXTWIN
};

// _PROMPTWIN DIMENSION CONSTS
const unsigned int _PROMPTWINSTARTY = 2;
const unsigned int _PROMPTWINSTARTX = 2;
const unsigned int _PROMPTWINLINES = 10;
const unsigned int _PROMPTWINCOLS = 120;

// _SAVEDFILESWIN DIMENSION CONSTS
const unsigned int _SAVEDFILESWINSTARTY = 2;
const unsigned int _SAVEDFILESWINSTARTX = 2;
const unsigned int _SAVEDFILESWINLINES = 10;
const unsigned int _SAVEDFILESWINCOLS = 120;

// _SAVEDTHEMESWIN DIMENSION CONSTS
const unsigned int _SAVEDTHEMESWINSTARTY = 0;
const unsigned int _SAVEDTHEMESWINSTARTX = 0;
const unsigned int _SAVEDTHEMESWINLINES = 0;
const unsigned int _SAVEDTHEMESWINCOLS = 0;

// _PROGRAMSWIN DIMENSION CONSTS
const unsigned int _PROGRAMSWINSTARTY = 2;
const unsigned int _PROGRAMSWINSTARTX = 2;
const unsigned int _PROGRAMSWINLINES = 10;
const unsigned int _PROGRAMSWINCOLS = 120;

// _HELPWIN DIMENSION CONSTS
const unsigned int _HELPWINSTARTY = 2;
const unsigned int _HELPWINSTARTX = 2;
const unsigned int _HELPWINLINES = 10;
const unsigned int _HELPWINCOLS = 120;

// _TEXTWIN DIMENSION CONSTS
const unsigned int _TEXTWINSTARTY = 0;
const unsigned int _TEXTWINSTARTX = 0;
const unsigned int _TEXTWINLINES = 1;
const unsigned int _TEXTWINCOLS = 60;

#endif // _CURSESWINCONSTS_HPP
