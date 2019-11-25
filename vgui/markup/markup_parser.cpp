#include "markup_parser.h"
#include "character_stream.h"
using namespace vgui;
#include <stack>

static constexpr const char* 
ERROR_NO_MATCHING_TAG = "syntax error: a tag didn't have a matching opening and ending tags";

static constexpr const char*
ERROR_UNEXPECTED_SYMBOL = "syntax error: unexpected symbol or token";

static constexpr const char*
ERROR_UNDEFINED_PARSE_STATE = "parse state error: we reached an undefined parse state";

enum TOKENS
{
    TOKEN_LESS_THAN,        // '<'
    TOKEN_GREATED_THAN,     // '>'
    TOKEN_EQUAL_SIGN,       // '='
    TOKEN_DOUBLE_QUOTES,    // '"'
    TOKEN_HYPHEN,           // '-'
    TOKEN_COMMA,            // ','
    TOKEN_NUMBER_SIGN,      // '#'
    TOKEN_SLASH,            // '/'
    TOKEN_CHARACTER,        // alphabet [a-z] and [A-Z]
    TOKEN_CONTROL_CHARACTER,// '\n' '\t' '\r'
    TOKEN_SPACE,            // ' '
    TOKEN_NUMBER,           // 0-9
    TOKEN_ASTERISK,         // '*'
    TOKEN_DOT,              // '.'
    TOKEN_UNKNOWN           // anything else not in this enum
};

