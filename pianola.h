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

#ifndef PIANOLA_H
#define PIANOLA_H

#include <QMainWindow>
#include <drumstick/rtmidioutput.h>

#if defined(Q_OS_WINDOWS)
#include "winsnap.h"
#endif

class QFrame;
class QLabel;

namespace drumstick { namespace widgets {
    class PianoKeybd;
}}

class Pianola : public QMainWindow {
    Q_OBJECT

public:
    Pianola( QWidget* parent = 0 );
    virtual ~Pianola();
    void enableChannel(int channel, bool enable);
    void setNoteRange(int lowerNote, int upperNote);
    void readSettings();
    void writeSettings();
    void retranslateUi();

signals:
    void closed();
    void noteOn(int channel, int note, int vel);
    void noteOff(int channel, int note, int vel);

public slots:
    void playNoteOn(int note, int vel);
    void playNoteOff(int note, int vel);
    void slotNoteOn(int channel, int note, int vel);
    void slotNoteOff(int channel, int note, int vel);
    void slotShowChannel(int chan);
    void slotShowAllChannels();
    void slotHideAllChannels();
    void allNotesOff();
    void slotLabel(int channel, const QString& text);
    void tightenKeys(bool enabled);

protected:
    void closeEvent( QCloseEvent *event ) override;
    void showEvent( QShowEvent * event ) override;
    bool nativeEvent( const QByteArray &eventType, void *message, long *result ) override;

private:
    drumstick::widgets::PianoKeybd* m_piano[drumstick::rt::MIDI_STD_CHANNELS];
    QMenu *m_chmenu;
    QAction *m_a1, *m_a2, *m_a3;
    QFrame* m_frame[drumstick::rt::MIDI_STD_CHANNELS];
    QAction* m_action[drumstick::rt::MIDI_STD_CHANNELS];
    QLabel* m_label[drumstick::rt::MIDI_STD_CHANNELS];
    bool m_tightenKeys;
    int m_lowerNote;
    int m_upperNote;
#if defined(Q_OS_WINDOWS)
    WinSnap m_snapper;
#endif
};

#endif /* PIANOLA_H */
