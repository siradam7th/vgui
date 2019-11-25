#pragma once
#include <string>
#include <fstream>

namespace vgui
{
    class CharacterStream
    {
    public:
        CharacterStream() = default;

        // open the file, returns true if successful else it returns false
        bool open_file(const std::string& path);

        // return the next character but doesn't advance the reading position
        // return -1 if EOF
        // NOTE: this function supports returning new-line characters, use it instead of next() if you
        // want to know when a new-line character will be read
        int peek();

        // return the next character and advances the reading position, returns -1 on error or EOF
        // usage: for(int c = cstream.next(); c != -1; c = cstream.next())
        // result must be casted back to char if the return value is not -1 to get the actual character
        // NOTE: this function handles new-lines by itself and doesn't return the character, use peek() instead
        // if you want to know when a new-line character will be read
        int next();

        // return the current position in the stream, can be used for stream operations
        // return -1 on failure
        long long current_pos();

        // move the reading position by a certain amount from the current position
        // NOTE: must support moving forward and backwards (positive and negative values)
        // NOTE: use carefully to avoid creating an endless cycle
        void move_pos_by(int by);

        // return the current line number, do not use the returned value for stream operations!
        long long current_line();

        // return the current column number, do not use the returned value for stream operations!
        long long current_column();

    private:
        long long m_line_number = 1;
        long long m_column_number = 1;
        long long m_previous_line_column_number = 1;
        bool m_reset_column_next_time = false;
        std::ifstream m_fstream;
    };
}