#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <optional>

namespace BMH2
{
    bool Contains(const std::map<char, size_t> &t, const char &c)
    {
        const auto it = t.find(c);
        return it != cend(t);
    }

    size_t CalculateStdOffset(const size_t size, const size_t pos)
    {
        return (pos == size - 1) ? size : (size - pos - 1);
    }

    std::map<char, size_t> CreateOffsets(const std::string_view &s)
    {
        std::map<char, size_t> res;
        for (size_t i = 0; i < size(s); ++i)
        {
            if ((i == (size(s) - 1)) && Contains(res, s[i]))
            {
                break;
            }
            res[s[i]] = CalculateStdOffset(size(s), i);
        }
        return res;
    }

    auto CreateOffsetFunc(const std::string_view &s)
    {
        return[off = CreateOffsets(s), def = size(s)](const char &c)
        {
            return Contains(off, c) ? off.find(c)->second : def;
        };
    }

    bool Equals(const std::string_view &str, const std::string_view &sub, const size_t &str_i)
    {
        for (size_t i = str_i - size(sub) + 1, j = 0; i <= str_i; ++i, ++j)
        {
            if (str[i] != sub[j])
            {
                return false;
            }
        }
        return true;
    }

    std::vector<size_t> FindAll(const std::string_view &str, const std::string_view &sub)
    {
        std::vector<size_t> res;
        const auto f = CreateOffsetFunc(sub);
        for (size_t i = size(sub) - 1; i < size(str); i += f(str[i]))
        {
            if (Equals(str, sub, i))
            {
                res.push_back(i - size(sub) + 1);
            }
        }
        return res;
    }
}

template<typename T> std::ostream &operator<<(std::ostream &cout, const std::vector<T> &vec)
{
    cout << "{ ";
    std::copy(cbegin(vec), cend(vec), std::ostream_iterator<T>(cout, "  "));
    return cout << "}";
}

int main()
{
    for (std::string str, sub;;)
    {
        std::cout << "Str: ";
        std::getline(std::cin, str);
        std::cout << "Sub: ";
        std::getline(std::cin, sub);
        std::cout << "Index: " << BMH2::FindAll(str, sub) << std::endl;
    }
}