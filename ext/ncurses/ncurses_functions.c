/*
  +----------------------------------------------------------------------+
  | PHP Version 4                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997, 1998, 1999, 2000, 2001 The PHP Group             |
  +----------------------------------------------------------------------+
  | This source file is subject to version 2.02 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available at through the world-wide-web at                           |
  | http://www.php.net/license/2_02.txt.                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Authors: Hartmut Holzgraefe <hartmut@six.de>                         |
  |                                                                      |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "php_ncurses.h"

#define FETCH_WINRES(r, z)   ZEND_FETCH_RESOURCE(r, WINDOW *, z, -1, "ncurses_handle", le_ncurses); \
                                    if(!r) RETURN_FALSE;


/* {{{ proto int ncurses_addch(int ch)
   Add character at current position and advance cursor */
PHP_FUNCTION(ncurses_addch)
{
	long ch;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&ch)==FAILURE) {
        return;
	}
	
	RETURN_LONG(addch(ch));
}
/* }}} */

/* {{{ proto int ncurses_color_set(int pair)
   Set fore- and background color */
PHP_FUNCTION(ncurses_color_set)
{
#ifdef HAVE_NCURSES_COLOR_SET
	long pair;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&pair)==FAILURE) {
		return;
	}
	RETURN_LONG(color_set(pair,NULL));
#else
	php_error(E_WARNING,"%s not supported in this build");
	RETURN_FALSE;
#endif  
}
/* }}} */

/* {{{ proto int ncurses_delwin(resource window)
   Delete a ncurses window */
PHP_FUNCTION(ncurses_delwin)
{
	zval **handle;
	WINDOW *w;

	if (ZEND_NUM_ARGS() != 1 || zend_get_parameters_ex(1, &handle) == FAILURE){
		WRONG_PARAM_COUNT;
	}

	FETCH_WINRES(w,handle);

	zend_list_delete(Z_LVAL_PP(handle));
}
/* }}} */

/* {{{ proto int ncurses_end()
   Stop using ncurses, clean up the screen */
PHP_FUNCTION(ncurses_end)
{
	RETURN_LONG(endwin());             /* endialize the curses library */
}
/* }}} */

/* {{{ proto int ncurses_getch()
   Read a character from keyboard */
PHP_FUNCTION(ncurses_getch)
{
	RETURN_LONG(getch());
}
/* }}} */

/* {{{ proto bool ncurses_has_colors()
   Check if terminal has colors */
PHP_FUNCTION(ncurses_has_colors)
{
	RETURN_BOOL(has_colors());
}
/* }}} */

/* {{{ proto int ncurses_init()
   Initialize ncurses */
PHP_FUNCTION(ncurses_init)
{
	initscr();             /* initialize the curses library */
	keypad(stdscr, TRUE);  /* enable keyboard mapping */
	(void) nonl();         /* tell curses not to do NL->CR/NL on output */
	(void) cbreak();       /* take input chars one at a time, no wait for \n */}
/* }}} */

/* {{{ proto int ncurses_init_pair(int pair, int fg, int bg)
   Allocate a color pair */
PHP_FUNCTION(ncurses_init_pair)
{
	long pair, fg, bg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll",&pair,&fg,&bg)==FAILURE) {
		return;
	}
	
	RETURN_LONG(init_pair(pair,fg,bg));
}
/* }}} */

/* {{{ proto int ncurses_move(int y, int x)
   Move output position */
PHP_FUNCTION(ncurses_move)
{
	long x, y;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll",&y,&x)==FAILURE) {
		return;
	}
	RETURN_LONG(move(y,x));
}
/* }}} */


/* {{{ proto int ncurses_newwin(int rows, int cols, int y, int x)
   Create a new window */
PHP_FUNCTION(ncurses_newwin)
{
	long rows,cols,y,x;
	WINDOW **pwin = (WINDOW **)emalloc(sizeof(WINDOW *));

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llll",&rows,&cols,&y,&x)==FAILURE) {
		return;
	}
  
	*pwin=newwin(rows,cols,y,x);
  
	if(!*pwin) {
		efree(pwin);
		RETURN_FALSE;
	}

	ZEND_REGISTER_RESOURCE(return_value, pwin, le_ncurses);
}
/* }}} */

/* {{{ proto int ncurses_refresh(int ch)
   Refresh screen */
PHP_FUNCTION(ncurses_refresh)
{
	RETURN_LONG(refresh());
}
/* }}} */

