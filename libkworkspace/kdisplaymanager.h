/*
    SPDX-FileCopyrightText: 2004, 2005 Oswald Buddenhagen <ossi@kde.org>
    SPDX-FileCopyrightText: 2005 Stephan Kulow <coolo@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "config-libkworkspace.h"
#include "kworkspace.h"
#include "kworkspace_export.h"
#include <QByteArray>
#include <QList>
#include <QString>

struct KWORKSPACE_EXPORT SessEnt {
    QString display, from, user, session;
    int vt;
    bool self : 1, tty : 1;
};

typedef QList<SessEnt> SessList;

class KWORKSPACE_EXPORT KDisplayManager
{
#if HAVE_X11

public:
    KDisplayManager();
    ~KDisplayManager();

    bool canShutdown();
    void shutdown(KWorkSpace::ShutdownType shutdownType, KWorkSpace::ShutdownMode shutdownMode, const QString &bootOption = QString());

    bool isSwitchable();
    int numReserve();
    void startReserve();
    bool localSessions(SessList &list);
    bool switchVT(int vt);
    void lockSwitchVT(int vt);

    bool bootOptions(QStringList &opts, int &dflt, int &curr);

    static QString sess2Str(const SessEnt &se);
    static void sess2Str2(const SessEnt &se, QString &user, QString &loc);

private:
    bool exec(const char *cmd, QByteArray &ret);
    bool exec(const char *cmd);

    void GDMAuthenticate();

#else // Q_WS_X11

public:
    KDisplayManager()
    {
    }

    bool canShutdown()
    {
        return false;
    }
    void shutdown(KWorkSpace::ShutdownType shutdownType, KWorkSpace::ShutdownMode shutdownMode, const QString &bootOption = QString())
    {
    }

    void setLock(bool)
    {
    }

    bool isSwitchable()
    {
        return false;
    }
    int numReserve()
    {
        return -1;
    }
    void startReserve()
    {
    }
    bool localSessions(SessList &list)
    {
        return false;
    }
    void switchVT(int vt)
    {
    }

    bool bootOptions(QStringList &opts, int &dflt, int &curr);

#endif // HAVE_X11

private:
#if HAVE_X11
    class Private;
    Private *const d;
#endif // HAVE_X11

}; // class KDisplayManager
