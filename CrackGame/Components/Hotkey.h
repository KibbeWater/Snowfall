//
// Created by kibbe on 1/18/2025.
//

#ifndef HOTKEY_H
#define HOTKEY_H

namespace Components {
    bool Hotkey(const char* label, int* key, ImVec2 button_size = ImVec2(120, 0));

    static const std::map<int, const char*> s_keyNames = {
        // Letters
        { ImGuiKey_A, "A" }, { ImGuiKey_B, "B" }, { ImGuiKey_C, "C" },
        { ImGuiKey_D, "D" }, { ImGuiKey_E, "E" }, { ImGuiKey_F, "F" },
        { ImGuiKey_G, "G" }, { ImGuiKey_H, "H" }, { ImGuiKey_I, "I" },
        { ImGuiKey_J, "J" }, { ImGuiKey_K, "K" }, { ImGuiKey_L, "L" },
        { ImGuiKey_M, "M" }, { ImGuiKey_N, "N" }, { ImGuiKey_O, "O" },
        { ImGuiKey_P, "P" }, { ImGuiKey_Q, "Q" }, { ImGuiKey_R, "R" },
        { ImGuiKey_S, "S" }, { ImGuiKey_T, "T" }, { ImGuiKey_U, "U" },
        { ImGuiKey_V, "V" }, { ImGuiKey_W, "W" }, { ImGuiKey_X, "X" },
        { ImGuiKey_Y, "Y" }, { ImGuiKey_Z, "Z" },

        // Numbers (main keyboard)
        { ImGuiKey_0, "0" }, { ImGuiKey_1, "1" }, { ImGuiKey_2, "2" },
        { ImGuiKey_3, "3" }, { ImGuiKey_4, "4" }, { ImGuiKey_5, "5" },
        { ImGuiKey_6, "6" }, { ImGuiKey_7, "7" }, { ImGuiKey_8, "8" },
        { ImGuiKey_9, "9" },

        // Numpad
        { ImGuiKey_Keypad0, "Num 0" }, { ImGuiKey_Keypad1, "Num 1" },
        { ImGuiKey_Keypad2, "Num 2" }, { ImGuiKey_Keypad3, "Num 3" },
        { ImGuiKey_Keypad4, "Num 4" }, { ImGuiKey_Keypad5, "Num 5" },
        { ImGuiKey_Keypad6, "Num 6" }, { ImGuiKey_Keypad7, "Num 7" },
        { ImGuiKey_Keypad8, "Num 8" }, { ImGuiKey_Keypad9, "Num 9" },
        { ImGuiKey_KeypadDecimal, "Num ." },
        { ImGuiKey_KeypadDivide, "Num /" },
        { ImGuiKey_KeypadMultiply, "Num *" },
        { ImGuiKey_KeypadSubtract, "Num -" },
        { ImGuiKey_KeypadAdd, "Num +" },
        { ImGuiKey_KeypadEnter, "Num Enter" },
        { ImGuiKey_KeypadEqual, "Num =" },

        // Function keys
        { ImGuiKey_F1, "F1" }, { ImGuiKey_F2, "F2" },
        { ImGuiKey_F3, "F3" }, { ImGuiKey_F4, "F4" },
        { ImGuiKey_F5, "F5" }, { ImGuiKey_F6, "F6" },
        { ImGuiKey_F7, "F7" }, { ImGuiKey_F8, "F8" },
        { ImGuiKey_F9, "F9" }, { ImGuiKey_F10, "F10" },
        { ImGuiKey_F11, "F11" }, { ImGuiKey_F12, "F12" },

        // Special characters and symbols
        { ImGuiKey_Tab, "Tab" },
        { ImGuiKey_Space, "Space" },
        { ImGuiKey_Backspace, "Backspace" },
        { ImGuiKey_Enter, "Enter" },
        { ImGuiKey_Escape, "Escape" },
        { ImGuiKey_LeftCtrl, "Left Ctrl" },
        { ImGuiKey_RightCtrl, "Right Ctrl" },
        { ImGuiKey_LeftAlt, "Left Alt" },
        { ImGuiKey_RightAlt, "Right Alt" },
        { ImGuiKey_LeftShift, "Left Shift" },
        { ImGuiKey_RightShift, "Right Shift" },
        { ImGuiKey_LeftSuper, "Left Super" },
        { ImGuiKey_RightSuper, "Right Super" },
        { ImGuiKey_Menu, "Menu" },
        { ImGuiKey_Apostrophe, "'" },
        { ImGuiKey_Comma, "," },
        { ImGuiKey_Minus, "-" },
        { ImGuiKey_Period, "." },
        { ImGuiKey_Slash, "/" },
        { ImGuiKey_Semicolon, ";" },
        { ImGuiKey_Equal, "=" },
        { ImGuiKey_LeftBracket, "[" },
        { ImGuiKey_Backslash, "\\" },
        { ImGuiKey_RightBracket, "]" },
        { ImGuiKey_GraveAccent, "`" },

        // Navigation
        { ImGuiKey_Insert, "Insert" },
        { ImGuiKey_Delete, "Delete" },
        { ImGuiKey_Home, "Home" },
        { ImGuiKey_End, "End" },
        { ImGuiKey_PageUp, "Page Up" },
        { ImGuiKey_PageDown, "Page Down" },
        { ImGuiKey_UpArrow, "Up" },
        { ImGuiKey_DownArrow, "Down" },
        { ImGuiKey_LeftArrow, "Left" },
        { ImGuiKey_RightArrow, "Right" },

        // Lock keys
        { ImGuiKey_CapsLock, "Caps Lock" },
        { ImGuiKey_ScrollLock, "Scroll Lock" },
        { ImGuiKey_NumLock, "Num Lock" },
        { ImGuiKey_PrintScreen, "Print Screen" },
        { ImGuiKey_Pause, "Pause" }
    };
}

#endif //HOTKEY_H
