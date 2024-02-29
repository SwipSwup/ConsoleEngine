//
// Created by david on 29/02/2024.
//

// ReSharper disable CppStringLiteralToCharPointerConversion
#include "Color.h"

#include <cstring>

namespace Engine
{
    Color::Color(char* escapeCode)
    {
        this->escapeCode = escapeCode;
        this->escapeCodeLength = strlen(escapeCode);
    }

    const Color Color::BLK = "\e[0;30m";
    const Color Color::RED = "\e[0;31m";
    const Color Color::GRN = "\e[0;32m";
    const Color Color::YEL = "\e[0;33m";
    const Color Color::BLU = "\e[0;34m";
    const Color Color::MAG = "\e[0;35m";
    const Color Color::CYN = "\e[0;36m";
    const Color Color::WHT = "\e[0;37m";

    const Color Color::BBLK = "\e[1;30m";
    const Color Color::BRED = "\e[1;31m";
    const Color Color::BGRN = "\e[1;32m";
    const Color Color::BYEL = "\e[1;33m";
    const Color Color::BBLU = "\e[1;34m";
    const Color Color::BMAG = "\e[1;35m";
    const Color Color::BCYN = "\e[1;36m";
    const Color Color::BWHT = "\e[1;37m";

    const Color Color::UBLK = "\e[4;30m";
    const Color Color::URED = "\e[4;31m";
    const Color Color::UGRN = "\e[4;32m";
    const Color Color::UYEL = "\e[4;33m";
    const Color Color::UBLU = "\e[4;34m";
    const Color Color::UMAG = "\e[4;35m";
    const Color Color::UCYN = "\e[4;36m";
    const Color Color::UWHT = "\e[4;37m";

    const Color Color::BLKB = "\e[40m";
    const Color Color::REDB = "\e[41m";
    const Color Color::GRNB = "\e[42m";
    const Color Color::YELB = "\e[43m";
    const Color Color::BLUB = "\e[44m";
    const Color Color::MAGB = "\e[45m";
    const Color Color::CYNB = "\e[46m";
    const Color Color::WHTB = "\e[47m";

    const Color Color::BLKHB = "\e[0;100m";
    const Color Color::REDHB = "\e[0;101m";
    const Color Color::GRNHB = "\e[0;102m";
    const Color Color::YELHB = "\e[0;103m";
    const Color Color::BLUHB = "\e[0;104m";
    const Color Color::MAGHB = "\e[0;105m";
    const Color Color::CYNHB = "\e[0;106m";
    const Color Color::WHTHB = "\e[0;107m";

    const Color Color::HBLK = "\e[0;90m";
    const Color Color::HRED = "\e[0;91m";
    const Color Color::HGRN = "\e[0;92m";
    const Color Color::HYEL = "\e[0;93m";
    const Color Color::HBLU = "\e[0;94m";
    const Color Color::HMAG = "\e[0;95m";
    const Color Color::HCYN = "\e[0;96m";
    const Color Color::HWHT = "\e[0;97m";

    const Color Color::BHBLK = "\e[1;90m";
    const Color Color::BHRED = "\e[1;91m";
    const Color Color::BHGRN = "\e[1;92m";
    const Color Color::BHYEL = "\e[1;93m";
    const Color Color::BHBLU = "\e[1;94m";
    const Color Color::BHMAG = "\e[1;95m";
    const Color Color::BHCYN = "\e[1;96m";
    const Color Color::BHWHT = "\e[1;97m";

    const Color Color::reset = "\e[0m";
    const Color Color::CRESET = "\e[0m";
    const Color Color::COLOR_RESET = "\e[0m";
} // Engine
