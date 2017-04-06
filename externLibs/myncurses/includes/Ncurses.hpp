/*
** Ncurses.hpp for MyNcursesPP in /home/soszyn_h/Documents/Projects/MyNcursesPP/includes/Ncurses.hpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Thu Mar 30 15:39:11 2017 Hugo SOSZYNSKI
** Last update Thu Mar 30 15:39:13 2017 Hugo SOSZYNSKI
*/

#ifndef NCURSES_HPP_
# define NCURSES_HPP_

# include <exception>
# include <string>
# include <queue>
# include <map>
# include <ncurses.h>

typedef void (*handler)(void*);

/// \namespace myncurses
/// \brief The "myncurses" namespace regroup all the classes and functions of the library.
namespace myncurses
{
  /// \class Window
  /// \brief Class containing the ncurses window and the associated functions.
  class Window
  {
  public:
    /// \brief Main window object constructor, initialise the ncurses.
    Window();

    /// \brief Window object constructor (This constructor DOES NOT initialise the ncurses).
    /// \param nlines Number of lines of the window.
    /// \param ncols Number of columns of the window.
    /// \param begin_y Y position the window begin at.
    /// \param begin_x X position the window begin at.
    Window(int nLines, int nCols, int beginY, int beginX);

    /// \brief Copy constructor for a Window object (create a new window).
    ///        This cannot duplicate the main window.
    /// \param other Another Window object.
    Window(Window const& other);

    /// \brief Window object destructor.
    ~Window();

    /// \brief Copy operator for a Window object (create a new window).
    ///        This cannot duplicate the main window.
    /// \param other Another Window object.
    /// \return The object the given window was copied at.
    Window& operator=(Window const& other);

  public:
    /// \brief Getter for the number of lines in the Window.
    /// \return Return the number of lines in the Window.
    int getNbLines() const;

    /// \brief Getter for the number of columns in the Window.
    /// \return Return the number of columns in the Window.
    int getNbCols() const;

    /// \brief Getter for the X position th window begin at.
    /// \return Return the X position the Window begin at.
    int getBeginX() const;

    /// \brief Getter for the Y position th window begin at.
    /// \return Return the Y position the Window begin at.
    int getBeginY() const;

    /// \brief Getter for the ncurses WINDOW pointer.
    /// \return The constant ncurses WINDOW pointer.
    WINDOW* getWINDOW();

  public:
    /// \brief Analogous to the C printf and the ncurses function mvprintw.
    ///        Print the "printf" formatted output at the given position in the window.
    /// \param y Y position the text printed will begin at.
    /// \param x X position the text printed will begin at.
    /// \param fmt The "printf"-type formatted string.
    /// \param ... The arguments corresponding to the given format string.
    /// \return Return an integer return ERR upon failure and OK (SVr4 only specifies "an integer value other than ERR") upon successful completion.
    int mvprintw(int y, int x, std::string const& fmt, ...) const;

    /// \brief Check if your terminal has colors
    /// \return true if your terminal has colors, false otherwise
    bool hasColor() const;

    /// \brief It must be called if the programmer wants to use colors, and  before  any  other  color  manipulation  routine  is called.
    ///        It is good practice to call this routine right after initialising the main Window.
    ///        This routine affects all the Windows.
    /// \return Return the integer ERR upon failure and an OK (SVr4 specifies only "an integer value other than ERR") upon successful completion.
    int startColor() const;

    /// \brief Refer to ncurses init_pair() function for more details
    ///        This routine affects all the Windows.
    /// \param pair The number of the pair to modify (0 is the default background pair)
    /// \param f Front color
    /// \param b Backgtound color
    /// \return Return the integer ERR upon failure and an OK (SVr4 specifies only "an integer value other than ERR") upon successful completion.
    int initPair(short pair, short f, short b) const;

    /// \brief Turns on the named attributes without affecting any others.
    /// \param attr The attribute to set/
    /// \return Return the integer OK on success, or ERR on failure.
    int attributeOn(int attr) const;

    /// \brief Turns off the named attributes without affecting any others.
    /// \param attr The attribute to turn off.
    /// \return Return the integer OK on success, or ERR on failure.
    int attributeOff(int attr) const;

    /// \brief The screen is cleared completely on the next call to refresh for that window and repainted from scratch.
    /// \return Return the integer OK on success and ERR on failure.
    int clear() const;

