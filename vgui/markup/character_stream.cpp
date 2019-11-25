#include "character_stream.h"
using namespace vgui;

bool CharacterStream::open_file(const std::string& path)
{
    m_fstream.open(path);
    if (m_fstream.is_open() && m_fstream.good())
    {
        return true;
    }
    else
    {
        return false;
    }
}

int CharacterStream::peek()
{
    int c = m_fstream.peek();
    if (c == EOF)
    {
        return -1;
    }
    return c;
}

int CharacterStream::next()
{
    // Docs ifstream::get(char): reads one character and returns it if available.
    // otherwise, returns Traits::eof() and sets failbit and eofbit.
    char c = 0;
    if (m_fstream.get(c))
    {
        // skip line feed LF (\n) and carriage return CR (\r)
        // Windows uses : CRLF (\r \n) for new lines
        // Unix, MacOS uses: LF (\n)  for new lines
        // Older MacOS uses: CR (\r) for new lines
        // NOTE: looks like the stl eats up the '\r' so we only need to handle '\n' for CRLF
        switch (c)
        {
        case '\n':
        {
            m_line_number++;
            m_previous_line_column_number = m_column_number;
            m_column_number = 1;
            // skip new line character and get the next one
            c = next();
            break;
        }
        case '\t':
        {
            m_column_number += 4;
            break;
        }
        default:
        {
            m_column_number++;
            break;
        }
        }

        return static_cast<int>(c);
    }
    else
    {
        return -1;
    }
}

long long CharacterStream::current_pos()
{
    return m_fstream.tellg();
}

void CharacterStream::move_pos_by(int by)
{
    m_fstream.seekg(by, std::ios_base::cur);
    // reset the column number if we move more than this current line has columns
    // and jump back into the previous line by the overflow amount
    if (auto overflow = m_column_number + by; overflow < 1)
    {
        // TODO: not tested correctly yet!!
        // go back to the previous line
        m_line_number--;
        // set the column number to the previous line max column number minus the overflow
        // to handle the case of the 'by' being larger than current line columns, and to account
        // for the overflow in the previous line instead of this one
        m_column_number = m_previous_line_column_number - overflow;
    }
    else
    {
        m_column_number += by;
    }
}

long long CharacterStream::current_line()
{
    return m_line_number;
}

long long CharacterStream::current_column()
{
    return m_column_number;
}