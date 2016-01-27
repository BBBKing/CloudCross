#include "include/mscloudprovider.h"





MSCloudProvider::MSCloudProvider()
{
    this->lastSyncTime=0;
    this->strategy=MSCloudProvider::SyncStrategy::PreferLocal;// by default

    // set flags to default
    this->flags.insert("dryRun",false);
    this->flags.insert("useInclude",false);
    this->flags.insert("noHidden",false);
    this->flags.insert("newRev",false);

//    this->dryRun=false;
//    this->useInclude=false;
//    this->noHidden=true;
//    this->newRev=false;
}

void MSCloudProvider::saveTokenFile(QString path){
    return;
}

void MSCloudProvider::loadTokenFile(QString path){
    return;
}

void MSCloudProvider::refreshToken(){
    return;
}


QString MSCloudProvider::fileChecksum(QString &fileName, QCryptographicHash::Algorithm hashAlgorithm){

    QFile f(fileName);

    if (f.open(QFile::ReadOnly)){

            QCryptographicHash hash(hashAlgorithm);

            if (hash.addData(&f)){

                return QString(hash.result().toHex());

            }
    }
    return QString();
}

// convert to milliseconds in UTC timezone
qint64 MSCloudProvider::toMilliseconds(QDateTime dateTime, bool isUTC){

    if(!isUTC){// dateTime currently in UTC, need convert

        QDateTime dateTime1=QDateTime(dateTime);
        qint64 delta;


        dateTime.setTimeSpec(Qt::UTC);
        dateTime=dateTime.toLocalTime();

        delta=dateTime.toMSecsSinceEpoch() - dateTime1.toMSecsSinceEpoch();

        QDateTime dd=QDateTime::fromMSecsSinceEpoch(dateTime1.toMSecsSinceEpoch() - delta);

        return dateTime1.toMSecsSinceEpoch() - delta;

    }
    else{
        return dateTime.toMSecsSinceEpoch();
    }

}


// convert to milliseconds in UTC timezone
qint64 MSCloudProvider::toMilliseconds(QString dateTimeString, bool isUTC){

    if(!isUTC){

        QDateTime d=QDateTime::fromString(dateTimeString,Qt::DateFormat::ISODate);
        QDateTime d1=QDateTime(d);

        qint64 delta;

        d.setTimeSpec(Qt::UTC);
        d=d.toLocalTime();

        delta= d.toMSecsSinceEpoch() - d1.toMSecsSinceEpoch();

        QDateTime dd=QDateTime::fromMSecsSinceEpoch(d1.toMSecsSinceEpoch() - delta);

        return  d1.toMSecsSinceEpoch() - delta;
    }
    else{

        QDateTime d=QDateTime::fromString(dateTimeString,Qt::DateFormat::ISODate);
        return d.toMSecsSinceEpoch();
    }

}


void MSCloudProvider::setFlag(QString flagName, bool flagVal){

    this->flags.insert(flagName,flagVal);

}


bool MSCloudProvider::getFlag(QString flagName){

    QHash<QString,bool>::iterator it=this->flags.find(flagName);
    if(it != this->flags.end()){
        return it.value();
    }
    else{
        return false;
    }
}


