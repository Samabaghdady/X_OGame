#pragma once
#ifndef TICTACTOE_H
#define TICTACTOE_H


#include <wx/mediactrl.h>

#include <wx/wx.h>

#include <wx/sound.h>
#include <wx/timer.h>

#include <map>
using namespace std;

class TicTacToeGUI : public wxFrame {
private:
    //GUI ELEMENTS
    wxButton* boardButtons[9];    // Buttons for the Tic Tac Toe board
    wxStaticText* statusText;     // Status bar for game updates
    wxStaticText* scoreText;      // Score display
    wxButton* resetButton;        // Reset button
    wxButton* themeToggleButton;  // Theme toggle button
    wxMediaCtrl* mediaCtrl;  // Media control for background music
    

    wxSound* backgroundSound;   // Pointer to background sound
    wxTimer* backgroundTimer;    // Timer to track the background sound duration
    int backgroundSoundPosition; // Elapsed time in seconds (you can adjust for precision)



    // Game state
    map<int, string> board;     //dictionary (Map)
    char nextStartingPlayer;      // To alternate the starting player
    char currentPlayer;           // Current player
    int playerXWins;              // Player X score
    int playerOWins;              // Player O score


    // Colors for the themes
    bool isDarkMode;              // Theme mode tracker
    //light theme
    wxColour lightBgColor;
    wxColour lightButtonColor;
    wxColour lightTextColor;
    //dark theme
    wxColour darkBgColor;
    wxColour darkButtonColor;
    wxColour darkTextColor;



    // Private methods
    void initializeBoard();
    void updateScore();
    bool checkWin(char player);
    bool checkDraw();
    bool ShowRestartPrompt(const wxString& message);
    
    // Event handlers
    void OnButtonClick(wxCommandEvent& event);
    void OnResetClick(wxCommandEvent& event);
    void OnThemeToggleClick(wxCommandEvent& event);


    void OnBackgroundSoundTimer(wxTimerEvent& event);
    

public:
    TicTacToeGUI();
    void OnKeyDown(wxKeyEvent& event);

};

#endif // TICTACTOE_H