/* {{{ proto int ncurses_start_color()
   Start using colors */
PHP_FUNCTION(ncurses_start_color)
{
	RETURN_LONG(start_color());
}
/* }}} */

/* {{{ proto int ncurses_standout()
   Start using 'standout' attribute */
PHP_FUNCTION(ncurses_standout)
{
	RETURN_LONG(standout());
}
/* }}} */

/* {{{ proto int ncurses_standend()
   Stop using 'standout' attribute */
PHP_FUNCTION(ncurses_standend)
{
	RETURN_LONG(standend());
}
/* }}} */

/* {{{ proto int ncurses_baudrate()
   Return baudrate of terminal */
PHP_FUNCTION(ncurses_baudrate)
{
	RETURN_LONG(baudrate());
}
/* }}} */

/* {{{ proto int ncurses_beep()
   Let the terminal beep */
PHP_FUNCTION(ncurses_beep)
{
	RETURN_LONG(beep());
}
/* }}} */

/* {{{ proto bool ncurses_can_change_color()
   Check if we can change terminals colors */
PHP_FUNCTION(ncurses_can_change_color)
{
	RETURN_LONG(can_change_color());
} 
/* }}} */

/* {{{ proto bool ncurses_cbreak()
   Switch of input buffering */
PHP_FUNCTION(ncurses_cbreak)
{
	RETURN_LONG(cbreak());
}
/* }}} */

/* {{{ proto bool ncurses_clear()
   Clear screen */
PHP_FUNCTION(ncurses_clear)
{
	RETURN_LONG(clear());
}
/* }}} */

/* {{{ proto bool ncurses_clrtobot()
   Clear screen from current position to bottom */
PHP_FUNCTION(ncurses_clrtobot)
{
	RETURN_LONG(clrtobot());
}
/* }}} */

/* {{{ proto bool ncurses_clrtoeol()
   Clear screen from current position to end of line */
PHP_FUNCTION(ncurses_clrtoeol)
{
	RETURN_LONG(clrtoeol());
}
/* }}} */

/* {{{ proto bool ncurses_def_prog_mode()
 */
PHP_FUNCTION(ncurses_def_prog_mode)
{
	RETURN_LONG(def_prog_mode());
}
/* }}} */

/* {{{ proto bool ncurses_def_shell_mode()
 */
PHP_FUNCTION(ncurses_def_shell_mode)
{
	RETURN_LONG(def_shell_mode());
}
/* }}} */

/* {{{ proto bool ncurses_delch()
   Delete character at current position, move rest of line left */
PHP_FUNCTION(ncurses_delch)
{
	RETURN_LONG(delch());
}
/* }}} */

/* {{{ proto bool ncurses_deleteln()
   Delete line at current position, move rest of screen up */
PHP_FUNCTION(ncurses_deleteln)
{
	RETURN_LONG(deleteln());
}
/* }}} */

/* {{{ proto bool ncurses_doupdate()
   Write all prepared refreshes to terminal */
PHP_FUNCTION(ncurses_doupdate)
{
	RETURN_LONG(doupdate());
}
/* }}} */

/* {{{ proto bool ncurses_echo()
   Activate keyboard input echo */
PHP_FUNCTION(ncurses_echo)
{
	RETURN_LONG(echo());
}
/* }}} */

/* {{{ proto bool ncurses_erase()
   Erease terminal screen */
PHP_FUNCTION(ncurses_erase)
{
	RETURN_LONG(erase());
}
/* }}} */

/* {{{ proto bool ncurses_erasechar()
   Return current erase character */
PHP_FUNCTION(ncurses_erasechar)
{
	RETURN_LONG(erasechar());
}
/* }}} */

/* {{{ proto bool ncurses_flash()
   Flash terminal screen (visual bell) */
PHP_FUNCTION(ncurses_flash)
{
	RETURN_LONG(flash());
}
/* }}} */

/* {{{ proto bool ncurses_flushinp()
   Flush keyboard input buffer */
PHP_FUNCTION(ncurses_flushinp)
{
	RETURN_LONG(flushinp());
}
/* }}} */

/* {{{ proto bool ncurses_has_ic()
   Check for insert- and delete-capabilities */
PHP_FUNCTION(ncurses_has_ic)
{
	RETURN_LONG(has_ic());
}
/* }}} */


/* {{{ proto bool ncurses_has_il()
   Check for line insert- and delete-capabilities */
