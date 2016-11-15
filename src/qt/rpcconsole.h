// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_RPCCONSOLE_H
#define BITCOIN_QT_RPCCONSOLE_H

#include "guiutil.h"
//#include "peertablemodel.h"

#include "net.h"

#include <QWidget>
#include <QCompleter>

namespace Ui {
    class RPCConsole;
}
class ClientModel;

/** Local Bitcoin RPC console. */
class RPCConsole: public QDialog
{
    Q_OBJECT

public:
    explicit RPCConsole(QWidget *parent = 0);
    ~RPCConsole();

    void setClientModel(ClientModel *model);

    enum MessageClass {
        MC_ERROR,
        MC_DEBUG,
        CMD_REQUEST,
        CMD_REPLY,
        CMD_ERROR
    };

protected:
    virtual bool eventFilter(QObject* obj, QEvent *event);

private Q_SLOTS:
    void on_lineEdit_returnPressed();
    void on_tabWidget_currentChanged(int index);
    /** open the debug.log from the current datadir */
    void on_openDebugLogfileButton_clicked();
    /** display messagebox with program parameters (same as bitcoin-qt --help) */
    void on_showCLOptionsButton_clicked();
    /** change the time range of the network traffic graph */
    void on_sldGraphRange_valueChanged(int value);
    /** update traffic statistics */
    void updateTrafficStats(quint64 totalBytesIn, quint64 totalBytesOut);
    /** clear traffic graph */
    void on_btnClearTrafficGraph_clicked();

public Q_SLOTS:
    void clear();
    void message(int category, const QString &message, bool html = false);
    /** Set number of connections shown in the UI */
    void setNumConnections(int count);
    /** Set number of blocks shown in the UI */
    void setNumBlocks(int count);
    /** Go forward or back in history */
    void browseHistory(int offset);
    /** Scroll console view to end */
    void scrollToEnd();
Q_SIGNALS:
    // For RPC command executor
    void stopExecutor();
    void cmdRequest(const QString &command);

private:
    static QString FormatBytes(quint64 bytes);
    void setTrafficGraphRange(int mins);

    Ui::RPCConsole *ui;
    ClientModel *clientModel;
    QStringList history;
    int historyPtr;

    void startExecutor();
};

#endif // BITCOIN_QT_RPCCONSOLE_H
