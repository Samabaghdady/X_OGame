#include "TicTacToe.h"

class TicTacToeApp : public wxApp {
public:
    virtual bool OnInit() {
        TicTacToeGUI* frame = new TicTacToeGUI();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(TicTacToeApp);