PHP_FUNCTION(ncurses_has_il)
{
	RETURN_LONG(has_il());
}
/* }}} */

/* {{{ proto bool ncurses_inch()
   Get character and attribute at current position */
PHP_FUNCTION(ncurses_inch)
{
	RETURN_LONG(inch());
}
/* }}} */

/* {{{ proto bool ncurses_insertln()
   Insert a line, move rest of screen down */
PHP_FUNCTION(ncurses_insertln)
{
	RETURN_LONG(insertln());
}
/* }}} */

/* {{{ proto bool ncurses_isendwin()
   Ncurses is in endwin mode, normal screen output may be performed */
PHP_FUNCTION(ncurses_isendwin)
{
	RETURN_LONG(isendwin());
}
/* }}} */

/* {{{ proto bool ncurses_killchar()
   Return current line kill character */
PHP_FUNCTION(ncurses_killchar)
{
	RETURN_LONG(killchar());
}
/* }}} */

/* {{{ proto bool ncurses_nl()
   Translate newline and carriage return / line feed */
PHP_FUNCTION(ncurses_nl)
{
	RETURN_LONG(nl());
}
/* }}} */

/* {{{ proto bool ncurses_nocbreak()
   Switch terminal to cooked mode */
PHP_FUNCTION(ncurses_nocbreak)
{
	RETURN_LONG(nocbreak());
}
/* }}} */

/* {{{ proto bool ncurses_noecho()
   Switch off keyboard input echo */
PHP_FUNCTION(ncurses_noecho)
{
	RETURN_LONG(noecho());
}
/* }}} */

/* {{{ proto bool ncurses_nonl()
   Do not ranslate newline and carriage return / line feed */
PHP_FUNCTION(ncurses_nonl)
{
	RETURN_LONG(nonl());
}
/* }}} */

/* {{{ proto bool ncurses_noraw()
   Switch terminal out of raw mode */
PHP_FUNCTION(ncurses_noraw)
{
	RETURN_LONG(noraw());
}
/* }}} */

/* {{{ proto bool ncurses_raw()
   Switch terminal into raw mode */
PHP_FUNCTION(ncurses_raw)
{
	RETURN_LONG(raw());
}
/* }}} */

/* {{{ proto bool ncurses_resetty()
   Restore saved terminal state */
PHP_FUNCTION(ncurses_resetty)
{
	RETURN_LONG(resetty());
}
/* }}} */

/* {{{ proto bool ncurses_savetty()
   Save terminal state */
PHP_FUNCTION(ncurses_savetty)
{
	RETURN_LONG(savetty());
}
/* }}} */

/* {{{ proto bool ncurses_termattrs()
   Return a logical OR of all attribute flags supported by terminal */
PHP_FUNCTION(ncurses_termattrs)
{
	RETURN_LONG(termattrs());
}
/* }}} */

/* {{{ proto bool ncurses_use_default_colors()
   Assign terminal default colors to color id -1 */
PHP_FUNCTION(ncurses_use_default_colors)
{
	RETURN_LONG(use_default_colors());
}
/* }}} */

/* {{{ proto bool ncurses_slk_attr()
 */
PHP_FUNCTION(ncurses_slk_attr)
{
	RETURN_LONG(slk_attr());
}
/* }}} */

/* {{{ proto bool ncurses_slk_clear()
 */
PHP_FUNCTION(ncurses_slk_clear)
{
	RETURN_LONG(slk_clear());
}
/* }}} */

/* {{{ proto bool ncurses_slk_noutrefresh()
 */
PHP_FUNCTION(ncurses_slk_noutrefresh)
{
	RETURN_LONG(slk_noutrefresh());
}
/* }}} */

/* {{{ proto bool ncurses_slk_refresh()
 */
PHP_FUNCTION(ncurses_slk_refresh)
{
	RETURN_LONG(slk_refresh());
}
/* }}} */

/* {{{ proto bool ncurses_slk_restore()
 */
PHP_FUNCTION(ncurses_slk_restore)
{
	RETURN_LONG(slk_restore());
}
/* }}} */

/* {{{ proto bool ncurses_slk_touch()
 */
PHP_FUNCTION(ncurses_slk_touch)
{
	RETURN_LONG(slk_touch());
}
/* }}} */

/* {{{ proto int ncurses_attroff(int intarg)
   Turn off the given attributes */