// return true if char is a valid alphabet letter
bool is_char_alphabet(char c)
{
    // if A-Z ascii or a-z ascii
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// return true if char is an ascii number 0-9
bool is_char_number(char c)
{
    if (c >= 48 && c <= 75)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// return true if char is in the printable ascii range, else return false
// NOTE: this function returns false for extended ascii characters
// such as latin characters and signs that are defined after ascii 126
bool is_printable_ascii(char c)
{
    if (c >= 32 && c <= 126)
    {
        return true;
    }
    else
    {
        return false;
    }
}

enum class ParseState
{
    // this is the default state
    NOTHING,
    // this state is set in order to start string accumulation
    ACCUMULATE, 
    // set right after the '<' char
    TAG_BEGIN,
    // set right after the '</' char
    TAG_END,
    // set right after '>' char
    TAG_CLOSE,
    // previous state must be "TAG_CLOSE", since content doesn't start unless a tag was already closed: <tag>content
    TAG_BEGIN_CONTENT,
    // set if previous state was "TAG_BEGIN_CONTENT" and current char is '<',
    // (since all content must between the tags <tag>content</tag>
    TAG_END_CONTENT,
    // used for reading the attributes of a tag
    TAG_BEGIN_ATTRIBUTE,
    // used for reading the attribute data of a tag
    TAG_BEGIN_ATTRIBUTE_DATA,
    // used for flagging the end of the data of an attribute
    TAG_END_ATTRIBUTE_DATA,
    // used for specifying that attribute reading was done
    TAG_END_ATTRIBUTE,
    // used to skip characters, for example multi-line comments
    SKIP
};

TOKENS tokenize(char c)
{
    switch (c)
    {
    case '<':
        return TOKEN_LESS_THAN;
    case '>':
        return TOKEN_GREATED_THAN;
    case '=':
        return TOKEN_EQUAL_SIGN;
    case ' ':
        return TOKEN_SPACE;
    case '"':
        return TOKEN_DOUBLE_QUOTES;
    case '-':
        return TOKEN_HYPHEN;
    case ',':
        return TOKEN_COMMA;
    case '#':
        return TOKEN_NUMBER_SIGN;
    case '*':
        return TOKEN_ASTERISK;
    case '/':
        return TOKEN_SLASH;
    case '.':
        return TOKEN_DOT;
    case '\n':
        return TOKEN_CONTROL_CHARACTER;
    case '\t':
        return TOKEN_CONTROL_CHARACTER;
    case '\r':
        return TOKEN_CONTROL_CHARACTER;
    default:
        if (is_char_alphabet(c))
        {
            return TOKEN_CHARACTER;
        }
        else if (is_char_number(c))
        {
            return TOKEN_NUMBER;
        }

        // we couldn't recognize the token! can throw an error if needed
        return TOKEN_UNKNOWN;
    }
}

ParseResult parse_tag_attribute_data(ParseState& state, CharacterStream& cstream, std::string& out_data)
{
    if (state != ParseState::TAG_BEGIN_ATTRIBUTE_DATA)
    {
        return {
            PS_STATE_ERROR,
            "parse state error: parse tag attribute data was entered without the correct state set",
            cstream.current_line(), cstream.current_column()
        };
    }

    // this is basically a flag so we can know when we reach the
    // second '"' character so we can stop accumulating
    bool reached_first_quote = false;
    auto local_state = ParseState::NOTHING;
    for (int c = cstream.next(); c != -1; c = cstream.next())
    {
        auto line = cstream.current_line();
        auto column = cstream.current_column();
        char ch = (char)c;
        auto token = tokenize(ch);

        switch (token)
        {
        case TOKEN_DOUBLE_QUOTES:
        {
            if (!reached_first_quote)
            {
                reached_first_quote = true;
            }
            else
            {
                // we reached the second '"' double quotes
                // our job is done, we are done parsing the data
                if (local_state == ParseState::ACCUMULATE)
                {
                    state = ParseState::TAG_END_ATTRIBUTE;
                    return { PS_SUCCESS, "", line, column };
                }
                else
                {
                    return
                    {
                        PS_EMPTY_ATTRIBUTE_DATA,
                        "syntax error: empty attribute data, attributes must not have empty data",
                        line, column
                    };
                }
            }
            break;
        }
        // we support the following symbols inside the data: '-' ',' 'space' '#' 'number', '.'
        // for example: "data-mydata" and "data, mydata" and "#data" and so on...
        case TOKEN_CHARACTER:
        case TOKEN_HYPHEN:
        case TOKEN_COMMA:
        case TOKEN_SPACE:
        case TOKEN_NUMBER_SIGN:
        case TOKEN_NUMBER:
        case TOKEN_DOT:
        {
            if (local_state == ParseState::NOTHING || local_state == ParseState::ACCUMULATE)
            {
                local_state = ParseState::ACCUMULATE;
                out_data += ch;
            }
            else
            {
                return 
                {
                    PS_STATE_ERROR, ERROR_UNDEFINED_PARSE_STATE, line, column
                };
            }
            break;
        }
        case TOKEN_CONTROL_CHARACTER:
        {
            continue;
            break;
        }
        default:
            return
            {
                PS_UNEXPECTED_SYMBOL, ERROR_UNEXPECTED_SYMBOL, line, column
            };
        }
    }

    return
    {
        PS_ERROR,
        "parsing error: an unknown error happened while parsing attribute data",
        cstream.current_line(), cstream.current_column()
    };
}

ParseResult parse_tag_attribute(ParseState& state, CharacterStream& cstream, Attribute& out_attr)
{
    if (state != ParseState::TAG_BEGIN_ATTRIBUTE)
    {
        return 
        {
            PS_STATE_ERROR,
            "parse state error: parse tag attribute was entered without the correct state set",
            cstream.current_line(), cstream.current_column()
        };
    }

    auto local_state = ParseState::NOTHING;
    for (int c = cstream.next(); c != -1; c = cstream.next())
    {
        auto line = cstream.current_line();
        auto column = cstream.current_column();
        char ch = (char)c;
        auto token = tokenize(ch);

        switch (token)
        {
        case TOKEN_CHARACTER:
        {
            // since the tag attribute name comes right after the 'space' char, we start accumulating right away
            if (local_state == ParseState::NOTHING || local_state == ParseState::ACCUMULATE)
            {
                local_state = ParseState::ACCUMULATE;
                out_attr.name += ch;
            }
            else
            {
                return
                {
                    PS_STATE_ERROR, ERROR_UNDEFINED_PARSE_STATE, line, column
                };
            }
            break;
        }
        case TOKEN_EQUAL_SIGN:
        {
            state = ParseState::TAG_BEGIN_ATTRIBUTE_DATA;
            if (auto result = parse_tag_attribute_data(state, cstream, out_attr.data); !result)
            {
                // an error happened while parsing attribute data
                return result;
            }

            // return since we have successfully read the data to the end
            state = ParseState::TAG_END_ATTRIBUTE;
            return { PS_SUCCESS, "", line, column };
        }
        case TOKEN_CONTROL_CHARACTER:
        {
            continue;
            break;
        }
        default:
            return 
            {
                PS_UNEXPECTED_SYMBOL, ERROR_UNEXPECTED_SYMBOL, line, column
            };
        }
    }

    return
    {
        PS_ERROR,
        "parsing error: an unknown error happened while parsing a tag attribute",
        cstream.current_line(), cstream.current_column()
    };
}

ParseResult parse_tag(ParseState& state, CharacterStream& cstream, Tag& out_tag)
{
    if (state != ParseState::TAG_BEGIN)
    {
        return 
        {
            PS_STATE_ERROR,
            "parse state error: parse tag was entered without the correct state set",
            cstream.current_line(), cstream.current_column()
        };
    }

    ParseState local_state = ParseState::NOTHING;
    for (int c = cstream.next(); c != -1; c = cstream.next())
    {
        auto line = cstream.current_line();
        auto column = cstream.current_column();
        char ch = (char)c;
        auto token = tokenize(ch);

        switch (token)
        {
        // handle closing tags </tag>
        case TOKEN_SLASH:
        {
            // make sure that we are right after the char '<', since '/' can only after that symbol
            // this also makes sure that no opening tags are allowed to have '/>' closing syntax
            if (local_state != ParseState::ACCUMULATE && local_state == ParseState::NOTHING)
            {
                out_tag.is_closing_tag = true;
            }
            else
            {
                return
                {
                    PS_UNEXPECTED_SYMBOL, ERROR_UNEXPECTED_SYMBOL, line, column
                };
            }
            break;
        }
        case TOKEN_GREATED_THAN:
        {
            // set the state so it says we reached the end of the tag
            state = ParseState::TAG_CLOSE;
            // NOTE: by reaching here, the out_tag should be filled with the parsed info
            return { PS_SUCCESS, "", line, column };
        }
        case TOKEN_CHARACTER:
        {
            // tag name comes right after the '<' char
            // check if we are still accumulating the string
            if (local_state == ParseState::NOTHING || local_state == ParseState::ACCUMULATE)
            {
                local_state = ParseState::ACCUMULATE;
                out_tag.name += ch;
            }
            else
            {
                return
                {
                    PS_STATE_ERROR, ERROR_UNDEFINED_PARSE_STATE, line, column
                };
            }

            break;
        }
        case TOKEN_SPACE:
        {
            // start parsing attributes
            Attribute attr;
            state = ParseState::TAG_BEGIN_ATTRIBUTE;
            if (auto result = parse_tag_attribute(state, cstream, attr); !result)
            {
                return result;
            }
            // add the parsed attribute to our tag attributes list
            out_tag.attributes.push_back(attr);
            break;
        }
        case TOKEN_CONTROL_CHARACTER:
        {
            continue;
            break;
        }
        default:
            return
            {
                PS_UNEXPECTED_SYMBOL, ERROR_UNEXPECTED_SYMBOL, line, column
            };
        }
    }

    return
    {
        PS_ERROR,
        "parsing error: an unknown error happened while parsing a tag",
        cstream.current_line(), cstream.current_column()
    };
}

ParseResult parse_tag_content(ParseState& state, CharacterStream& cstream, Tag& out_tag)
{
    if (state != ParseState::TAG_BEGIN_CONTENT)
    {
        return 
        {
            PS_STATE_ERROR,
            "parse state error: parse tag content was entered without the correct state set",
            cstream.current_line(), cstream.current_column()
        };
    }

    for (int c = cstream.next(); c != -1; c = cstream.next())
    {
        auto line = cstream.current_line();
        auto column = cstream.current_column();
        char ch = (char)c;
        auto token = tokenize(ch);

        if (token == TOKEN_CONTROL_CHARACTER)
        {
            continue;
        }
        // check if the char is not '<' since that messes up the tag opening syntax
        // the char '>' is valid because it's only used at the end, and content
        // can only come after that char, so we can parse it easily
        if (is_printable_ascii(ch) && token != TOKEN_LESS_THAN)
        {
            out_tag.content += ch;
        }
        // peek to check if the next char will be the tag opening char, if yes, the our work is done
        else if (token == TOKEN_LESS_THAN)
        {
            // move back the reading postion by one so calling function gets this character
            cstream.move_pos_by(-1);
            // set the correct state
            state = ParseState::TAG_END_CONTENT;
            return { PS_SUCCESS, "", line, column };
        }
        else
        {
            return
            {
                PS_UNEXPECTED_SYMBOL,
                "syntax error: unexpected symbol or token, tag content can only be in the printable ascii range",
                line, column
            };
        }
    }

    return
    {
        PS_ERROR,
        "parsing error: an unknown error happened while parsing content of a tag",
        cstream.current_line(), cstream.current_column()
    };
}

void parse_single_line_comment(ParseState& state, CharacterStream& cstream, long long line)
{
    // while we are on the same line, skip everything until we are at another line
    state = ParseState::SKIP;
    do
    {
        // peek allows us to handle new lines unlike next() which doesn't
        auto peek_ch = (char)cstream.peek();
        if (peek_ch == '\n')
        {
            break;
        }
        auto current_ch = (char)cstream.next();
    } while (cstream.current_line() == line);

    state = ParseState::NOTHING;
}

ParseResult parse_multi_line_comment(ParseState& state, CharacterStream& cstream)
{
    // since we already know that the next token is an asterisk we just consume it
    cstream.next();

    state = ParseState::SKIP;
    while (state == ParseState::SKIP)
    {
        auto current_ch = (char)cstream.next();
        auto current_token = tokenize(current_ch);
        // if we are at the '*' asterick symbol, stop skipping
        if (current_token == TOKEN_ASTERISK)
        {
            state = ParseState::NOTHING;
            break;
        }
    }
    // consume the next character and if it's not a slash
    // throw a syntax error since multi-line comments end with
    // the '*/' symbol only
    if (auto token = tokenize((char)cstream.next()); token == TOKEN_SLASH)
    {
        return { PS_SUCCESS, "", cstream.current_line(), cstream.current_column() };
    }
    else
    {
        return
        {
            PS_UNEXPECTED_SYMBOL, ERROR_UNEXPECTED_SYMBOL,
            cstream.current_line(), cstream.current_column()
        };
    }
}

ParseResult MarkupDocument::parse(const std::string& file_path)
{
    CharacterStream cstream;
    if (!cstream.open_file(file_path))
    {
        return { PS_FAILED_TO_LOAD, "couldn't open the file" };
    }

    ParseState state = ParseState::NOTHING;
    for (int c = cstream.next(); c != -1; c = cstream.next())
    {
        auto line = cstream.current_line();
        auto column = cstream.current_column();
        char ch = (char)c;

        auto token = tokenize(c);
        switch (token)
        {
        case TOKEN_LESS_THAN:
        {
            // handle tags
            if (state == ParseState::NOTHING || state == ParseState::TAG_CLOSE || state == ParseState::TAG_END_CONTENT)
            {
                Tag tag;
                tag.line = line;
                tag.column = column;
                state = ParseState::TAG_BEGIN;
                if (auto result = parse_tag(state, cstream, tag); !result)
                {
                    return result;
                }
                // reaching here means the tag was successfully parsed a tag
                m_tags.push_back(tag);
            }
            else
            {
                return
                {
                    PS_STATE_ERROR,
                    "parse state error: parse tag was skipped because unsupported state was set",
                    line, column
                };
            }
            break;
        }
        case TOKEN_CHARACTER:
        {
            // handle tag content
            // check that we already handled a tag opening successfully
            // since the content comes after <tag> and this TAG_CLOSE is
            // set after the '>' char, else throw an error
            if (state == ParseState::TAG_CLOSE && !m_tags.empty())
            {
                // move the reading position by one character so that the tag content
                // parsing function gets to read the first char of content
                // NOTE: this is needed because we need to know if the char is a valid character before
                // the content parsing function is called in order to decide if it's the begining of tag content
                // and at the same time to let the parsing function only see what's it's supposed to know
                cstream.move_pos_by(-1);
                // find the last tag we parsed since it's the one that owns the content
                auto& tag = m_tags.back();
                state = ParseState::TAG_BEGIN_CONTENT;
                if (auto result = parse_tag_content(state, cstream, tag); !result)
                {
                    return result;
                }
            }
            else
            {
                return 
                { 
                    PS_UNEXPECTED_SYMBOL,
                    "syntax error: unexpected symbol or token, content can only be inside a tag",
                    line, column
                };
            }
            break;
        }
        case TOKEN_CONTROL_CHARACTER:
        {
            // just skip this character, since it's either \n \t \r and they aren't any of use to us
            break;
        }
        case TOKEN_SPACE:
        {
            // just skip this character
            break;
        }
        case TOKEN_UNKNOWN:
        {
            return { PS_UNEXPECTED_SYMBOL, ERROR_UNEXPECTED_SYMBOL, line, column };
        }
        case TOKEN_SLASH:
        {
            // handle comments
            auto next_ch = cstream.peek();
            auto next_token = tokenize(next_ch);
            if (next_token == TOKEN_SLASH)
            {
                // handle single line comment
                parse_single_line_comment(state, cstream, line);
            }
            else if (next_token == TOKEN_ASTERISK)
            {
                // handle multi-line comments
                if (auto result = parse_multi_line_comment(state, cstream); !result)
                {
                    return result;
                }
            }
            else
            {
                return
                {
                    PS_UNEXPECTED_SYMBOL, ERROR_UNEXPECTED_SYMBOL, line, column
                };
            }
            break;
        }
        default:
            return
            {
                PS_UNEXPECTED_SYMBOL, ERROR_UNEXPECTED_SYMBOL, line, column
            };
        }
    }

    // Check that for every open tag there is an ending tag
    // we use this struct in the stack instead of the actual tag
    // to avoid copying the entire tag information which contains vectors,
    // because we don't actually need the rest of the information to be in the stack
    struct tag_info
    {
        std::string name;
        long long line;
        long long column;
    };

    std::stack<tag_info> open_tags_stack;
    for (auto& tag : m_tags)
    {
        if (!tag.is_closing_tag)
        {
            open_tags_stack.push({ tag.name, tag.line, tag.column });
        }
        else
        {
            if (!open_tags_stack.empty())
            {
                auto& open_tag = open_tags_stack.top();
                if (open_tag.name == tag.name)
                {
                    // there was an open tag with the same name and we
                    // found a tag that closes it, all good
                    open_tags_stack.pop();
                }
                else
                {
                    // the last open tag didn't have the same name as this closing tag
                    // throw an error since every open tag must be closed
                    return
                    {
                        PS_TAG_NOT_CLOSED,
                        ERROR_NO_MATCHING_TAG,
                        open_tag.line, open_tag.column
                    };
                }
            }
            else
            {
                return
                {
                    PS_TAG_NOT_CLOSED,
                    "syntax error: a tag didn't have a matching opening tag",
                    tag.line, tag.column
                };
            }
        }
    }

    if (!open_tags_stack.empty())
    {
        auto& opning_tag = open_tags_stack.top();
        return
        {
            PS_TAG_NOT_CLOSED,
            ERROR_NO_MATCHING_TAG,
            opning_tag.line, opning_tag.column
        };
    }

    return { PS_SUCCESS, "" };
}

std::vector<Tag>& MarkupDocument::getTags()
{
    return m_tags;
}