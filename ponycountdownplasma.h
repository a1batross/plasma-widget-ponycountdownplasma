/***************************************************************************
 *   Copyright (C) %{CURRENT_YEAR} by %{AUTHOR} <%{EMAIL}>                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

// Here we avoid loading the header multiple times
#ifndef PONYCOUNTDOWNPLASMA_HEADER
#define PONYCOUNTDOWNPLASMA_HEADER

#include <KIcon>
// We need the Plasma Applet headers
#include <Plasma/Applet>
#include <Plasma/Svg>
#include <Plasma/Label>

//Download File
#include <QUrl>
#include "filedownloader.h"

//QJson
#include <qjson/parser.h>
#include <QVariant>
#include <QLCDNumber>
#include <QTimer>
#include <KTimeZone>
#include <qtimespan.h>


class QSizeF;

namespace Plasma {
    class Label;
}

// Define our plasma Applet
class ponycountdownplasma : public Plasma::Applet
{
    Q_OBJECT
    public:
        // Basic Create/Destroy
        ponycountdownplasma(QObject *parent, const QVariantList &args);
        ~ponycountdownplasma();
	

        void init();
	void show();
	void timershow();
	
    //signals:
	//void ep_here();
	
    private slots:
	void parse();
	//void ep_here_notify();
	void interval_to();

    private:
        Plasma::Svg m_svg;
	QString m_json;
	QTimer m_cd;
	fileDownloader m_dl;
	QFont m_font;
	
	//Premiere information
	QVariantMap m_info;
	QDateTime m_datetime;
	QTimeSpan m_tonewep;
	Plasma::Label *m_label_ep;
	Plasma::Label *m_label_name;
	Plasma::Label *m_label_season;
	Plasma::Label *m_label_timeto;
	KTimeZone m_tz;
	
};
 
// This is the command that links your applet to the .desktop file
K_EXPORT_PLASMA_APPLET(ponycountdownplasma, ponycountdownplasma)
#endif
