#ifndef FEHLCD_H
#define FEHLCD_H

// #include "spi.h"
// #include "derivative.h"
#include <stdint.h>
#include <cstring>
#include <string>
#include "tigr.h"
#include "LCDColors.h"


#define LCD_WIDTH 320
#define LCD_HEIGHT 240


class FEHLCD
{
// The FEHLCD class is a singleton class, meaning that only one instance of it can exist at a time
// Make the FEHImage class a friend so it can access the Tigr *screen
// Do not let the user access the Tigr *screen directly
    friend class FEHImage;
    // friend class FEHKeyboard;
protected:
    Tigr *screen;

public:

    //TODO(AdamExley): Enforce singleton pattern
    
    /// @private
    FEHLCD();

    /// @private
    ~FEHLCD() {}

    /// @name Touch Functions
    ///@{
    /// @brief Check if the screen has been touched
    /// @param x_pos Pointer to a variable to store the x position of the cursor
    /// @param y_pos Pointer to a variable to store the y position of the cursor
    /// @param update_screen If true, calls Update() before checking for click. If false, uses data from the last Update() call
    /// @return true if a click was detected, false otherwise
    /// @note Pointer values are set regardless of whether or not a click was detected
    bool Touch(int *x_pos, int *y_pos, bool update_screen = true);
    bool Touch(float *x_pos, float *y_pos, bool update_screen = true);
    ///@}

    /// @private
    /// @brief One-time setup for LCD object
    void Initialize();

    /// @brief Clear the screen to a specific color
    /// @param color Color to clear the screen to
    void Clear(unsigned int color);
    
    /// @brief Clear the screen to current background color
    void Clear();

    /// @brief Update the screen, drawing all changes since the last Update() call and checking for any type of user input
    /// @note This function must be called for the user to see any changes made to the screen
    void Update();

    /// @brief Set the font color, which is the color used for writing text AND drawing shapes
    /// @param color Color to set
    void SetFontColor(unsigned int color);

    /// @brief Set the background color of the screen, this is the color that will be drawn when using the Clear() function without a color parameter
    /// @param color Background color to set
    void SetBackgroundColor(unsigned int color);

    /// @name Drawing Functions
    ///@{
    /// @brief Draw a pixel at the specified location
    void DrawPixel(int x, int y);
    void DrawLine(int x1, int y1, int x2, int y2);
    void DrawRectangle(int x, int y, int width, int height);
    void FillRectangle(int x, int y, int width, int height);
    void DrawCircle(int x0, int y0, int r);
    void FillCircle(int x0, int y0, int r);
    void DrawHorizontalLine(int y, int x1, int x2);
    void DrawVerticalLine(int x, int y1, int y2);
    ///@}

    /// @name Write At
    ///@{
    /// @brief Write information at a specific pixel location on the screen
    /// @param val The value to write
    /// @param x The x coordinate to start writing at
    /// @param y The y coordinate to start writing at
    /// @see WriteRC() for writing at a specific row and column of the text grid
    void WriteAt(const char *val, int x, int y);
    void WriteAt(std::string val, int x, int y);
    void WriteAt(int val, int x, int y);
    void WriteAt(float val, int x, int y);
    void WriteAt(double val, int x, int y);
    void WriteAt(bool val, int x, int y);
    void WriteAt(char val, int x, int y);
    ///@}

    /// @name Write RC
    ///@{
    /// @brief Write information at a specific row and column on the screen
    /// @param val The value to write
    /// @param row The row to start writing at
    /// @param col The column to start writing at
    /// @see WriteAt() for writing at a specific pixel location
    /// @note Uses row and column for standard text positioning
    void WriteRC(const char *val, int row, int col);
    void WriteRC(int val, int row, int col);
    void WriteRC(float val, int row, int col);
    void WriteRC(double val, int row, int col);
    void WriteRC(bool val, int row, int col);
    void WriteRC(char val, int row, int col);
    ///@}


    /// @name Write
    ///@{
    /// @brief Write information to the screen
    /// @param val The value to write
    void Write(const char *val);
    void Write(int    val);
    void Write(float  val);
    void Write(double val);
    void Write(bool   val);
    void Write(char   val);
    ///@}

    /// @name Write Line
    ///@{
    /// @brief Write information to the screen and move to the next text line
    void WriteLine(const char *val);
    void WriteLine(std::string val);
    void WriteLine(int    val);
    void WriteLine(float  val);
    void WriteLine(double val);
    void WriteLine(bool   val);
    void WriteLine(char   val);
    ///@}

    // Color modification
    unsigned int ScaleColor(unsigned int color, float scale);

protected:
    TPixel FEH2Tigr(unsigned int color) {return tigrRGB((char)(color >> 16), (char)(color >> 8), (char)color);}

private:

    /// @brief Internal function to draw a line on the screen
    /// @note Does not check for bounds, not intended for public use
    void _DrawLine(int x1, int y1, int x2, int y2);


    int abs(int n) { return n > 0 ? n : -n; }

    void _Initialize();
    void _Clear();

    void WriteChar(int row, int col, char c);
    void WriteCharAt(int x, int y, char c);

    unsigned int Convert24BitColorTo16Bit(unsigned int color);
    unsigned int ConvertRGBColorTo16Bit(unsigned char r, unsigned char g, unsigned char b);

    void NextLine();
    void CheckLine();
    void NextChar();

    int _maxlines;
    int _maxcols;
    int _width;
    int _height;
    int _currentline;
    int _currentchar;
    unsigned int _forecolor;
    unsigned int _backcolor;


    TPixel tigr_forecolor() { return FEH2Tigr(_forecolor); }
    TPixel tigr_backcolor() { return FEH2Tigr(_backcolor); }

    static unsigned char fontData[];
};

namespace FEHIcon
{
    /* Class definition for software icons */
    class Icon
    {
    private:
        int x_start, x_end;
        int y_start, y_end;
        int width;
        int height;
        unsigned int color;
        unsigned int textcolor;
        char label[200];
        int set;

    public:
        Icon();
        void SetProperties(char name[20], int start_x, int start_y, int w, int h, unsigned int c, unsigned int tc);
        void Draw();
        void Select();
        void Deselect();
        int Pressed(float x, float y, int mode);
        int WhilePressed(float xi, float yi);
        void ChangeLabelString(const char new_label[20]);
        void ChangeLabelFloat(float val);
        void ChangeLabelInt(int val);
    };

    /* Function prototype for drawing an array of icons in a rows by cols array with top, bot, left, and right margins from edges of screen, labels for each icon from top left across each row to the bottom right, and color for the rectangle and the text color */
    void DrawIconArray(Icon icon[], int rows, int cols, int top, int bot, int left, int right, char labels[][20], unsigned int col, unsigned int txtcol);
}

extern FEHLCD LCD;

#endif // FEHLCD_H
