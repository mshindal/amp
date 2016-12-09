#ifndef SCANNER_H
#define SCANNER_H

#include <QThread>
#include "song.h"

class Scanner : public QThread {
Q_OBJECT
public:
    Scanner();

    void run() override;

private:
    void searchFolderRecursively(QString absolutePath);

signals:

    void songFound(Song s);
};

#endif // SCANNER_H
