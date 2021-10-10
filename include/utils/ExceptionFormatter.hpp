// Shamelessly copied from https://stackoverflow.com/a/12262626
/*
Example:

throw std::runtime_error(Formatter() << foo << 13 << ", bar" << myData);   // implicitly cast to std::string
throw std::runtime_error(Formatter() << foo << 13 << ", bar" << myData >> Formatter::to_str);    // explicitly cast to std::string

*/

#pragma once

#include <stdexcept>
#include <sstream>

namespace lima{
class exceptionFormatter{
    public:
        exceptionFormatter() {}
        ~exceptionFormatter() {}

        template <typename Type>
        exceptionFormatter & operator << (const Type & value)
        {
            stream_ << value;
            return *this;
        }

        std::string str() const         { return stream_.str(); }
        operator std::string () const   { return stream_.str(); }

        enum ConvertToString 
        {
            to_str
        };
        std::string operator >> (ConvertToString) { return stream_.str(); }

    private:
        std::stringstream stream_;

        exceptionFormatter(const exceptionFormatter &);
        exceptionFormatter & operator = (exceptionFormatter &);
    };
}