PHP_FUNCTION(ncurses_attroff)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}
	
	RETURN_LONG(attroff(intarg));
}
/* }}} */

/* {{{ proto int ncurses_attron(int intarg)
   Turn on the given attributes */
PHP_FUNCTION(ncurses_attron)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}
	
	RETURN_LONG(attron(intarg));
}
/* }}} */

/* {{{ proto int ncurses_attrset(int intarg)
   Set given attributes */
PHP_FUNCTION(ncurses_attrset)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}
	
	RETURN_LONG(attrset(intarg));
}
/* }}} */

/* {{{ proto int ncurses_bkgd(int intarg)
   Set background property for terminal screen */
PHP_FUNCTION(ncurses_bkgd)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}
	
	RETURN_LONG(bkgd(intarg));
}
/* }}} */

/* {{{ proto int ncurses_curs_set(int intarg)
   Set cursor state */
PHP_FUNCTION(ncurses_curs_set)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}
	
	RETURN_LONG(curs_set(intarg));
}
/* }}} */

/* {{{ proto int ncurses_delay_output(int intarg)
   Delay output on terminal using padding characters */
PHP_FUNCTION(ncurses_delay_output)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}
	
	RETURN_LONG(delay_output(intarg));
}
/* }}} */

/* {{{ proto int ncurses_echochar(int intarg)
   Single character output including refresh */
PHP_FUNCTION(ncurses_echochar)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}
	
	RETURN_LONG(echochar(intarg));
}
/* }}} */

/* {{{ proto int ncurses_halfdelay(int intarg)
   Put terminal into halfdelay mode */
PHP_FUNCTION(ncurses_halfdelay)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}
	
	RETURN_LONG(halfdelay(intarg));
}
/* }}} */

/* {{{ proto int ncurses_has_key(int intarg)
   Check for presence of a function key on terminal keyboard */
PHP_FUNCTION(ncurses_has_key)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}
	
	RETURN_LONG(has_key(intarg));
}
/* }}} */

/* {{{ proto int ncurses_insch(int intarg)
   Insert character moving rest of line including character at current position */
PHP_FUNCTION(ncurses_insch)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}
	
	RETURN_LONG(insch(intarg));
}
/* }}} */

/* {{{ proto int ncurses_insdelln(int intarg)
   Insert lines before current line scrolling down (negative numbers delete and scroll up) */
PHP_FUNCTION(ncurses_insdelln)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}
	
	RETURN_LONG(insdelln(intarg));
}
/* }}} */

/* {{{ proto int ncurses_mouseinterval(int intarg)
   Set timeout for mouse button clicks */
PHP_FUNCTION(ncurses_mouseinterval)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}
	
	RETURN_LONG(mouseinterval(intarg));
}
/* }}} */

/* {{{ proto int ncurses_napms(int intarg)
   �s sleep */
PHP_FUNCTION(ncurses_napms)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}
	
	RETURN_LONG(napms(intarg));
}
/* }}} */

/* {{{ proto int ncurses_scrl(int intarg)
   Scroll window content up or down without changing current position */
PHP_FUNCTION(ncurses_scrl)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}
	
	RETURN_LONG(scrl(intarg));
}
/* }}} */

/* {{{ proto int ncurses_slk_attroff(int intarg)
 */
PHP_FUNCTION(ncurses_slk_attroff)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}
	
	RETURN_LONG(slk_attroff(intarg));
}
/* }}} */

/* {{{ proto int ncurses_slk_attron(int intarg)
 */
PHP_FUNCTION(ncurses_slk_attron)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}

	RETURN_LONG(slk_attron(intarg));
}
/* }}} */

/* {{{ proto int ncurses_slk_attrset(int intarg)
 */
PHP_FUNCTION(ncurses_slk_attrset)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}

	RETURN_LONG(slk_attrset(intarg));
}
/* }}} */

/* {{{ proto int ncurses_slk_color(int intarg)
 */
PHP_FUNCTION(ncurses_slk_color)
{
#ifdef HAVE_NCURSES_SLK_COLOR
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}

	RETURN_LONG(slk_color(intarg));
#else
	php_error(E_WARNING,"%s not supported in this build");
	RETURN_FALSE;
#endif  
}
/* }}} */

/* {{{ proto int ncurses_slk_init(int intarg)
 */
PHP_FUNCTION(ncurses_slk_init)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}

	RETURN_LONG(slk_init(intarg));
}
/* }}} */

