#include <lexer/lexer.hpp>

slfbp::lexer::lexer(std::initializer_list<const char *> args_symbols)
{
    for (auto &&i : args_symbols)
        symbols_reference[i] = true;
}

void slfbp::lexer::add(std::string &str, slfbp::token::id type, std::vector<slfbp::token> &alloc)
{
    if (!str.empty())
    {
        if (type == slfbp::token::id::symbol)
            if (!symbols_reference[str])
                throw std::runtime_error("Error: Symbol unknow: " + str);
        alloc.push_back(slfbp::token(str.c_str(), str.size(), type));
        str.clear();
    }
}

bool slfbp::lexer::issymbol(const std::string &symbol)
{
    return symbols_reference[symbol];
}
void slfbp::lexer::tokenize(const std::string &str, std::vector<slfbp::token> &alloc)
{
    const char *cstr = str.c_str();
    std::string word;
    bool alfanum = true;
    while (*cstr)
    {
        ///////////////////////////////////////////////////////
        if (std::isspace(*cstr))
            slfbp::lexer::add(word, alfanum ? slfbp::token::id::word : slfbp::token::id::symbol, alloc);
        else if (alfanum == sstring::isalfanum(*cstr))
        {
            word.push_back(*cstr);
            if (!alfanum)
            {
                if (!this->symbols_reference[word])
                {
                    word.pop_back();
                    slfbp::lexer::add(word, slfbp::token::id::symbol, alloc);
                    word.push_back(*cstr);
                }
            }
        }
        else
        {
            slfbp::lexer::add(word, alfanum ? slfbp::token::id::word : slfbp::token::id::symbol, alloc);
            word.push_back(*cstr);
            alfanum = !alfanum;
        }
        ///////////////////////////////////////////////////////
        cstr++;
    }
    if (!word.empty())
        slfbp::lexer::add(word, alfanum ? slfbp::token::id::word : slfbp::token::id::symbol, alloc);
}

void slfbp::lexer::view(const std::vector<slfbp::token> &alloc)
{
    for (auto &&i : alloc)
        std::cout << "[\"" << i._atom << "\", \"" << (int)(*i._id) << "\"]" << std::endl;
}
