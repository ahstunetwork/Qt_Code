#include <Word.h>

int Word::getIndex() const
{
return index;
}

void Word::setIndex(int value)
{
index = value;
}

QString Word::getWord() const
{
return word;
}

void Word::setWord(const QString &value)
{
word = value;
}

QString Word::getSoundmark() const
{
return soundmark;
}

void Word::setSoundmark(const QString &value)
{
soundmark = value;
}

QString Word::getMeaning() const
{
return meaning;
}

void Word::setMeaning(const QString &value)
{
meaning = value;
}

int Word::getStudy_count() const
{
return study_count;
}

void Word::setStudy_count(int value)
{
study_count = value;
}

bool Word::getIs_marked() const
{
return is_marked;
}

void Word::setIs_marked(bool value)
{
is_marked = value;
}
