// Compiler
#include <iostream>
#include <vector>

struct Token
{
    enum class Type
    {
        ndef, num, op
    };
    Type type;
    std::string value;
    friend std::ostream& operator<<(std::ostream& os, const Token& t);
};

std::ostream& operator<<(std::ostream& os, const Token& t)
{
    switch(t.type)
    {
        case Token::Type::num:
            os << "Number: " << t.value;
            break;
        case Token::Type::op:
            os << "Operator: " << t.value;
            break;
        default:
            break;
    }
    return os;
}

Token::Type charTokenType(char c)
{
    if(c == '=' || c == '+' || c == '-' || c == '*' || c == '/')
        return Token::Type::op;
    else if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
        return Token::Type::num;
    std::cout << "ERROR: unknown token" << std::endl;
    return Token::Type::ndef;
}

std::vector<Token*> getTokens(std::string iline)
{
    std::vector<Token*> tokens;
    while(!iline.empty())
    {
        Token* tok = new Token();
        char current = iline.front();
        iline.erase(0,1);
        tok->value.push_back(current);
        tok->type = charTokenType(current);
        while(!iline.empty())
        {
            char next = iline.front();
            Token::Type next_t = charTokenType(next);
            if(tok->type == next_t)
            {
                tok->value.push_back(next);
                iline.erase(0,1);
            }
            else
                break;
        }
        tokens.push_back(tok);
    }
    return tokens;
}

int main() {
    std::cout << "Super professional calculator" << std::endl;
    std::string iline;
    std::getline(std::cin, iline);
    std::cout << iline << std::endl;
    std::vector<Token*> tokens = getTokens(iline);
    for(Token* t : tokens)
    {
        std::cout << (*t) << std::endl;
    }
    return 0;
}