/* {{{ proto int ncurses_typeahead(int intarg)
   Specify different filedescriptor for typeahead checking */
PHP_FUNCTION(ncurses_typeahead)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}

	RETURN_LONG(typeahead(intarg));
}
/* }}} */

/* {{{ proto int ncurses_ungetch(int intarg)
   Put a character back into the input stream */
PHP_FUNCTION(ncurses_ungetch)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}

	RETURN_LONG(ungetch(intarg));
}
/* }}} */

/* {{{ proto int ncurses_vidattr(int intarg)
 */
PHP_FUNCTION(ncurses_vidattr)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}

	RETURN_LONG(vidattr(intarg));
}
/* }}} */

/* {{{ proto int ncurses_use_extended_names(int intarg)
   Control use of extended names in terminfo descriptions */
PHP_FUNCTION(ncurses_use_extended_names)
{
#ifdef HAVE_NCURSES_USE_EXTENDED_NAMES
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}

	RETURN_LONG(use_extended_names(intarg));
#else
	php_error(E_WARNING,"%s not supported in this build");
	RETURN_FALSE;
#endif  
}
/* }}} */

/* {{{ proto void ncurses_bkgdset(int intarg)
   Control screen background */
PHP_FUNCTION(ncurses_bkgdset)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}

	bkgdset(intarg);
}
/* }}} */

/* {{{ proto int ncurses_filter()
 */
PHP_FUNCTION(ncurses_filter)
{
	filter();
}
/* }}} */

/* {{{ proto int ncurses_noqiflush()
   Do not flush on signal characters*/
PHP_FUNCTION(ncurses_noqiflush)
{
	noqiflush();
}
/* }}} */

/* {{{ proto int ncurses_qiflush()
   Flush on signal characters */
PHP_FUNCTION(ncurses_qiflush)
{
	qiflush();
}
/* }}} */

/* {{{ proto void ncurses_timeout(int intarg)
   Set timeout for special key sequences */
PHP_FUNCTION(ncurses_timeout)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}

	timeout(intarg);
}
/* }}} */

/* {{{ proto void ncurses_use_env(int intarg)
   Control use of environment information about terminal size */
PHP_FUNCTION(ncurses_use_env)
{
	long intarg;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l",&intarg)==FAILURE) {
		return;
	}

	use_env(intarg);
}
/* }}} */

/* {{{ proto int ncurses_addstr(string text)
   Output text at current position */
PHP_FUNCTION(ncurses_addstr)
{
	char *str;
	int str_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",&str,&str_len)==FAILURE) {
		return;
	}

	RETURN_LONG(addstr(str));
}
/* }}} */

/* {{{ proto int ncurses_putp(string text)
 */
PHP_FUNCTION(ncurses_putp)
{
	char *str;
	int str_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",&str,&str_len)==FAILURE) {
		return;
	}

	RETURN_LONG(putp(str));
}
/* }}} */

/* {{{ proto int ncurses_scr_dump(string text)
   Dump screen content to file */
PHP_FUNCTION(ncurses_scr_dump)
{
	char *str;
	int str_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",&str,&str_len)==FAILURE) {
		return;
	}

	RETURN_LONG(scr_dump(str));
}
/* }}} */

/* {{{ proto int ncurses_scr_init(string text)
   Initialize screen from file dump */
PHP_FUNCTION(ncurses_scr_init)
{
	char *str;
	int str_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",&str,&str_len)==FAILURE) {
		return;
	}

	RETURN_LONG(scr_init(str));
}
/* }}} */

/* {{{ proto int ncurses_scr_restore(string text)
   Restore screen from file dump */
PHP_FUNCTION(ncurses_scr_restore)
{
	char *str;
	int str_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",&str,&str_len)==FAILURE) {
		return;
	}

	RETURN_LONG(scr_restore(str));
}
/* }}} */

/* {{{ proto int ncurses_scr_set(string text)
   Inherit screen from file dump */
PHP_FUNCTION(ncurses_scr_set)
{
	char *str;
	int str_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",&str,&str_len)==FAILURE) {
		return;
	}

	RETURN_LONG(scr_set(str));
}
/* }}} */

/* {{{ proto int ncurses_mvaddch(int y, int x, int c)
   Move current position and add character */
PHP_FUNCTION(ncurses_mvaddch)
{
	long y,x,c;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll",&y,&x,&c)==FAILURE) {
        return;
	}
	
	RETURN_LONG(mvaddch(y,x,c));
}
/* }}} */

