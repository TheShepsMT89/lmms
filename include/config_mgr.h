/*
 * config_mgr.h - class configManager, a class for managing LMMS-configuration
 *
 * Copyright (c) 2005-2007 Tobias Doerffel <tobydox/at/users.sourceforge.net>
 * 
 * This file is part of Linux MultiMedia Studio - http://lmms.sourceforge.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */


#ifndef _CONFIG_MGR_H
#define _CONFIG_MGR_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#include <QtGui/QDialog>
#include <QtCore/QMap>
#include <QtCore/QVector>
#include <QtCore/QPair>


class QLineEdit;
class QLabel;
class QRadioButton;
class QHBoxLayout;
class QVBoxLayout;
class QFrame;

class engine;


const QString PROJECTS_PATH = "projects/";
const QString PRESETS_PATH = "presets/";
const QString SAMPLES_PATH = "samples/";
const QString DEFAULT_THEME_PATH = "themes/default/";
const QString TRACK_ICON_PATH = "track_icons/";
const QString LOCALE_PATH = "locale/";


class configManager : public QDialog 
{
	Q_OBJECT
public:
	static inline configManager * inst( void )
	{
		if( s_instanceOfMe == NULL )
		{
			s_instanceOfMe = new configManager();
		}
		return( s_instanceOfMe );
	}

	const QString & dataDir( void ) const
	{
		return( m_dataDir );
	}

	const QString & workingDir( void ) const
	{
		return( m_workingDir );
	}

	QString userProjectsDir( void ) const
	{
		return( workingDir() + PROJECTS_PATH );
	}

	QString userPresetsDir( void ) const
	{
		return( workingDir() + PRESETS_PATH );
	}

	QString userSamplesDir( void ) const
	{
		return( workingDir() + SAMPLES_PATH );
	}

	QString factoryProjectsDir( void ) const
	{
		return( dataDir() + PROJECTS_PATH );
	}

	QString factoryPresetsDir( void ) const
	{
		return( dataDir() + PRESETS_PATH );
	}

	QString factorySamplesDir( void ) const
	{
		return( dataDir() + SAMPLES_PATH );
	}

	QString defaultArtworkDir( void ) const
	{
		return( m_dataDir + DEFAULT_THEME_PATH );
	}

	QString artworkDir( void ) const
	{
		return( m_artworkDir );
	}

	QString trackIconsDir( void ) const
	{
		return( m_dataDir + TRACK_ICON_PATH );
	}

	QString localeDir( void ) const
	{
		return( m_dataDir + LOCALE_PATH );
	}

	const QString & pluginDir( void ) const
	{
		return( m_pluginDir );
	}

	const QString & vstDir( void ) const
	{
		return( m_vstDir );
	}

	const QString & flDir( void ) const
	{
		return( m_flDir );
	}

	const QString & ladspaDir( void ) const
	{
		return( m_ladDir );
	}

#ifdef HAVE_STK_H
	const QString & stkDir( void ) const
	{
		return( m_stkDir );
	}
#endif

	inline const QStringList & recentlyOpenedProjects( void ) const
	{
		return( m_recentlyOpenedProjects );
	}

	void addRecentlyOpenedProject( const QString & _file );

	const QString & value( const QString & _class,
					const QString & _attribute ) const;
	void setValue( const QString & _class, const QString & _attribute,
						const QString & _value );

	bool loadConfigFile( void );
	void saveConfigFile( void );


public slots:
	void setWorkingDir( const QString & _wd );
	void setVSTDir( const QString & _vd );
	void setArtworkDir( const QString & _ad );
	void setFLDir( const QString & _fd );
	void setLADSPADir( const QString & _fd );
	void setSTKDir( const QString & _fd );


protected slots:
	void openWorkingDir( void );

	virtual void accept( void );

        void backButtonClicked( void );
        void nextButtonClicked( void );
	void switchPage( int _pg );
	void switchPage( QWidget * _pg );


private:
	static configManager * s_instanceOfMe;

	configManager( void );
	configManager( const configManager & _c );
	~configManager();

	void createWidgets( void );


	void addPage( QWidget * _w, const QString & _title );

	void loadStyleSheet( void );


	const QString m_lmmsRcFile;
	QString m_workingDir;
	QString m_dataDir;
	QString m_artworkDir;
	QString m_pluginDir;
	QString m_vstDir;
	QString m_flDir;
	QString m_ladDir;
#ifdef HAVE_STK_H
	QString m_stkDir;
#endif
	QStringList m_recentlyOpenedProjects;


	typedef QVector<QPair<QString, QString> > stringPairVector;
	typedef QMap<QString, stringPairVector> settingsMap;
	settingsMap m_settings;


	QWidget * m_pageIntro;
	QWidget * m_pageWorkingDir;
	QWidget * m_pageFiles;

	QRadioButton * m_samplesCopyRB;
	QRadioButton * m_presetsCopyRB;
	QRadioButton * m_projectsCopyRB;

	QLineEdit * m_wdLineEdit;

	// wizard stuff
	QList<QPair<QWidget *, QString> > m_pages;
	int m_currentPage;
	QFrame * m_hbar;
	QWidget * m_contentWidget;
	QLabel * m_title;
	QPushButton * m_cancelButton;
	QPushButton * m_backButton;
	QPushButton * m_nextButton;
	QPushButton * m_finishButton;
	QHBoxLayout * m_buttonLayout;
	QHBoxLayout * m_mainLayout;
	QVBoxLayout * m_contentLayout;


	friend class engine;

} ;

#endif
