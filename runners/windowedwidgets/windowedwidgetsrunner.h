/*
    SPDX-FileCopyrightText: 2006 Aaron Seigo <aseigo@kde.org>
    SPDX-FileCopyrightText: 2010 Marco Martin <notmart@gmail.com>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#pragma once

#include <QMutex>

#include <krunner/abstractrunner.h>

/**
 * This class looks for matches in the set of .desktop files installed by
 * applications. This way the user can type exactly what they see in the
 * applications menu and have it start the appropriate app. Essentially anything
 * that KService knows about, this runner can launch
 */

class WindowedWidgetsRunner : public KRunner::AbstractRunner
{
    Q_OBJECT

public:
    WindowedWidgetsRunner(QObject *parent, const KPluginMetaData &metaData);
    ~WindowedWidgetsRunner() override;

    void match(KRunner::RunnerContext &context) override;
    void run(const KRunner::RunnerContext &context, const KRunner::QueryMatch &action) override;

protected Q_SLOTS:
    QMimeData *mimeDataForMatch(const KRunner::QueryMatch &match) override;

private:
    void loadMetadataList();
    QList<KPluginMetaData> m_applets;
    QMutex m_mutex;
};