/* {{{ proto int ncurses_mvaddchnstr(int y, int x, string s, int n)
   Move position and add attrributed string with specified length */
PHP_FUNCTION(ncurses_mvaddchnstr)
{
	long y,x,n;
	char *str;
	int str_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llsl",&y,&x,&str,&str_len,&n)==FAILURE) {
        return;
	}
	
	RETURN_LONG(mvaddchnstr(y,x,(chtype *)str,n));
}
/* }}} */

/* {{{ proto int ncurses_addchnstr(string s, int n)
   Add attributed string with specified length at current position */
PHP_FUNCTION(ncurses_addchnstr)
{
	long n;
	char *str;
	int str_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl",&str,&str_len,&n)==FAILURE) {
        return;
	}
	
	RETURN_LONG(addchnstr((chtype *)str,n));
}
/* }}} */

/* {{{ proto int ncurses_mvaddchstr(int y, int x, string s)
   Move position and add attributed string */
PHP_FUNCTION(ncurses_mvaddchstr)
{
	long y,x;
	char *str;
	int str_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lls",&y,&x,&str,&str_len)==FAILURE) {
        return;
	}
	
	RETURN_LONG(mvaddchstr(y,x,(chtype *)str));
}
/* }}} */

/* {{{ proto int ncurses_addchstr(string s)
   Add attributed string at current position */
PHP_FUNCTION(ncurses_addchstr)
{
	char *str;
	int str_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",&str,&str_len)==FAILURE) {
		return;
	}
	
	RETURN_LONG(addchstr((chtype *)str));
}
/* }}} */

/* {{{ proto int ncurses_mvaddnstr(int y, int x, string s, int n)
   Move position and add string with specified length */
PHP_FUNCTION(ncurses_mvaddnstr)
{
	long y,x,n;
	char *str;
	int str_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llsl",&y,&x,&str,&str_len,&n)==FAILURE) {
        return;
	}
	
	RETURN_LONG(mvaddnstr(y,x,str,n));
}
/* }}} */

/* {{{ proto int ncurses_addnstr(string s, int n)
   Add string with specified length at current position */
PHP_FUNCTION(ncurses_addnstr)
{
	long n;
	char *str;
	int str_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl",&str,&str_len,&n)==FAILURE) {
        return;
	}
	
	RETURN_LONG(addnstr(str,n));
}
/* }}} */

/* {{{ proto int ncurses_mvaddstr(int y, int x, string s)
   Move position and add string */
PHP_FUNCTION(ncurses_mvaddstr)
{
	long y,x;
	char *str;
	int str_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lls",&y,&x,&str,&str_len)==FAILURE) {
        return;
	}
	
	RETURN_LONG(mvaddstr(y,x,str));
}
/* }}} */

/* {{{ proto int ncurses_mvdelch(int y, int x)
   Move position and delete character, shift rest of line left */
PHP_FUNCTION(ncurses_mvdelch)
{
	long y,x;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lls",&y,&x)==FAILURE) {
        return;
	}
	
	RETURN_LONG(mvdelch(y,x));
}
/* }}} */


/* {{{ proto int ncurses_mvgetch(int y, int x)
   Move position and get character at new position */
PHP_FUNCTION(ncurses_mvgetch)
{
	long y,x;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lls",&y,&x)==FAILURE) {
        return;
	}
	
	RETURN_LONG(mvgetch(y,x));
}
/* }}} */

/* {{{ proto int ncurses_mvinch(int y, int x)
   Move position and get attributed character at new position */
PHP_FUNCTION(ncurses_mvinch)
{
	long y,x;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lls",&y,&x)==FAILURE) {
        return;
	}
	
	RETURN_LONG(mvinch(y,x));
}
/* }}} */

/* {{{ proto int ncurses_insstr(string)
   Insert string at current position, moving rest of line right */
PHP_FUNCTION(ncurses_insstr)
{
	char *str;
	int str_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",&str,&str_len)==FAILURE) {
		return;
	}
	
	RETURN_LONG(insstr(str));
}
/* }}} */

/* {{{ proto int ncurses_instr(string)
 */
PHP_FUNCTION(ncurses_instr)
{
	char *str;
	int str_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",&str,&str_len)==FAILURE) {
		return;
	}
	
	RETURN_LONG(instr(str));
}
/* }}} */

