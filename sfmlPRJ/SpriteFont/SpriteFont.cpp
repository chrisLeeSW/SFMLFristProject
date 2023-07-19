#include "stdafx.h"
#include "SpriteFont.h"


bool SpriteFont::LoadFromFile(const std::string path)
{
    rapidcsv::Document doc(path, rapidcsv::LabelParams(-1, -1));

    for (int i = 1;i < doc.GetRowCount();++i)
    {
        auto rows = doc.GetRow<std::string>(i);
        frames.push_back({rows[0].front(), rows[1], {std::stoi(rows[2]),std::stoi(rows[3]),
        std::stoi(rows[4]),std::stoi(rows[5]) } });
    }
    return true;
}