    /// \brief Must be called to get actual output to the terminal.
    /// \return Return the integer OK on success and ERR on failure.
    int refresh() const;

    /// \brief The echo and noecho routines control whether characters typed by the user are echoed by getch as they are typed.
    ///        Initially getch is in echo mode, so characters typed are echoed.
    ///        This routine affects all the Windows.
    /// \return Return the integer OK on success and ERR on failure.
    int termEcho();

    /// \brief The echo and noecho routines control whether characters typed by the user are echoed by getch as they are typed.
    ///        Initially getch is in echo mode, so characters typed are echoed.
    ///        This routine affects all the Windows.
    /// \return Return the integer OK on success and ERR on failure.
    int termNoecho();

  protected:
    /// \brief Method to know if the current window is the stdscr.
    /// \return true if the window is stdscr, false otherwise.
    bool isStdscr() const;

    /// \brief Check if the ncurses has already benn initialised by user call to 'initscr'.
    /// \return true if the ncurses has already been initialised, false otherwise.
    bool isNcursesInitialised() const;

  protected:
    int		_nLines; //!< The number of line in the Window.
    int		_nCols; //!< The number of columns in the Window.
    int		_beginY; //!< The Y position the window begin at.
    int		_beginX; //!< The X position the window begin at.
    WINDOW	*_window; //!< The pointer to the ncurses WINDOW.
  };

  /// \class Events
  /// \brief Class containing the ncurses events handling.
  ///        This class must NOT be copied. You MUST use only ONE Events object by Window (undefined behavior).
  class Events
  {
  public:
    /// \brief Constructor for the Events object.
    /// \param window The Window object the Events will be associated with.
    Events(Window* window);

    /// \brief The destructor for the Events object.
    ~Events();

  public:
    /// \brief Method used to bind event to a function.
    ///        If an event has already been registered, the handler is replaced.
    ///        This method should never fail (in case of fail, an NcursesError exception is thrown).
    /// \param key The key you want to bind the handler to.
    /// \param handler The handler you ant to bind to the key (handler's prototype: "void handler(void *);").
    /// \param param The parameter to pass to the handler.
    void registerEvent(int key, handler func, void* param);

    /// \brief Method used to save the user inputs queue deleting all inputs not already registered.
    void inputs();

    /// \brief Method used to execute the handlers of the event already saved in the user inputs queue.
    void events();

    /// \brief The keypad option enables the keypad of the user's terminal. If enabled (bf is TRUE), the user can press a function key (such as an arrow key).
    ///        If disabled (bf is FALSE), curses does not treat function keys specially and the program has to interpret the escape sequences itself.
    ///        The default value for keypad is FALSE.
    /// \param bf Boolean used to turn-on/off the keypad.
    /// \return Return the integer OK on success and ERR on failure.
    int termKeypad(bool bf) const;

    /// \brief The nodelay option causes Events to have non-blocking call.
    ///        If disabled (bf is  FALSE), Events waits until a key is pressed.
    ///        The default value for nodelay is FALSE.
    /// \param bf Boolean used to turn-on/off the blocking keyboard handling.
    /// \return Return the integer OK on success and ERR on failure.
    int tremNodelay(bool bf) const;

    /// \brief The raw and noraw routines place the terminal into or out of raw mode.
    ///        Characters typed are immediately passed through to the user program
    ///        This routine affects all the Windows.
    /// \return Return the integer OK on success and ERR on failure.
    int termRaw() const;

    /// \brief The noraw routine returns the terminal to normal mode.
    ///        This routine affects all the Windows.
    /// \return Return the integer OK on success and ERR on failure.
    int termNoraw() const;

  protected:
    Window*			_window; //!< Window the events are associated with.
    std::map<int, handler>	_handlers; //!< Map of bind events handlers.
    std::map<int, void*>	_params; //!< Map of bind events handler's params.
    std::queue<int>		_inputs; //!< Queue of events to be executed.
  };

  /// \class NcursesError
  /// \brief Exception type specific to the MyNcursesPP library.
  class NcursesError: public std::exception
  {
  public:
    /// \brief Constructor of the exception.
    /// \param msg The error message associated with the exception.
    NcursesError(std::string msg);
    ~NcursesError() throw() {};

  public:
    /// \brief Get the message associated to the exception.
    /// \return The error message associated with the exception.
    const char* what() const throw();

  protected:
    std::string _message; //!< String containing the message associated to the exception.
  };
}

#endif // !NCURSES_HPP_