/* {{{ proto int ncurses_mvhline(int,int,int,int)
 */
PHP_FUNCTION(ncurses_mvhline)
{
	long i1,i2,i3,i4;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llll",&i1,&i2,&i3,&i4)==FAILURE) {
        return;
	}
	
	RETURN_LONG(mvhline(i1,i2,i3,i4));
}
/* }}} */

/* {{{ proto int ncurses_mvcur(int,int,int,int)
 */
PHP_FUNCTION(ncurses_mvcur)
{
	long i1,i2,i3,i4;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llll",&i1,&i2,&i3,&i4)==FAILURE) {
        return;
	}
	
	RETURN_LONG(mvcur(i1,i2,i3,i4));
}
/* }}} */

/* {{{ proto int ncurses_init_color(int,int,int,int)
 */
PHP_FUNCTION(ncurses_init_color)
{
	long i1,i2,i3,i4;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llll",&i1,&i2,&i3,&i4)==FAILURE) {
        return;
	}
	
	RETURN_LONG(init_color(i1,i2,i3,i4));
}
/* }}} */

/* {{{ proto int ncurses_border(int,int,int,int,int,int,int,int)
 */
PHP_FUNCTION(ncurses_border)
{
	long i1,i2,i3,i4,i5,i6,i7,i8;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llllllll",&i1,&i2,&i3,&i4,&i5,&i6,&i7,&i8)==FAILURE) {
        return;
	}
	
	RETURN_LONG(border(i1,i2,i3,i4,i5,i6,i7,i8));
}
/* }}} */

/* {{{ proto int ncurses_assume_default_colors(int,int)
 */
PHP_FUNCTION(ncurses_assume_default_colors)
{
#ifdef HAVE_NCURSES_ASSUME_DEFAULT_COLORS
	long i1,i2;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll",&i1,&i2)==FAILURE) {
        return;
	}
	
	RETURN_LONG(assume_default_colors(i1,i2));
#else
	php_error(E_WARNING,"%s not supported in this build");
	RETURN_FALSE;
#endif  
}
/* }}} */

/* {{{ proto int ncurses_define_key(string,int)
 */
PHP_FUNCTION(ncurses_define_key)
{
	long n;
	char *str;
	int str_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl",&str,&str_len,&n)==FAILURE) {
        return;
	}
	
	RETURN_LONG(define_key(str,n));
}
/* }}} */

/* {{{ proto int ncurses_hline(int,int)
 */
PHP_FUNCTION(ncurses_hline)
{
	long i1,i2;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll",&i1,&i2)==FAILURE) {
        return;
	}
	
	RETURN_LONG(hline(i1,i2));
}
/* }}} */

/* {{{ proto int ncurses_vline(int,int)
 */
PHP_FUNCTION(ncurses_vline)
{
	long i1,i2;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll",&i1,&i2)==FAILURE) {
        return;
	}
	
	RETURN_LONG(vline(i1,i2));
}
/* }}} */

/* {{{ proto int ncurses_keyok(int,bool)
 */
PHP_FUNCTION(ncurses_keyok)
{
	long i,b;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll",&i,&b)==FAILURE) {
        return;
	}
	
	RETURN_LONG(hline(i,b));
}
/* }}} */

/* {{{ proto int ncurses_mvwaddstr(resource window, int y, int x, string text)
 */
PHP_FUNCTION(ncurses_mvwaddstr)
{
	zval **handle, **x, **y, **text;
	WINDOW **w;

	if (ZEND_NUM_ARGS() != 4 || zend_get_parameters_ex(4, &handle, &y, &x, &text) == FAILURE){
		WRONG_PARAM_COUNT;
	}

	FETCH_WINRES(w,handle);

	convert_to_long_ex(y);
	convert_to_long_ex(x);
	convert_to_string_ex(text);


	RETURN_LONG(mvwaddstr(*w,Z_LVAL_PP(y),Z_LVAL_PP(x),Z_STRVAL_PP(text)));
}
/* }}} */

/* {{{ proto int ncurses_wrefresh(resource window)
 */
PHP_FUNCTION(ncurses_wrefresh)
{
	zval **handle;
	WINDOW **w;

	if (ZEND_NUM_ARGS() != 1 || zend_get_parameters_ex(1, &handle) == FAILURE){
		WRONG_PARAM_COUNT;
	}

	FETCH_WINRES(w,handle);

	RETURN_LONG(wrefresh(*w));
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
