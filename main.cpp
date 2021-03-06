#include <QtWidgets>
#include <QtSql>
#include <cstdlib>
#include <locale.h>

#include "mainform.h"

#include "dbfkts.h"

int main(int argc, char *argv[])
{
    QApplication::setApplicationName("DkVerwaltungQt");
    QApplication::setOrganizationName("MHS");

    setlocale(LC_ALL, "C");
    QLocale::setDefault(QLocale::c());

    QApplication app(argc, argv);

    qDebug() << "settings: " << getSettings().fileName();
    QString dbPath = getFilePathFromIni("DBPath", getStandardPath(), "DkVerwaltungQt.db3");
    qDebug() << "dbPath: " << dbPath;
    if(!dbPath.length())
        return 1;
    bool existingData = QFile::exists(dbPath);
    if (!existingData){
        QMessageBox::warning(0, QStringLiteral("Datenbank Fehler"),
                         dbPath + QStringLiteral(" existiert nicht!"));
        return 2;
    }
    if (!createConnection(dbPath))
        return 1;

    MainForm form;
    form.resize(1024, 768);
    form.show();
    return app.exec();
}
