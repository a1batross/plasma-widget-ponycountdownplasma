/*
 *         DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                     Version 2, December 2004
 *
 *  Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>
 *
 *  Everyone is permitted to copy and distribute verbatim or modified
 *  copies of this license document, and changing it is allowed as long
 *  as the name is changed.
 *
 *             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *    TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *   0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#include "ponycountdownplasma.h"
#include "qdbusnotification.h"
#include <KLocale>
#include <QGraphicsLinearLayout>
#include <KSystemTimeZones>

/*
     ******************************************************************** 
     *              *               *                 *                 *
     * m_label_days * m_label_hours * m_label_minutes * m_label_seconds * First row. Contain 4 labels with estimated time
     *              *               *                 *                 * information.
     ********************************************************************  
     *              *               *                 *                 *
     *    Days      *    Hours      *   Minutes       *   Seconds       * Second row. Contain 4 labels with non-changing
     *              *               *                 *                 * text
     ******************************************************************** 
     *                   *                      *                       *
     *  m_label_season   *    m_label_name      *    m_label_ep         * Third row. Contain 3 labels 
     *                   *                      *                       * with next premiere information
     ********************************************************************
*/
    


ponycountdownplasma::ponycountdownplasma(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args),
    m_svg(this), 
    m_label_ep(0), m_label_name(0), m_label_season(0),
    m_label_day_est(0), m_label_hour_est(0), m_label_min_est(0), m_label_sec_est(0)
{
    // this will get us the standard applet background, for free!
    setBackgroundHints(DefaultBackground);
    m_svg.setImagePath("widgets/background");
    setHasConfigurationInterface(false);
    setAspectRatioMode(Plasma::IgnoreAspectRatio);
    
    m_font.setPixelSize(24);
    
    resize(500, 150);
    
}

ponycountdownplasma::~ponycountdownplasma()
{

}

void ponycountdownplasma::init()
{
    download();
    
    layout = new QGraphicsGridLayout(this);
    layout->setSpacing(10);
    
    show_firstrow();
    show_secondrow();
    show_thirdrow();
}


void ponycountdownplasma::download()
{
    // Download file and call parse() when it will be downloaded
    m_dl.getFile("http://api.ponycountdown.com/next");
    connect(&m_dl, SIGNAL(downloaded()), SLOT(prepare()));
}


void ponycountdownplasma::prepare()
{
    //Parsing JSON
    QJson::Parser parser;
    bool ok;
    m_info = parser.parse(m_dl.downloadedData().toUtf8(), &ok).toMap();
    
    if(!ok)
    {
      setFailedToLaunch(true, i18n("A problem with JSON, try to restart or check your network settings"));
    }
    m_datetime = KSystemTimeZones::local().toZoneTime(m_datetime.fromString(info("time"), Qt::ISODate));
    
    m_tonewep.setFromMSecs(m_datetime.toMSecsSinceEpoch() - QDateTime::currentDateTime().toMSecsSinceEpoch());
    
    update(); 
}



void ponycountdownplasma::update()
{   
    m_label_season->setText(i18n("Season №%1", info("season")));
    m_label_name->setText(i18n("Episode Name: %1", info("name")));
    m_label_ep->setText(i18n("Episode №%1", info("episode")));
    
    timerstart();
}

void ponycountdownplasma::show_firstrow()
{
    m_label_day_est = new Plasma::Label;
    m_label_hour_est = new Plasma::Label;
    m_label_min_est = new Plasma::Label;
    m_label_sec_est = new Plasma::Label; 
    
    m_label_day_est->setAlignment(Qt::AlignCenter);
    m_label_day_est->setFont(m_font);
    m_label_day_est->setText("0");
    
    m_label_hour_est->setAlignment(Qt::AlignCenter);
    m_label_hour_est->setFont(m_font);
    m_label_hour_est->setText("0");
    
    m_label_min_est->setAlignment(Qt::AlignCenter);
    m_label_min_est->setFont(m_font);
    m_label_min_est->setText("0");
    
    m_label_sec_est->setAlignment(Qt::AlignCenter);
    m_label_sec_est->setFont(m_font);
    m_label_sec_est->setText("0");
    
    layout->setRowMaximumHeight(1, 24);
    layout->addItem(m_label_day_est, 1, 1);
    layout->addItem(m_label_hour_est, 1, 2);
    layout->addItem(m_label_min_est, 1, 3);
    layout->addItem(m_label_sec_est, 1, 4);
}
    
void ponycountdownplasma::show_secondrow()
{
    Plasma::Label *m_label_day = new Plasma::Label;
    Plasma::Label *m_label_hour = new Plasma::Label;
    Plasma::Label *m_label_min = new Plasma::Label;
    Plasma::Label *m_label_sec = new Plasma::Label;
    
    m_label_day->setAlignment(Qt::AlignCenter);
    m_label_day->setText(i18n("Days"));
    
    m_label_hour->setAlignment(Qt::AlignCenter);
    m_label_hour->setText(i18n("Hours"));
    
    m_label_min->setAlignment(Qt::AlignCenter);
    m_label_min->setText(i18n("Minutes"));
    
    m_label_sec->setAlignment(Qt::AlignCenter);
    m_label_sec->setText(i18n("Seconds"));
    
    layout->setRowMaximumHeight(2, 12);
    layout->addItem(m_label_day, 2, 1);
    layout->addItem(m_label_hour, 2, 2);
    layout->addItem(m_label_min, 2, 3);
    layout->addItem(m_label_sec, 2, 4);
}
    
void ponycountdownplasma::show_thirdrow()
{
    QGraphicsLinearLayout *thirdrow = new QGraphicsLinearLayout();
    
    m_label_ep = new Plasma::Label;
    m_label_name = new Plasma::Label;
    m_label_season = new Plasma::Label;
  
    //Setting text for label of third row. 
    m_label_season->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    m_label_season->setText(i18n("Season №%1", info("season")));
    
    m_label_name->setAlignment(Qt::AlignCenter);
    m_label_name->setText(i18n("Episode Name: %1", info("name")));
    
    m_label_ep->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    m_label_ep->setText(i18n("Episode №%1", info("episode")));
    
    
    layout->addItem(thirdrow, 3, 1, 1, 4);
    layout->setAlignment(thirdrow, Qt::AlignTop);
    //layout->setRowMaximumHeight(3, 12);
    
    thirdrow->setOrientation(Qt::Horizontal);
    thirdrow->addItem(m_label_season);
    thirdrow->addItem(m_label_name);
    thirdrow->addItem(m_label_ep);
}

void ponycountdownplasma::timerstart()
{
    connect(&m_cd, SIGNAL(timeout()), SLOT(interval_to()));
    m_cd.setInterval(1000);
    m_cd.start();
    
}

void ponycountdownplasma::interval_to()
{
    m_tonewep -= 1000;
    
    if(timePart(Qt::Milliseconds) < 0) {
      showNotification("ponycountdownplasma",
		       "Ponies!",
		       "New episode of My Little Pony: Friendship is Magic was started",
		       "ponycountdown"
      );
      download();
      return;		//Do not do anything >:3
    }
    
    m_label_day_est->setText(timePart(Qt::Days));
    m_label_hour_est->setText(timePart(Qt::Hours));
    m_label_min_est->setText(timePart(Qt::Minutes));
    m_label_sec_est->setText(timePart(Qt::Seconds));
    
    //qDebug() << timePart(Qt::Days) << timePart(Qt::Hours) << timePart(Qt::Minutes) << timePart(Qt::Seconds);
}





#include "ponycountdownplasma.moc"
