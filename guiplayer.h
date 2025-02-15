/*
    Drumstick MIDI File Player Multiplatform Program
    Copyright (C) 2006-2021, Pedro Lopez-Cabanillas <plcl@users.sf.net>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef INCLUDED_GUIPLAYER_H
#define INCLUDED_GUIPLAYER_H

#include <QMainWindow>
#include <QProgressDialog>
#include <QObject>
#include <QString>
#include <QList>
#include <QHash>
#include <QPointer>
#include <QTranslator>
#include <QThread>
#include "connections.h"
#include "recentfileshelper.h"
#include "pianola.h"
#include "channels.h"
#include "lyrics.h"

#if defined(Q_OS_WINDOWS)
#include "winsnap.h"
#endif

class MIDIEvent;

namespace drumstick { namespace rt {
    class MIDIOutput;
}}

namespace Ui {
    class GUIPlayerClass;
}

class SequencePlayer;
class About;

const QString QSTR_DOMAIN("drumstick.sourceforge.net");
const QString QSTR_APPNAME("Drumstick MIDI File Multiplatform Player");

enum PlayerState {
    InvalidState,
    EmptyState,
    PlayingState,
    PausedState,
    StoppedState
};

class GUIPlayer : public QMainWindow
{
    Q_OBJECT

public:
    GUIPlayer(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~GUIPlayer();

    void appendSMFEvent(MIDIEvent* ev);
    void appendWRKEvent(unsigned long ticks, MIDIEvent* ev);
    void appendOVEEvent(unsigned long ticks, MIDIEvent* ev);

    void updateTimeLabel(long milliseconds);
    void updateTempoLabel(float ftempo);
    bool isSupported(QString fileName);
    void connectOutput(const QString &driver, const QString &connection);
    void openFile(const QString &fileName);
    void updateState(PlayerState newState);

protected:
    void dragEnterEvent( QDragEnterEvent* event ) override;
    void dropEvent( QDropEvent* event ) override;
    void closeEvent( QCloseEvent* event ) override;
    bool nativeEvent( const QByteArray &eventType, void *message, long *result ) override;
    void showEvent(QShowEvent *event) override;

public slots:
    void about();
    void play();
    void pause();
    void stop();
    void open();
    void setup();
    void tempoReset();
    void volumeReset();
    void tempoSlider(int value);
    void quit();
    void volumeSlider(int value);
    void pitchShift(int value);
    void playerFinished();
    void playerStopped();
    void playerEcho(long time, long ticks);

    void progressDialogInit(const QString& type, int max);
    void progressDialogUpdate(int pos);
    void progressDialogClose();

    void slotShowPianola(bool checked);
    void slotPianolaClosed();
    void slotShowChannels(bool checked);
    void slotChannelsClosed();
    void slotShowLyrics(bool checked);
    void slotLyricsClosed();
    void slotShowRhythm(bool checked);

    void slotAboutTranslation();
    void slotSwitchLanguage(QAction *action);
    void slotFileInfo();

private:
    void createLanguageMenu();
    void retranslateUi();

    PlayerState m_state;
    drumstick::rt::MIDIOutput* m_midiOut;
    SequencePlayer* m_player;
    Ui::GUIPlayerClass* m_ui;
    QPointer<QProgressDialog> m_pd;
    QThread m_playerThread;
    RecentFilesHelper* m_recentFiles;
    QPointer<Connections> m_connections;
    QPointer<Pianola> m_pianola;
    QPointer<Channels> m_channels;
    QPointer<Lyrics> m_lyrics;
    QTranslator *m_trq, *m_trp, *m_trl;
    QAction *m_currentLang;
    bool m_firstShown{true};
#if defined(Q_OS_WINDOWS)
    WinSnap m_snapper;
#endif
};

#endif // INCLUDED_GUIPLAYER_H
