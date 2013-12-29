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

// Here we avoid loading the header multiple times
#ifndef PONYCOUNTDOWNPLASMA_HEADER
#define PONYCOUNTDOWNPLASMA_HEADER

//#include <KIcon>
// We need the Plasma Applet headers
#include <Plasma/Applet>
#include <Plasma/Svg>
#include <Plasma/Label>
#include <QGraphicsGridLayout>

//Download File
#include "filedownloader.h"

//QJson
#include <qjson/parser.h>
#include <QVariant>

#include <QTimer>
#include <qtimespan.h>		//Is not my class ^^
				//See https://gitorious.org/qtimespandevel


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
	
	void init(); //Here calls download();
	void download();		//download() downloading file and calls SLOT parse(); 
	void update();			//show() is calling after prepare(). This function is important,
					//because here declares main layout
 
	void show_firstrow();		//see README for help about this three
	void show_secondrow();		//little functions
	void show_thirdrow();
	
	void timerstart();		//this func is important too! Here starts countdown to new episode :)
	
	inline QString timePart(Qt::TimeSpanUnit unit, Qt::TimeSpanFormat format = Qt::DaysAndTime) { return QString::number(m_tonewep.part(unit, format)); }; 
	inline QString info(const char * request) { return m_info[request].toString(); }
	
    protected slots:
	void prepare();
	void interval_to();
	
    signals:
	void ep_here();
	
    private:
	// ---------DOWNLOADING DATA-----------
	fileDownloader m_dl;		// Class for downloading files from http. 
					// See filedownloader.h
	QVariantMap m_info; 		// Here goes parsed JSON data
	
	// -------TIMEY-WIMEY... STUFF---------
	
	QDateTime m_datetime;		// Episode Date & Time
	QTimer m_cd;			// A timer for m_tonewep
	QTimeSpan m_tonewep;		// Estimated Date & Time
	
	// -----------PLASMA THINGS------------
	Plasma::Svg m_svg;
	QGraphicsGridLayout *layout;
	QFont m_font;			//A Font settings
	Plasma::Label *m_label_ep, *m_label_name, *m_label_season, //third row
		      // Need more Plasma::Label! 
		      *m_label_day_est, *m_label_hour_est, *m_label_min_est, *m_label_sec_est; // first row

};
 
// This is the command that links your applet to the .desktop file
K_EXPORT_PLASMA_APPLET(ponycountdownplasma, ponycountdownplasma)
#endif
