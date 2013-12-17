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

#include "ponycountdownplasma.h"
#include <QPainter>
#include <QFontMetrics>
#include <QSizeF>
#include <KLocale>
#include <QGraphicsGridLayout>


#include <plasma/svg.h>
#include <plasma/theme.h>
#include <plasma/widgets/lineedit.h>
#include <plasma/widgets/pushbutton.h>
#include <knotification.h>
#include <KTimeZone>

ponycountdownplasma::ponycountdownplasma(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args),
    m_svg(this)
{
    // this will get us the standard applet background, for free!
    setBackgroundHints(DefaultBackground);
    m_svg.setImagePath("widgets/background");
    setHasConfigurationInterface(false);  
    resize(500, 140);
    
    m_font.setPixelSize(24);
    
}

ponycountdownplasma::~ponycountdownplasma()
{
    if (hasFailedToLaunch()) {
        // Do some cleanup here
    } else {
        // Save settings
    }
}


void ponycountdownplasma::parse()
{
    m_json = m_dl.downloadedData();
    
    qDebug() << "Got JSON: " << m_json;
    
    QJson::Parser parser;
    bool ok;
  
    m_info = parser.parse(m_json.toUtf8(), &ok).toMap();
    
    if(!ok)
    {
      setFailedToLaunch(true, i18n("Oops! A little problem when reading JSON."));
    }
    
    show(); // The show must go on!
}

void ponycountdownplasma::timershow()
{
    QDateTime now = QDateTime::currentDateTime();
    
    
    
    m_tonewep.setFromMSecs(m_datetime.toMSecsSinceEpoch() - now.toMSecsSinceEpoch());
    
    m_cd.setInterval(1000);
    
    connect(&m_cd, SIGNAL(timeout()), SLOT(interval_to()));
    
    m_cd.start();
    
}

void ponycountdownplasma::interval_to()
{
    m_tonewep -= 1000;
    QString days = QString::number(m_tonewep.daysPart()) + " days ";
    QString hours = QString::number(m_tonewep.hoursPart()) + " hours ";
    QString min = QString::number(m_tonewep.minutesPart()) + " minutes ";
    QString secs = QString::number(m_tonewep.secsPart()) + " seconds ";
    
    QString full = days + hours + min + secs;
    
    qDebug() << full;
    
    m_label_timeto->setText(full);
}


//void ponycountdownplasma::timeout()
//{
//    KNotification *notify = new KNotification( "ponyOnLine" );
//    notify->setText("Ponies is here!");
//
//    notify->sendEvent();
//}

void ponycountdownplasma::show()
{
    QGraphicsGridLayout *layout = new QGraphicsGridLayout(this);
    //layout->setOrientation(Qt::Vertical); //so widgets will be stacked up/down
    layout->setSpacing(20.0);
    layout->setRowStretchFactor(2, 3);
    
    m_datetime = m_datetime.fromString(m_info["time"].toString(), Qt::ISODate);
    m_datetime = m_tz.toZoneTime(m_datetime);
    
    
    qDebug() << "Success parsed to name" << m_info["name"].toString();
    qDebug() << "Time for episode is now" << m_datetime.toString();
    
    QString ep_name = "Name: " + m_info["name"].toString();
    QString ep_ep = "Episode: " + m_info["episode"].toString();
    QString ep_season = "Season: " + m_info["season"].toString();
     

    m_label_season = new Plasma::Label(this);
    m_label_ep = new Plasma::Label(this);
    m_label_name = new Plasma::Label(this);
    m_label_timeto = new Plasma::Label(this);

    m_label_season->setText(ep_season);
    m_label_season->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    m_label_ep->setText(ep_ep);
    m_label_ep->setAlignment(Qt::AlignVCenter | Qt::AlignCenter);
    m_label_name->setText(ep_name);
    m_label_name->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    m_label_timeto->setText("0 seconds");
    m_label_timeto->setAlignment(Qt::AlignVCenter | Qt::AlignCenter);
    m_label_timeto->setFont(m_font);
    
    layout->addItem(m_label_season, 1, 1); 
    layout->addItem(m_label_ep, 1, 2); 
    layout->addItem(m_label_name, 1, 3); 
    layout->addItem(m_label_timeto, 2, 1, 1, 3);
    
    timershow();
}

void ponycountdownplasma::init()
{
    m_dl.setUrl((QUrl)"http://api.ponycountdown.com/next");
    connect(&m_dl, SIGNAL(downloaded()), SLOT(parse()));

    
}

#include "ponycountdownplasma.moc"
