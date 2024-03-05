//
// Created by david on 29/02/2024.
//

// ReSharper disable CppStringLiteralToCharPointerConversion
#include "Color.h"

#include <cstring>
#include <iostream>
#include <sstream>

#include "../Window/Window.h"

namespace Engine
{
    Color::Color(char* escapeCode)
    {
        this->escapeCode = escapeCode;
        this->escapeCodeLength = strlen(escapeCode);
    }

    Color::Color(int r, int g, int b)
    {
        //todo
        std::string code = "\x1b[38;2;";
        code.append(std::to_string(r));
        code.append(";");
        code.append(std::to_string(g));
        code.append(";");
        code.append(std::to_string(b));
        code.append("m");
        escapeCodeLength = code.length();
        escapeCode = new char[escapeCodeLength + 1];

        std::strcpy(const_cast<char*>(escapeCode), code.c_str());
    }

    const Color Color::BLK = "\x1b[0;30m";
    //const Color Color::BLK = "\x1b[38;2;47;186;147m";
    const Color Color::RED = "\x1b[0;31m";
    const Color Color::GRN = "\x1b[0;32m";
    const Color Color::YEL = "\x1b[0;33m";
    const Color Color::BLU = "\x1b[0;34m";
    const Color Color::MAG = "\x1b[0;35m";
    const Color Color::CYN = "\x1b[0;36m";
    const Color Color::WHT = "\x1b[0;37m";

    const Color Color::BBLK = "\x1b[1;30m";
    const Color Color::BRED = "\x1b[1;31m";
    const Color Color::BGRN = "\x1b[1;32m";
    const Color Color::BYEL = "\x1b[1;33m";
    const Color Color::BBLU = "\x1b[1;34m";
    const Color Color::BMAG = "\x1b[1;35m";
    const Color Color::BCYN = "\x1b[1;36m";
    const Color Color::BWHT = "\x1b[1;37m";

    const Color Color::UBLK = "\x1b[4;30m";
    const Color Color::URED = "\x1b[4;31m";
    const Color Color::UGRN = "\x1b[4;32m";
    const Color Color::UYEL = "\x1b[4;33m";
    const Color Color::UBLU = "\x1b[4;34m";
    const Color Color::UMAG = "\x1b[4;35m";
    const Color Color::UCYN = "\x1b[4;36m";
    const Color Color::UWHT = "\x1b[4;37m";

    const Color Color::BLKB = "\x1b[40m";
    const Color Color::REDB = "\x1b[41m";
    const Color Color::GRNB = "\x1b[42m";
    const Color Color::YELB = "\x1b[43m";
    const Color Color::BLUB = "\x1b[44m";
    const Color Color::MAGB = "\x1b[45m";
    const Color Color::CYNB = "\x1b[46m";
    const Color Color::WHTB = "\x1b[47m";

    const Color Color::BLKHB = "\x1b[0;100m";
    const Color Color::REDHB = "\x1b[0;101m";
    const Color Color::GRNHB = "\x1b[0;102m";
    const Color Color::YELHB = "\x1b[0;103m";
    const Color Color::BLUHB = "\x1b[0;104m";
    const Color Color::MAGHB = "\x1b[0;105m";
    const Color Color::CYNHB = "\x1b[0;106m";
    const Color Color::WHTHB = "\x1b[0;107m";

    const Color Color::HBLK = "\x1b[0;90m";
    const Color Color::HRED = "\x1b[0;91m";
    const Color Color::HGRN = "\x1b[0;92m";
    const Color Color::HYEL = "\x1b[0;93m";
    const Color Color::HBLU = "\x1b[0;94m";
    const Color Color::HMAG = "\x1b[0;95m";
    const Color Color::HCYN = "\x1b[0;96m";
    const Color Color::HWHT = "\x1b[0;97m";

    const Color Color::BHBLK = "\x1b[1;90m";
    const Color Color::BHRED = "\x1b[1;91m";
    const Color Color::BHGRN = "\x1b[1;92m";
    const Color Color::BHYEL = "\x1b[1;93m";
    const Color Color::BHBLU = "\x1b[1;94m";
    const Color Color::BHMAG = "\x1b[1;95m";
    const Color Color::BHCYN = "\x1b[1;96m";
    const Color Color::BHWHT = "\x1b[1;97m";

    const Color Color::reset = "\x1b[0m";
    const Color Color::CRESET = "\x1b[0m";
    const Color Color::COLOR_RESET = "\x1b[0m";
} // Engine
