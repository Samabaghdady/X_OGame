#include "TicTacToe.h"

// Constructor for TicTacToeGUI
TicTacToeGUI::TicTacToeGUI()
    : wxFrame(nullptr, wxID_ANY, "Modern Tic Tac Toe", wxDefaultPosition, wxSize(400, 600)),
    nextStartingPlayer('X'), playerXWins(0), playerOWins(0), isDarkMode(false),
    lightBgColor(255, 255, 255), lightButtonColor(240, 240, 240), lightTextColor(51, 51, 51),
    darkBgColor(18, 18, 18), darkButtonColor(44, 44, 44), darkTextColor(234, 234, 234) {

    SetBackgroundColour(lightBgColor);
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    //Background Music
    wxSound backgroundSound("background.wav");
    backgroundSound.Play(wxSOUND_ASYNC | wxSOUND_LOOP);

    // Create a grid sizer for the board
    wxGridSizer* gridSizer = new wxGridSizer(3, 3, 5, 5);
    for (int i = 0; i < 9; ++i) {
        boardButtons[i] = new wxButton(panel, 1000 + i, "", wxDefaultPosition, wxSize(100, 100));
        boardButtons[i]->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        boardButtons[i]->SetBackgroundColour(lightButtonColor);
        boardButtons[i]->SetForegroundColour(lightTextColor);
        gridSizer->Add(boardButtons[i], 1, wxEXPAND | wxALL, 5);
        boardButtons[i]->Bind(wxEVT_BUTTON, &TicTacToeGUI::OnButtonClick, this);
    }

    // Status text
    statusText = new wxStaticText(panel, wxID_ANY, "Player X's turn", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    statusText->SetForegroundColour(lightTextColor);

    // Score text
    scoreText = new wxStaticText(panel, wxID_ANY, "Player X: 0 | Player O: 0", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    scoreText->SetForegroundColour(lightTextColor);

    // Reset button
    resetButton = new wxButton(panel, wxID_ANY, "Restart Game", wxDefaultPosition, wxSize(100, 30));
    resetButton->SetBackgroundColour(lightButtonColor);
    resetButton->SetForegroundColour(lightTextColor);
    resetButton->Bind(wxEVT_BUTTON, &TicTacToeGUI::OnResetClick, this);

    // Theme toggle button
    themeToggleButton = new wxButton(panel, wxID_ANY, "Toggle Theme", wxDefaultPosition, wxSize(150, 30));
    themeToggleButton->SetBackgroundColour(lightButtonColor);
    themeToggleButton->SetForegroundColour(lightTextColor);
    themeToggleButton->Bind(wxEVT_BUTTON, &TicTacToeGUI::OnThemeToggleClick, this);

    // Layout // create a vertical box sizer
    wxBoxSizer* vSizer = new wxBoxSizer(wxVERTICAL);
    vSizer->Add(gridSizer, 1, wxEXPAND | wxALL, 10);
    vSizer->Add(statusText, 0, wxALIGN_CENTER | wxALL, 10);
    vSizer->Add(scoreText, 0, wxALIGN_CENTER | wxALL, 5);
    vSizer->Add(resetButton, 0, wxALIGN_CENTER | wxALL, 5);
    vSizer->Add(themeToggleButton, 0, wxALIGN_CENTER | wxALL, 5);

    panel->SetSizer(vSizer);
    initializeBoard();

    // Bind key down event
    this->Bind(wxEVT_CHAR_HOOK, &TicTacToeGUI::OnKeyDown, this);
}
void TicTacToeGUI::OnKeyDown(wxKeyEvent& event) {
    if (event.GetKeyCode() == 'R' || event.GetKeyCode() == 'r') {
        int response = wxMessageBox("Are you sure you want to restart the game?", "Confirm Restart", wxYES_NO | wxICON_QUESTION);
        if (response == wxYES) {

            initializeBoard();
        }
    }
    else {
        event.Skip();
    }
}
void TicTacToeGUI::initializeBoard() {
    for (int i = 0; i < 9; ++i) {
        board[i] = ' ';
        boardButtons[i]->SetLabel("");
        boardButtons[i]->Enable();
        boardButtons[i]->SetBackgroundColour(isDarkMode ? darkButtonColor : lightButtonColor);
    }
    currentPlayer = nextStartingPlayer;
    statusText->SetLabel(wxString::Format("Player %c's turn", currentPlayer));
}
void TicTacToeGUI::updateScore() {
    scoreText->SetLabel(wxString::Format("Player X: %d | Player O: %d", playerXWins, playerOWins));
}
bool TicTacToeGUI::checkWin(char player) {
    return (
        (board[0] == player && board[1] == player && board[2] == player) || // Rows
        (board[3] == player && board[4] == player && board[5] == player) ||
        (board[6] == player && board[7] == player && board[8] == player) ||
        (board[0] == player && board[3] == player && board[6] == player) || // Columns
        (board[1] == player && board[4] == player && board[7] == player) ||
        (board[2] == player && board[5] == player && board[8] == player) ||
        (board[0] == player && board[4] == player && board[8] == player) || // Diagonals
        (board[2] == player && board[4] == player && board[6] == player)
    );
}
bool TicTacToeGUI::checkDraw() {
    for (int i = 0; i < 9; ++i) {
        if (board[i] == ' ') return false;
    }
    return true;
}
bool TicTacToeGUI::ShowRestartPrompt(const wxString& message) {
    int response = wxMessageBox(message, "Game Over", wxYES_NO | wxICON_QUESTION);
    return (response == wxYES);
}

void TicTacToeGUI::OnButtonClick(wxCommandEvent& event) {
    int id = event.GetId();
    int index = id - 1000; // Map button ID to board index

    // Check if the button is already clicked
    if (board[index] != ' ') {
        wxMessageBox("Invalid move!", "Error", wxICON_ERROR);
        return;
    }

    // Update board and button label
    board[index] = currentPlayer;
    boardButtons[index]->SetLabel(wxString::Format("%c", currentPlayer));
    boardButtons[index]->SetForegroundColour(currentPlayer == 'X' ? *wxRED : *wxBLUE);

    // Play move sound asynchronously so it doesn't block the background sound
    /*wxSound moveSound("move.wav");
    moveSound.Play(wxSOUND_ASYNC);*/

    // Check for a win or draw
    if (checkWin(currentPlayer)) {
        if (currentPlayer == 'X')
            playerXWins++;
        else playerOWins++;

        // Update the next starting player
        nextStartingPlayer = (currentPlayer == 'X') ? 'O' : 'X';


        updateScore();
        if (ShowRestartPrompt(wxString::Format("Player %c wins! Play a new game?", currentPlayer))) {
            initializeBoard();

        }
        else {
            Close(true); // Exit the game
        }
        return;
    }

    if (checkDraw()) {
        // Alternate the starting player after a draw

        nextStartingPlayer = (nextStartingPlayer == 'X') ? 'O' : 'X';

        if (ShowRestartPrompt("It's a draw! Play a new game?")) {
            initializeBoard();
        }
        else {
            Close(true); // Exit the game
        }
        return;
    }
    // Switch player and update status
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    statusText->SetLabel(wxString::Format("Player %c's turn", currentPlayer));
}

void TicTacToeGUI::OnResetClick(wxCommandEvent& event) {
    initializeBoard();
}

void TicTacToeGUI::OnThemeToggleClick(wxCommandEvent& event) {
    isDarkMode = !isDarkMode;
    SetBackgroundColour(isDarkMode ? darkBgColor : lightBgColor);
    statusText->SetForegroundColour(isDarkMode ? darkTextColor : lightTextColor);
    scoreText->SetForegroundColour(isDarkMode ? darkTextColor : lightTextColor);
    resetButton->SetBackgroundColour(isDarkMode ? darkButtonColor : lightButtonColor);
    resetButton->SetForegroundColour(isDarkMode ? darkTextColor : lightTextColor);
    themeToggleButton->SetBackgroundColour(isDarkMode ? darkButtonColor : lightButtonColor);
    themeToggleButton->SetForegroundColour(isDarkMode ? darkTextColor : lightTextColor);

    for (int i = 0; i < 9; ++i) {
        boardButtons[i]->SetBackgroundColour(isDarkMode ? darkButtonColor : lightButtonColor);
    }
    Refresh();
}