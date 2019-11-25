#pragma once
#include <string>
#include <vector>

namespace vgui
{
    // helper classes for reporting parsing error
    enum ParseStatus
    {
        PS_SUCCESS,
        PS_ERROR,
        PS_STATE_ERROR,
        PS_FAILED_TO_LOAD,
        PS_UNEXPECTED_SYMBOL,
        PS_TAG_NOT_CLOSED,
        PS_EMPTY_ATTRIBUTE_DATA
    };

    struct ParseResult
    {
        ParseStatus status;
        std::string error;
        long long line = 0;
        long long column = 0;

        ParseResult(ParseStatus status_, const std::string& error_, long long line_, long long column_) :
            status(status_), error(error_), line(line_), column(column_) {}

        ParseResult(ParseStatus status_, const std::string& error_) :
            status(status_), error(error_), line(0), column(0) {}

        operator bool()
        {
            if (status == ParseStatus::PS_SUCCESS)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    };

    // An attribute has:
    // - name: required
    // - data: required, having empty data is ill-formed
    struct Attribute
    {
        std::string name;
        std::string data;
    };

    // A tag has:
    // - name: required
    // - attributes: optional
    struct Tag
    {
        std::string name;
        std::string content;
        // a list of attributes, can be empty.
        std::vector<Attribute> attributes;
        bool is_closing_tag = false;
        long long line = 0;
        long long column = 0;
    };

    class MarkupDocument
    {
    public:
        ParseResult parse(const std::string& file_path);
        std::vector<Tag>& getTags();
    private:
        std::vector<Tag> m_tags;
    };
}