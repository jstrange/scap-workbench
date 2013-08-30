/*
 * Copyright 2013 Red Hat Inc., Durham, North Carolina.
 * All Rights Reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *      Martin Preisler <mpreisle@redhat.com>
 */

#include "Scanner.h"
#include <QThread>

Scanner::Scanner():
    mScannerMode(SM_SCAN),
    mScanThread(0),
    mMainThread(0),
    mSession(0),
    mTarget("")
{}

Scanner::~Scanner()
{}

void Scanner::setScanThread(QThread* thread)
{
    mScanThread = thread;
}

void Scanner::setMainThread(QThread* thread)
{
    mMainThread = thread;
}

void Scanner::setSession(ScanningSession* session)
{
    // TODO: assert that we are not running
    mSession = session;
}

void Scanner::setTarget(const QString& target)
{
    // TODO: assert that we are not running
    mTarget = target;
}

const QString& Scanner::getTarget() const
{
    return mTarget;
}

void Scanner::setScannerMode(ScannerMode mode)
{
    // TODO: assert that we are not running
    mScannerMode = mode;
}

ScannerMode Scanner::getScannerMode() const
{
    return mScannerMode;
}

void Scanner::setARFForRemediation(const QByteArray& results)
{
    mARFForRemediation = results;
}

const QByteArray& Scanner::getARFForRemediation() const
{
    return mARFForRemediation;
}

void Scanner::signalCompletion(bool cancel)
{
    if (cancel)
        emit canceled();
    else
        emit finished();

    if (mMainThread)
    {
        moveToThread(mMainThread);
    }

    if (mScanThread)
    {
        mScanThread->quit();
        mScanThread = 0;
    }
}