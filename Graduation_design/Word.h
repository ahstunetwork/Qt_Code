#ifndef WORD_H
#define WORD_H

#include <QString>
#include <QDebug>

class Word
{
public:
    Word()
    {
        qDebug() << "Word class construct" << endl;
    }

    Word(int index, QString word, QString soundmark, QString meaning, int study_count, bool is_marked)
    {
        this->index   =  index;
        this->word    =  word;
        this->soundmark = soundmark;
        this->meaning = meaning;
        this->study_count = study_count;
        this->is_marked = is_marked;
    }



    int index;
    QString word;
    QString soundmark;
    QString meaning;
    int study_count;
    bool is_marked;



    int getIndex() const;
    void setIndex(int value);

    QString getWord() const;
    void setWord(const QString &value);

    QString getSoundmark() const;
    void setSoundmark(const QString &value);

    QString getMeaning() const;
    void setMeaning(const QString &value);

    int getStudy_count() const;
    void setStudy_count(int value);

    bool getIs_marked() const;
    void setIs_marked(bool value);
};


#endif // WORD_H
