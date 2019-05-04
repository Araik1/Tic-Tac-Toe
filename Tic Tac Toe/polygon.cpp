#include "polygon.h"
#include "QDebug"
polygon::polygon()
{
    p.resize(3);
    for(auto i = 0; i < 3; ++i)
    {
        p[i].resize(3);
    }
    clear();
    s = X;
    siz = 3;
}

polygon::polygon(size_t size)
{
    p.resize(size);
    for(auto i = 0; i < size; ++i)
    {
        p[i].resize(size);
    }
    clear();
    s = X;

    this->siz = size;
}

void polygon::polygonResize(size_t size)
{
    p.resize(size);
    for(auto i = 0; i < size; ++i)
    {
        p[i].resize(size);
    }

    this->siz = size;
}

bool polygon::step(size_t i, size_t j)
{
    if(i < siz && j < siz)
    {
        if(this->getCellValue(i, j) == null)
        {
            if(s == X)
            {
                this->setCellValue(i, j, s);
                s = O;
            }
            else
            {
                this->setCellValue(i, j, s);
                s = X;
            }
            return true;
        }
    }
    else
        return false;
}

gamer polygon::getPlayer()
{
    return s;
}

bool polygon::checkIsWin(gamer symbol)
{
    int mdig(0), supdig(0), hor(0), ver(0);

    for (int i = 0; i < p.size(); i++)
    {
        hor = ver = 0;
        for (int j = 0; j < p.size(); j++)
        {
            if (p[i][j] == symbol)
            {
                hor++;
            }
            if (p[j][i] == symbol)
            {
                ver++;
            }
        }
        if ((hor == p.size()) || (ver == p.size()))
        {
            return true;
        }
        if (p[i][i] == symbol)
        {
            mdig++;
        }
        if (p[i][p.size() - 1 - i] == symbol)
        {
            supdig++;
        }
        if((mdig == p.size()) || (supdig == p.size()))
        {
            return true;
        }
    }
    return false;

}

gamer polygon::statusGame()
{
    if(checkIsWin(O))
    {
        return O;
    }
    else if(checkIsWin(X))
    {
        return X;
    }
    else if(draw())
    {
        return XO;
    }
    else
    {
        return null;
    }
}

bool polygon::setCellValue(size_t i, size_t j, gamer v)
{
    if(getCellValue(i, j) == null)
    {
        p[i][j] = v;
        return true;
    }
    else
        return false;
}

gamer polygon::getCellValue(size_t i, size_t j)
{
    return p[i][j];
}

bool polygon::draw()
{
    size_t d = 0;
    for(auto i = 0; i < p.size(); ++i)
    {
        for(auto j = 0; j < p.size(); ++j)
        {
            if(getCellValue(i, j) != null)
                d++;
        }
    }
    if(d == (p.size()*p.size()))
        return true;
    else
        return false;

}

void polygon::clear()
{
    for(auto i = 0; i < p.size(); ++i)
    {
        for(auto j = 0; j < p.size(); ++j)
        {
            p[i][j] = null;
        }
    }
    s = X;
}

size_t polygon::size()
{
    return siz;
}
