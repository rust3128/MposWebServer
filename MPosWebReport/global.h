#ifndef GLOBAL_H
#define GLOBAL_H
#include <QCoreApplication>
#include <QDir>
#include "httpsessionstore.h"
#include "staticfilecontroller.h"

#include "filelogger.h"
#include "templatecache.h"

using namespace stefanfrings;


/** Redirects log messages to a file */
extern FileLogger* logger;
extern TemplateCache* templateCache;
extern QString searchConfigFile();
/** Функция поиска конфигурационного файла */


#endif // GLOBAL_H
